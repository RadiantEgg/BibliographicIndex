#ifndef STOPWORD_H
#define STOPWORD_H

#include "status.h"

typedef struct stopword_list stopword_list;

Status stopword_create(stopword_list **stopwords);
void stopword_free(stopword_list **stopwords);
Status stopword_add(stopword_list *stopwords, const char *word);
Status stopword_remove(stopword_list *stopwords, const char *word);
int stopword_contains(const char *word, void *stopwords);
Status stopword_foreach(const stopword_list *stopwords, Status (*visit)(const char *word, void *ctx), void *ctx);

#endif
