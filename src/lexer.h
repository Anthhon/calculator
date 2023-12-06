#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdint.h>
#include <stdbool.h>

#include "includes.h"

#define OPERATIONS_SYMBOLS "+-*/^"

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
} Token;

typedef struct {
    Token *tokens;
    uint16_t capacity;
    const char *text;
} TokensManager;

void token_push(TokensManager *tokens_manager, const uint16_t length, const uint16_t position, const TokenType type);
void tokenize_input(TokensManager *tokens_manager);

#endif // _TOKENIZER_H_
