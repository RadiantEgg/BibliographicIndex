#ifndef STORE_H
#define STORE_H

#include "status.h"
#include "book.h"
#include "index.h"
#include "stopword.h"

Status store_load(book_list **books, index_list **index, stopword_list **stopwords);
Status store_save(const book_list *books, const stopword_list *stopwords);

#endif
