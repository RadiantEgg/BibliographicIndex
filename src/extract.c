#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "status.h"
#include "extract.h"

static void to_lower(const char *src, char *dst)
{
    while (*src) 
        *dst++ = tolower((unsigned char)*src++);
    *dst = '\0';
}

static void shrink_whitespace(const char *src, char *dst)
{
    char word[MAX_TITLE_LENGTH];
    int n;
    int first = 1;

    while (sscanf(src, "%199s%n", word, &n) == 1) {
        if (!first)
            *dst++ = ' ';
        dst += sprintf(dst, "%s", word);
        first = 0;
        src += n;
    }
    *dst = '\0';
}

static void free_words(char **words, int n)
{
    for (int i = 0; i < n; i++)
        free(words[i]);
}

static Status get_title_words(const char *title, char **buf, int capacity, int *count)
{
    char word[MAX_TITLE_LENGTH];
    const char *src = title;
    int n;
    int i = 0;

    *count = 0;
    while (sscanf(src, "%199s%n", word, &n) == 1) {
        int len;

        if (i >= capacity) {
            free_words(buf, i);
            return ERROR_TITLE_LONG;
        }

        len = (int)strlen(word);
        buf[i] = malloc((size_t)len + 1);
        if (buf[i] == NULL) {
            free_words(buf, i);
            return ERROR_MEM;
        }
        memcpy(buf[i], word, (size_t)len + 1);
        i++;
        src += n;
    }

    *count = i;
    return OK;
}

static int already_kept(char **words, int n, const char *word)
{
    for (int i = 0; i < n; i++) {
        if (strcmp(words[i], word) == 0)
            return 1;
    }
    return 0;
}

Status title_check(const char *title)
{
    const unsigned char *p;
    int has_letter = 0;

    if (title == NULL)
        return ERROR_TITLE_EMPTY;

    p = (const unsigned char *)title;
    while (*p) {
        if (isalpha(*p))
            has_letter = 1;
        else if (!isspace(*p))
            return ERROR_TITLE_CHAR;
        p++;
    }

    if ((const char *)p - title >= MAX_TITLE_LENGTH)
        return ERROR_TITLE_LONG;
    if (!has_letter)
        return ERROR_TITLE_EMPTY;
    return OK;
}

Status title_normalize(const char *title, char **normalized_title)
{
    char *buf;

    if (normalized_title == NULL)
        return ERROR_NULL;
    *normalized_title = NULL;

    if (title == NULL)
        return ERROR_TITLE_EMPTY;

    buf = malloc(strlen(title) + 1);
    if (buf == NULL)
        return ERROR_MEM;

    to_lower(title, buf);
    shrink_whitespace(buf, buf);

    int len = strlen(buf);
    char *tmp = realloc(buf, len + 1);
    if (tmp != NULL)
        buf = tmp;

    *normalized_title = buf;
    return OK;
}

Status title_keywords(const char *normalized_title, int (*is_stopword)(const char *word, void *stopwords), void *stopwords, const char ***keywords, int *count)
{
    enum {
        MAX_WORDS = MAX_TITLE_LENGTH / 2
    };

    char *buf[MAX_WORDS];
    char *kept[MAX_WORDS];
    const char **out;
    int n = 0;
    int k = 0;
    Status status;

    if (keywords == NULL || count == NULL)
        return ERROR_NULL;
    *keywords = NULL;
    *count = 0;

    if (normalized_title == NULL || is_stopword == NULL || stopwords == NULL)
        return ERROR_NULL;

    status = get_title_words(normalized_title, buf, MAX_WORDS, &n);
    if (status != OK)
        return status;

    for (int i = 0; i < n; i++) {
        if (is_stopword(buf[i], stopwords) || already_kept(kept, k, buf[i])) {
            free(buf[i]);
            continue;
        }
        kept[k++] = buf[i];
    }

    if (k == 0)
        return OK;

    out = malloc((size_t)k * sizeof *out);
    if (out == NULL) {
        free_words(kept, k);
        return ERROR_MEM;
    }

    for (int i = 0; i < k; i++)
        out[i] = kept[i];
    *keywords = out;
    *count = k;
    return OK;
}
