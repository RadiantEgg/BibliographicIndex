#ifndef BOOK_H
#define BOOK_H

#include "status.h"
#include "index.h"
#include "stopword.h"

typedef struct book_list book_list;

Status book_create(book_list **books);
void book_free(book_list **books);
Status book_add(book_list *books, const char *title, index_list *index, stopword_list *stopwords, int *existing_id);
Status book_add_id(book_list *books, int book_id, const char *title, index_list *index, stopword_list *stopwords);
Status book_edit(book_list *books, int book_id, const char *title, index_list *index, stopword_list *stopwords, int *kept_id);
Status book_delete(book_list *books, int book_id, index_list *index);
Status book_title(const book_list *books, int book_id, const char **title);
Status book_foreach(const book_list *books, Status (*visit)(int book_id, const char *title, void *ctx), void *ctx);

#endif
