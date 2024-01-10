#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lexer.h"
#include "includes.h"
#include "reporter.h"

bool is_number(const char character)
{
    return character >= '0' && character <= '9' ? true : false;
}

void token_push(TokensManager *tokens_manager, const TokenType t_type, const double t_value)
{
    // Allocate memory to new token
    ++tokens_manager->capacity;

    tokens_manager->tokens = realloc(tokens_manager->tokens, (tokens_manager->capacity * sizeof(Token)));
    if (tokens_manager->tokens == NULL) {
        error_report(ERR_INSUFICIENT_MEMORY, NULL);
    }

    // Push token into manager
    Token new_operation = {
        .type = t_type,
        .value = t_value,
    };

    memcpy(&(tokens_manager->tokens[tokens_manager->capacity - 1]), &new_operation, sizeof(Token));
}

void tokenize_input(TokensManager *tokens_manager)
{
    for (uint16_t current_pos = 0; current_pos < strlen(tokens_manager->text); ++current_pos) {
        uint16_t t_length = 0;
        uint32_t text_l = strlen(tokens_manager->text) - 1;
        char current_char = tokens_manager->text[current_pos];

        TokenType t_type = TOKEN_NONE;

        if (is_number(current_char)) {
            while (is_number(current_char) || current_char == '.') {
                ++t_length;
                ++current_pos;
                current_char = tokens_manager->text[current_pos];
            }
            t_type = TOKEN_NUMBER;

            char *t_value_str = malloc(sizeof(*t_value_str) * t_length + 1);
            if (t_value_str == NULL) {
                error_report(ERR_INSUFICIENT_MEMORY, NULL);
            }

            memset(t_value_str, 0, sizeof(*t_value_str) * t_length + 1);
            strncpy(t_value_str, &tokens_manager->text[current_pos - t_length], t_length);

            double t_value = atof(t_value_str);

            // Avoid jumping 1 character after reading some number,
            // removing this line can lead to a bug
            --current_pos;
            token_push(tokens_manager, t_type, t_value);

            free(t_value_str);
            t_value_str = NULL;

            continue;
        }

        switch (current_char)
        {
            case ' ':
                continue;
                break;
            case '+':
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_ADD;
                break;
            case '-':
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_SUB;
                break;
            case '*':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_MUL;
                break;
            case '/':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_DIV;
                break;
            case '^':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_POW;
                break;
            case '(':
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_L_PARENTHESES;
                break;
            case ')':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_R_PARENTHESES;
                break;
            case '[':
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_L_BRACKET;
                break;
            case ']':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_R_BRACKET;
                break;
            case '{':
                if (current_pos == text_l) {
                    error_report(ERR_INVALID_LAST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_L_BRACE;
                break;
            case '}':
                if (current_pos == 0) {
                    error_report(ERR_INVALID_FIRST_CHAR, &current_char);
                }

                ++t_length;
                t_type = TOKEN_R_BRACE;
                break;
            default:
                error_report(ERR_INVALID_CHAR, &current_char);
                break;
        }

        token_push(tokens_manager, t_type, 0.0);
    }
}
