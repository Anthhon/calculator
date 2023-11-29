#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include <stdint.h>

#define LogInfo(...) fprintf(stdout, "[+] "); \
    fprintf(stdout, __VA_ARGS__)
#define LogExit(...) fprintf(stderr, "[!] "); \
    fprintf(stderr, __VA_ARGS__); \
    exit(EXIT_FAILURE)

#define OPERATIONS_SYMBOLS "+-*/^"

enum {
    OPER_SUM,
    OPER_MIN,
    OPER_MUL,
    OPER_DIV,
    OPER_POW,
    OPER_NONE,
};

typedef struct {
    int64_t value;
    uint8_t operation;
} Operation;

typedef struct {
    Operation *operations;
    uint16_t capacity;
} OperationsManager;

#endif // _INCLUDES_H_
