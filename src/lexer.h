#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdint.h>
#include <stdbool.h>

#define OPERATIONS_SYMBOLS "+-*/^{}[]()"

typedef enum {
    // Others
    TOKEN_NONE = 0,
    TOKEN_NUMBER,

    // Operations
    TOKEN_ADD, TOKEN_SUB,
    TOKEN_MUL, TOKEN_DIV,
    TOKEN_POW,

    // Symbols
    TOKEN_L_BRACE, TOKEN_R_BRACE,
    TOKEN_L_BRACKET, TOKEN_R_BRACKET,
    TOKEN_L_PARENTHESES, TOKEN_R_PARENTHESES,
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
