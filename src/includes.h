#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include <stdint.h>

#define LogInfo(...) fprintf(stdout, "[+] "); \
    fprintf(stdout, __VA_ARGS__)
#define LogExit(...) fprintf(stderr, "[!] "); \
    fprintf(stderr, __VA_ARGS__); \
    exit(EXIT_FAILURE)

#define OPERATIONS_SYMBOLS "+-*/^"

typedef enum {
    OPERATION_ADD,
    OPERATION_SUBTRACT,
    OPERATION_MULTIPLY,
    OPERATION_DIVIDE,
    OPERATION_POWER,
    OPERATION_NONE,
} OperationType;

typedef struct {
    int64_t value;
    OperationType operation;
} Operation;

typedef struct {
    Operation *operations;
    uint16_t capacity;
} OperationsManager;

#endif // _INCLUDES_H_
