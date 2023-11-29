#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include <stdint.h>

#define LogInfo(...) fprintf(stdout, "[+] "); \
        fprintf(stdout, __VA_ARGS__)
#define LogError(...) fprintf(stderr, "[!] "); \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE)

#define OPERATIONS_SYMBOLS '+-*\/^'

typedef struct {
        int64_t value;
        char operation;
} Token;

#endif // _INCLUDES_H_
