#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "includes.h"
#include "lexer.h"

void replace_tokens(TokensManager *tokens_manager, uint16_t index, uint16_t offset)
{
    // 120, +, 120, NULL, NULL, +, 10
    // Turns into
    // 120, +, 120, +, 10
    for (uint16_t i = index; i < tokens_manager->capacity; ++i) {
        Token actual_token = tokens_manager->tokens[i];
        if (actual_token.type != TOKEN_NONE && i > 1) {
            tokens_manager->tokens[i - offset] = actual_token;
        }
    }
    tokens_manager->capacity -= offset;
}

TokenType get_greater_type(TokensManager *tokens_manager)
{
    TokenType greater_type = TOKEN_ADD;
    for (int i = 0; i < tokens_manager->capacity; ++i) {
        if (tokens_manager->tokens[i].type > greater_type) {
            greater_type = tokens_manager->tokens[i].type;
        }
    }

    return greater_type;
}

double interpret_tree(TokensManager *tokens_manager)
{
    if (tokens_manager->capacity == 1) {
        return tokens_manager->tokens[0].value;
    }

    TokenType greater_type = get_greater_type(tokens_manager);

    for (int i = 0; i < tokens_manager->capacity; ++i) {
        Token actual_token = tokens_manager->tokens[i];
        if (actual_token.type >= greater_type) {
            Token prev_token = tokens_manager->tokens[i - 1];
            Token next_token = tokens_manager->tokens[i + 1];

            double f_val = prev_token.value;
            double s_val = next_token.value;
            double result = 0.0;

            switch (actual_token.type) {
                case TOKEN_ADD:
                    result = f_val + s_val;
                    break;
                case TOKEN_SUB:
                    result = f_val - s_val;
                    break;
                case TOKEN_MUL:
                    result = f_val * s_val;
                    break;
                case TOKEN_DIV:
                    result = f_val / s_val;
                    break;
                case TOKEN_POW:
                    result = powf(f_val, s_val);
                    break;
                default:
                    continue;
                    break;
            }

            tokens_manager->tokens[i - 1].value = result;
            tokens_manager->tokens[i].type = TOKEN_NONE;
            tokens_manager->tokens[i + 1].type = TOKEN_NONE;

            replace_tokens(tokens_manager, i, 2);
            break;
        }
    }
    return interpret_tree(tokens_manager);
}
