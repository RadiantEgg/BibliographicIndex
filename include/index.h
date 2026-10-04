#ifndef INDEX_H
#define INDEX_H

#include "status.h"

typedef struct index_list index_list;

Status index_create(index_list **index);
void index_free(index_list **index);
Status index_add(index_list *index, const char *keyword, int book_id);
Status index_remove(index_list *index, const char *keyword, int book_id);
Status index_find(const index_list *index, const char *keyword, Status (*visit)(int book_id, void *ctx), void *ctx);
Status index_intersect(const index_list *index, const char **keywords, int count, Status (*visit)(int book_id, void *ctx), void *ctx);
Status index_foreach(const index_list *index, Status (*visit)(const char *keyword, int book_id, void *ctx), void *ctx);


#endif