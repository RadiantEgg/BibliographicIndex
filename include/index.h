#ifndef INDEX_H
#define INDEX_H

#include "status.h"

typedef struct index_list index_list;

Status index_create(index_list **out);
void index_free(index_list **list);
Status index_add(index_list *list, const char *keyword, int number);
Status index_remove(index_list *list,  const char *keyword, int number);
Status index_find(const index_list *list, const char *keyword, Status (*visit)(int book_id, void *ctx), void *ctx);
Status index_intersect(const index_list *list, const char **keywords, int count, Status (*visit)(int book_id, void *ctx), void *ctx);
Status index_foreach(const index_list *list, Status (*visit)(const char *keyword, int book_id, void *ctx), void *ctx);


#endif