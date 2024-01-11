#include "interpreter.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

//#define DEBUG

#include "includes.h"
#include "reporter.h"
#include "lexer.h"
#include "tests.h"

// DEBUG CODE ///////////////////////////////////////////////////////////////
#ifdef DEBUG

void tokens_print(TokensManager *tokens_manager)
{
    char *tok_text = NULL;

    printf("Tokens {\n");
    for (uint16_t i = 0; i < tokens_manager->capacity; i++) {
        // This line could scare a lil bit, but it's just copying
        // the content from the text to 'tok_text', using the given position by the token
        // itself.
        tok_text = strndup(&tokens_manager->text[tokens_manager->tokens[i].position], tokens_manager->tokens[i].length);
        if (tok_text == NULL) {
            error_report(ERR_INSUFICIENT_MEMORY, NULL);
        }

        printf("\tToken %u::(type: %i, priority: %i, value: %f)\n", 
                i, 
                tokens_manager->tokens[i].type,
                tokens_manager->tokens[i].priority,
                tokens_manager->tokens[i].value);

        free(tok_text);
        tok_text = NULL;
    }
    printf("}\n");
}

#endif
/////////////////////////////////////////////////////////////////////////////

void usage_print(char *program)
{
    char *program_name = basename(program);

    LogInfo("Usage: %s <formula>\n", program_name);
    exit(EXIT_SUCCESS);
}

double calculate_formula(char *formula)
{
    TokensManager tokens_manager = {
        .tokens = NULL,
        .capacity = 0,
        .text = formula,
    };

    tokenize_input(&tokens_manager);
    if (tokens_manager.tokens == NULL) {
        error_report(ERR_COULD_NOT_TOKENIZE_INPUT, NULL);
    }

    _Debug({
            tokens_print(&tokens_manager);
    });

    double result = interpret_tree(&tokens_manager);

    free(tokens_manager.tokens);
    tokens_manager.tokens = NULL;

    return result;
}

int main(int argc, char **argv)
{
    switch (argc) {
        case 1:
            usage_print(argv[0]);
            break;
        case 2:
            if (strncmp(argv[1], "-t", 2) == 0 || strncmp(argv[1], "--test", 6) == 0) {
                return tests_run();
            }

            double result = calculate_formula(argv[1]);
            fprintf(stdout, "%2.3f\n", result);

            break;
        default:
            // Concatenate all arguments into a single string
            {
                size_t total_length = 0;
                for (int i = 1; i < argc; ++i) {
                    total_length += strlen(argv[i]);
                    ++total_length;
                }

                char *formula = malloc(sizeof(*formula) * (total_length + 1));
                if (formula == NULL) {
                    error_report(ERR_INSUFICIENT_MEMORY, NULL);
                    return 1;
                }

                formula[total_length] = '\0';

                for (int i = 1; i < argc; ++i) {
                    strcat(formula, argv[i]);
                }

                double result = calculate_formula(formula);
                fprintf(stdout, "%2.3f\n", result);

                free(formula);
            }
            break;
    }

    return 0;
}
