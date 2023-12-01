#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#include "includes.h"
#include "lexer.h"

void usage_print(char *program)
{
    char *program_name = basename(program);

    LogInfo("Usage: %s <formula>\n", program_name);
    exit(EXIT_SUCCESS);
}

// This function is intended to be used only for debugging purposes
void tokens_print(TokensManager *tokens_manager)
{
    char *tok_text = NULL;

    LogInfo("Input: %s\n", tokens_manager->tokens->text);

    for (uint16_t i = 0; i < tokens_manager->capacity; i++) {
        // This line could scare a lil bit, but it's just copying
        // the content from the text to 'tok_text', using the given position by the token
        // itself.
        tok_text = strndup(&tokens_manager->tokens[i].text[tokens_manager->tokens[i].position], tokens_manager->tokens[i].length);
        if (tok_text == NULL) {
            LogExit("Could not allocate memory to token text\n");
        }

        LogInfo("Token %u::(text: %s, len: %u, pos: %u, type: %i)\n", 
                i, 
                tok_text, 
                tokens_manager->tokens[i].length, 
                tokens_manager->tokens[i].position, 
                tokens_manager->tokens[i].type);

        free(tok_text);
        tok_text = NULL;
    }
}

void calculate_formula(char *formula)
{
    TokensManager tokens_manager = {0};

    tokenize_input(&tokens_manager, formula);

    tokens_print(&tokens_manager);
}

int main(int argc, char **argv)
{
    switch (argc)
    {
        case 1:
            usage_print(argv[0]);
            break;
        case 2:
            calculate_formula(argv[1]);
            break;
        default:
            // TODO: Handle multiple arguments input, when multiple args were passed it should
            // concatenate them all in a single 'String' and pass them into 'calculate_formula'
            LogExit("Multiple arguments not handled yet!\n");
            break;
    }

    return 0;
}
