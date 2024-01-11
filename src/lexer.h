#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdint.h>
#include <stdbool.h>

#define OPERATIONS_SYMBOLS "+-*/^{}[]()"

typedef enum {
    // Others
    TOKEN_NONE = 0,
    TOKEN_NUMBER = 1,

    // Operations
    TOKEN_ADD = 2,
    TOKEN_SUB = 3,
    TOKEN_MUL = 4,
    TOKEN_DIV = 5,
    TOKEN_POW = 6,

    // Symbols
    TOKEN_L_BRACE = 7,
    TOKEN_R_BRACE = 7,
    TOKEN_L_BRACKET = 8,
    TOKEN_R_BRACKET = 8,
    TOKEN_L_PARENTHESES = 9,
    TOKEN_R_PARENTHESES = 9,
} TokenType;

typedef struct {
    uint16_t length;
    uint16_t position;
    TokenType type;
    uint16_t priority;
    double value;
} Token;

typedef struct {
    Token *tokens;
    uint16_t capacity;
    const char *text;
} TokensManager;

void token_push(TokensManager *tokens_manager, const TokenType t_type, const uint16_t t_priority, const double t_value);
void tokenize_input(TokensManager *tokens_manager);

#endif // _TOKENIZER_H_
