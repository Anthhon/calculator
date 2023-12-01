#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "includes.h"
#include "lexer.h"

bool is_whitespace(const char character)
{
    return character == ' ' ? true : false;
}

bool is_number(const char character)
{
    return character >= '0' && character <= '9' ? true : false;
}

void token_push(TokensManager *tokens_manager, const char *src, const uint16_t t_length, const uint16_t t_position, const TokenType t_type)
{
    // Allocate memory to new token
    ++tokens_manager->capacity;

    tokens_manager->tokens = realloc(tokens_manager->tokens, (tokens_manager->capacity * sizeof(Token)));
    if (tokens_manager->tokens == NULL) {
        LogExit("Could not allocate memory to store tokens!\n");
    }

    // Push token into manager
    Token new_operation = {
        .text = src,
        .length = t_length,
        .position = t_position,
        .type = t_type,
    };

    memcpy(&(tokens_manager->tokens[tokens_manager->capacity - 1]), &new_operation, sizeof(Token));
}

void tokenize_input(TokensManager *tokens_manager, const char *input)
{
    for (uint16_t current_pos = 0; current_pos < strlen(input); ++current_pos) {
        uint16_t t_length = 0;
        uint16_t t_position = current_pos;
        TokenType t_type = TOKEN_NONE;

        char current_char = input[current_pos];
        if (is_whitespace(current_char)) {
            continue;
        }
        else if (is_number(current_char)) {
            while (is_number(current_char)) {
                ++t_length;
                ++current_pos;
                current_char = input[current_pos];
            }
            t_type = TOKEN_NUMBER;

            // Avoid jumping 1 character after reading some number,
            // removing this line can lead to a bug
            --current_pos;
        }
        else if (current_char == TOKEN_ADD) {
            ++t_length;
            t_type = TOKEN_ADD;
        }
        else if (current_char == TOKEN_SUB) {
            ++t_length;
            t_type = TOKEN_SUB;
        }
        else if (current_char == TOKEN_MUL) {
            ++t_length;
            t_type = TOKEN_MUL;
        }
        else if (current_char == TOKEN_DIV) {
            ++t_length;
            t_type = TOKEN_DIV;
        }
        else if (current_char == TOKEN_POW) {
            ++t_length;
            t_type = TOKEN_POW;
        }

        token_push(tokens_manager, input, t_length, t_position, t_type);
    }
}
