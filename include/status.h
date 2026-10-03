#ifndef STATUS_H
#define STATUS_H

typedef enum {
    OK = 0,
    REMOVED = 1,
    ERROR_NULL = -1,
    ERROR_MEM = -2,
    ERROR_INVAL = -3,
    ERROR_TITLE_EMPTY = -4,
    ERROR_TITLE_LONG = -5,
    ERROR_TITLE_CHAR = -6,
    ERROR_NOT_FOUND = -7,
    ERROR_EXISTS = -8,
    ERROR_IO = -9,
} Status;

const char *status_message(Status status);

#endif
