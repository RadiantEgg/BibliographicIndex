#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "status.h"
#include "stopword.h"

typedef struct stopword_node {
    char *word;
    struct stopword_node *next;
} stopword_node;

struct stopword_list {
    stopword_node head;
};


static stopword_node *get_pre(stopword_list *stopwords, const char *word)
{
    if (stopwords == NULL || word == NULL)
        return NULL;

    stopword_node *pre = &stopwords->head;
    while (pre->next && strcmp(pre->next->word, word) < 0)      
        pre = pre->next; 
    return pre;
}

static Status make_stopword_node(const char *word, stopword_node **out)
{
    if (word == NULL || out == NULL)
        return ERROR_NULL;
    *out = NULL;

    stopword_node *newnode = malloc(sizeof((*newnode)));
    if (newnode == NULL)        return ERROR_MEM;

    size_t len = strlen(word);
    newnode->word = malloc(len + 1);
    if (newnode->word == NULL)  {
        free(newnode);
        return ERROR_MEM;
    }
    memcpy(newnode->word, word, len + 1);
    newnode->next = NULL;

    *out = newnode;
    return OK;
}

Status stopword_create(stopword_list **stopwords)
{
    if (stopwords == NULL)      return ERROR_NULL;
    *stopwords = NULL;

    stopword_list *tmp = malloc(sizeof(*tmp));
    if (tmp == NULL)            return ERROR_MEM;

    tmp->head.word= NULL;
    tmp->head.next = NULL;
    *stopwords = tmp;
    return OK;
}

void stopword_free(stopword_list **stopwords)
{
    if (stopwords == NULL || *stopwords == NULL)        return;

    stopword_node *cur = (*stopwords)->head.next;
    while (cur) {
        stopword_node *tmp = cur;
        cur = cur->next;
        free(tmp->word);
        free(tmp);
    }

    free(*stopwords);
    *stopwords = NULL;
}

Status stopword_add(stopword_list *stopwords, const char *word)
{
    if (stopwords == NULL || word == NULL)
        return ERROR_NULL;

    if (stopword_contains(word, stopwords))      return ERROR_EXISTS;

    stopword_node *newnode;
    Status st = make_stopword_node(word, &newnode);
    if (st != OK)                           return st;

    stopword_node *pre = get_pre(stopwords, word);
    newnode->next = pre->next;
    pre->next = newnode;

    return OK;
}

Status stopword_remove(stopword_list *stopwords, const char *word)
{
    if (stopwords == NULL || word == NULL)
        return ERROR_NULL;

    if (!stopword_contains(word, stopwords))     return ERROR_NOT_FOUND;

    stopword_node *pre = get_pre(stopwords, word);

    stopword_node *tmp = pre->next;
    pre->next = tmp->next;
    free(tmp->word);
    free(tmp);
    return OK;
}

int stopword_contains(const char *word, void *stopwords)
{
    if (word == NULL || stopwords == NULL)
        return 0;

    stopword_node *cur = ((stopword_list *)stopwords)->head.next;
    while (cur) {
        if (strcmp(cur->word, word) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

Status stopword_foreach(const stopword_list *stopwords, Status (*visit)(const char *word, void *ctx), void *ctx)
{
    if (stopwords == NULL || visit == NULL)
        return ERROR_NULL;

    stopword_node *cur = stopwords->head.next;
    while (cur) {
        Status st = visit(cur->word, ctx);
        if (st != OK)
            return ERROR_VISIT;
        cur = cur->next;
    }
    return OK;
}
