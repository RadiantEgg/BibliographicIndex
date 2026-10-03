#ifndef STOPWORD_H
#define STOPWORD_H

#include "status.h"

typedef struct stopword_list stopword_list;

Status stopword_create(stopword_list **out);
void stopword_free(stopword_list **list);
Status stopword_add(stopword_list *list, const char *word);
Status stopword_remove(stopword_list *list, const char *word);
int stopword_contains(const char *word, void *stopwords);
Status stopword_foreach(stopword_list *list, Status (*visit)(const char *word, void *ctx), void *ctx);

#endif
