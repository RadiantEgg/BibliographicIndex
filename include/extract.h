#ifndef EXTRACT_H
#define EXTRACT_H

#define MAX_TITLE_LENGTH 200

#include "status.h"

Status title_check(const char *title);
Status title_normalize(const char *title, char **normalized_title);
Status title_keywords(const char *normalized_title, int (*is_stopword)(const char *word, void *stopwords), void *stopwords, const char ***keywords, int *count);

#endif
