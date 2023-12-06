#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "includes.h"
#include "lexer.h"
#include "tests.h"

uint8_t test_simple_formula(void)
{
    const TokenType expected_types[] = {
        TOKEN_SUB, TOKEN_NUMBER, TOKEN_ADD, TOKEN_NUMBER, TOKEN_MUL,
        TOKEN_NUMBER, TOKEN_DIV, TOKEN_NUMBER, TOKEN_POW, TOKEN_NUMBER
    };
    const uint8_t expected_lengths[] = {1, 3, 1, 1, 1, 1, 1, 1, 1, 2};
    const char *expected_texts[] = {"-", "200", "+", "3", "*", "4", "/", "2", "^", "33"};
    uint8_t exit_status = 0;

    TokensManager tokens_manager = {
        .tokens = NULL,
        .capacity = 0,
        .text = "-200 + 3 *4 / 2^33",
    };

    // Test 1 - Check for correct capacity, values and types for each type of operation
    tokenize_input(&tokens_manager);

    // Check for correct capacity and NULL tokens
    ++exit_status;
    if (tokens_manager.tokens == NULL || tokens_manager.capacity != 10) return exit_status;

    // Check types
    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].type != expected_types[i]) return exit_status;
    }

    // Check lengths
    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].length != expected_lengths[i]) return  exit_status;
    }

    // Check texts 
    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        const Token *token = &tokens_manager.tokens[i];
        const char *expected_text = expected_texts[i];
        ++exit_status;
        if (strncmp(&tokens_manager.text[token->position], expected_text, token->length) != 0) return exit_status;
    }

    return 0;
}

// This function should be used as a wrapper
// of smaller functions with specific tests
bool tests_run(void) {
    uint8_t exit_code = 0; // If you make a test with more than 256 checks you need help

    LogInfo("%sInitializing tests...%s\n", BHGRN, CRESET);

    LogInfo("Test 1...");
    if ((exit_code = test_simple_formula())) {
        LogInfo("\rTest 1 - %sFailed!%s (code %u)\n ", BHRED, CRESET, exit_code);
    } else {
        LogInfo("\rTest 1 - %sSucceeded!%s\n", BHGRN, CRESET);
    }

    return 0;
}
