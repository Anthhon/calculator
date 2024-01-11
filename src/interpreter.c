#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "interpreter.h"
#include "includes.h"
#include "lexer.h"
#include "main.h"
#include "reporter.h"

static uint64_t greater_prior_operations = 0;
static TokenType greater_priority = TOKEN_NONE;

void tokens_replace(TokensManager *tokens_manager, uint16_t index, uint16_t offset)
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
    TokenType tmp_greater_priority = TOKEN_ADD;

    for (int i = 0; i < tokens_manager->capacity; ++i) {
        uint16_t t_priority = tokens_manager->tokens[i].type + tokens_manager->tokens[i].priority;
        if (tokens_manager->tokens[i].type > TOKEN_NUMBER) {
            if (t_priority > tmp_greater_priority) {
                greater_prior_operations = 0;
                tmp_greater_priority = t_priority;
            }
            if (t_priority == tmp_greater_priority) {
                ++greater_prior_operations;
            }
        }
    }

    return tmp_greater_priority;
}

double tokens_interpret_recursive(TokensManager *tokens_manager)
{
    if (tokens_manager->capacity == 1) {
        return tokens_manager->tokens[0].value;
    }
    if (tokens_manager->capacity == 2 && tokens_manager->tokens[0].type == TOKEN_SUB) {
        return -(tokens_manager->tokens[1].value);
    }
    if (greater_prior_operations <= 0 || greater_priority == 0) {
        greater_priority = get_greater_type(tokens_manager);
        return tokens_interpret_recursive(tokens_manager);
    }

    for (int i = 0; i < tokens_manager->capacity; ++i) {
        Token actual_token = tokens_manager->tokens[i];
        if (actual_token.type > TOKEN_NUMBER && actual_token.type + actual_token.priority >= greater_priority) {
            Token prev_token = tokens_manager->tokens[i - 1];
            Token next_token = tokens_manager->tokens[i + 1];
            --greater_prior_operations;

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

            tokens_replace(tokens_manager, i, 2);
            break;
        }
    }
    return tokens_interpret_recursive(tokens_manager);
}

void tokens_check(TokensManager *tokens_manager)
{
    for (uint16_t i = 0; i < tokens_manager->capacity; ++i) {
        Token actual_token = tokens_manager->tokens[i];

        // Handle operations with negative numbers
        if (actual_token.type == TOKEN_SUB && \
            tokens_manager->tokens[i - 1].type > TOKEN_NUMBER) {
                tokens_manager->tokens[i + 1].value *= -1;
                tokens_manager->tokens[i].type = TOKEN_NONE;

                tokens_replace(tokens_manager, i, 1);

                if (tokens_manager->tokens[i].type > TOKEN_NUMBER) {
                    error_report(ERR_EXTRA_OPERATOR, NULL);
                }
        }

        // Handle extra operators
        if (actual_token.type > TOKEN_NUMBER && tokens_manager->tokens[i - 1].type > TOKEN_NUMBER) {
                if (tokens_manager->tokens[i].type > TOKEN_NUMBER) {
                    error_report(ERR_EXTRA_OPERATOR, NULL);
                }
        }
    }
}

double tokens_interpret(TokensManager *tokens_manager) {
    tokens_check(tokens_manager);

    return tokens_interpret_recursive(tokens_manager);
}

