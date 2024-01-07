#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

#include "includes.h"
#include "main.h"
#include "lexer.h"
#include "tests.h"

static uint8_t test_num = 0;

uint8_t test_lexer_1(void)
{
    const TokenType expected_types[] = {
        TOKEN_SUB, TOKEN_NUMBER, TOKEN_ADD, TOKEN_NUMBER, TOKEN_MUL,
        TOKEN_NUMBER, TOKEN_DIV, TOKEN_NUMBER, TOKEN_POW, TOKEN_NUMBER
    };
    const double expected_values[] = { 0.0, 200.0, 0.0, 3.0, 0.0, 4.0, 0.0, 2.0, 0.0, 33.0 };
    uint8_t exit_status = 0;

    TokensManager tokens_manager = {
        .tokens = NULL,
        .capacity = 0,
        .text = "-200 + 3 *4 / 2^33",
    };

    tokenize_input(&tokens_manager);

    ++exit_status;
    if (tokens_manager.tokens == NULL || tokens_manager.capacity != 10) return exit_status;

    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].type != expected_types[i]) return exit_status;
    }

    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].value != expected_values[i]) return exit_status;
    }

    return 0;
}

uint8_t test_lexer_2(void)
{
    const TokenType expected_types[] = {
        TOKEN_NUMBER, TOKEN_ADD, TOKEN_NUMBER, TOKEN_MUL, 
        TOKEN_NUMBER, TOKEN_POW, TOKEN_NUMBER, TOKEN_DIV, TOKEN_NUMBER
    };
    const double expected_values[] = { 120.0, 0.0, 120.0, 0.0, 10.0, 0.0, 2.0, 0.0, 10.0 };
    uint8_t exit_status = 0;

    TokensManager tokens_manager = {
        .tokens = NULL,
        .capacity = 0,
        .text = "120 +120* 10^2/ 10",
    };

    tokenize_input(&tokens_manager);

    ++exit_status;
    if (tokens_manager.tokens == NULL || tokens_manager.capacity != 9) return exit_status;

    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].type != expected_types[i]) return exit_status;
    }

    for (size_t i = 0; i < tokens_manager.capacity; ++i) {
        ++exit_status;
        if (tokens_manager.tokens[i].value != expected_values[i]) return exit_status;
    }

    return 0;
}

void test_formulas(void)
{
    LogInfo("Test %u...", ++test_num);
    if (calculate_formula("420+69") == 489.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", test_num, BHRED, CRESET);
    }

    if (calculate_formula("1000 -333") == 667.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", ++test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", ++test_num, BHRED, CRESET);
    }

    if (calculate_formula("25*4 ") == 100.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", ++test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", ++test_num, BHRED, CRESET);
    }

    if (calculate_formula(" 144/12") == 12.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", ++test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", ++test_num, BHRED, CRESET);
    }

    if (calculate_formula("2^6") == 64.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", ++test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", ++test_num, BHRED, CRESET);
    }

    if (calculate_formula("3*5+10^2/2-4") == 61.0) {
        LogInfo("\rTest %u - %sSucceeded!%s\n", ++test_num, BHGRN, CRESET);
    } else {
        LogInfo("\rTest %u - %sFailed!%s\n ", ++test_num, BHRED, CRESET);
    }
}

// The 'exit_status' variable within each test function serves as an indicator of 
// the test's progress and pinpointing potential error locations within the lexer 
// implementation.
//
// The value of 'exit_status' provides a contextual clue about the step or condition 
// that didn't match the expected outcome, the exit_status increments at distinct 
// validation points (e.g., capacity check, type verification, value comparison).

bool tests_run(void) {
    uint8_t exit_code = 0; // If you make a test with more than 256 checks you need help

    LogInfo("%sInitializing tests...%s\n", BHGRN, CRESET);

    LogInfo("Test %u...", ++test_num);
    if ((exit_code = test_lexer_1())) {
        LogInfo("\rTest %u - %sFailed!%s (code %u)\n ", test_num, BHRED, CRESET, exit_code);
    } else {
        LogInfo("\rTest %u - %sSucceeded!%s\n", test_num, BHGRN, CRESET);
    }

    LogInfo("Test %u...", ++test_num);
    if ((exit_code = test_lexer_2())) {
        LogInfo("\rTest %u - %sFailed!%s (code %u)\n ", test_num, BHRED, CRESET, exit_code);
    } else {
        LogInfo("\rTest %u - %sSucceeded!%s\n", test_num, BHGRN, CRESET);
    }

    test_formulas();

    return 0;
}
