#include "status.h"

const char *status_message(Status status)
{
    switch (status) {
    case OK:
        return "";
    case REMOVED:
        return "该书名已存在，当前这本书已删除";
    case ERROR_NULL:
        return "调用参数是空指针";
    case ERROR_MEM:
        return "内存分配失败";
    case ERROR_INVAL:
        return "命令参数不合法";
    case ERROR_TITLE_EMPTY:
        return "书名去掉首尾空白后为空";
    case ERROR_TITLE_LONG:
        return "书名超过 200 字节";
    case ERROR_TITLE_CHAR:
        return "书名含有非英文字母、连字符或其他非法字符";
    case ERROR_NOT_FOUND:
        return "书号不存在";
    case ERROR_EXISTS:
        return "书名已存在，数据未改";
    case ERROR_IO:
        return "读写数据文件失败";
    default:
        return "未知错误";
    }
}
