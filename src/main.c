#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <math.h>

#include "includes.h"
#include "parser.h"
#include "lexer.h"
#include "reporter.h"
#include "tests.h"

void print_tabs(size_t quantity) {
    for (size_t i = 0; i < quantity; ++i) {
        printf("    ");
    }
}

void usage_print(char *program)
{
    char *program_name = basename(program);

    LogInfo("Usage: %s <formula>\n", program_name);
    exit(EXIT_SUCCESS);
}

size_t tree_node_id = 0;
void tree_print_rec(TreeNode *tree_root, size_t level)
{
    print_tabs(level);
    fprintf(stdout, "Node %lu {\n", ++tree_node_id);

    print_tabs(level);
    fprintf(stdout, "type: %i\n", tree_root->node_type);

    print_tabs(level);
    fprintf(stdout, "value: %i\n", tree_root->value);

    print_tabs(level);
    fprintf(stdout, "left:\n");
    if (tree_root->node_left != NULL) {
        tree_print_rec(tree_root->node_left , level + 1);
    }

    print_tabs(level);
    fprintf(stdout, "right:\n");
    if (tree_root->node_right != NULL) {
        tree_print_rec(tree_root->node_right, level + 1);
    }

    print_tabs(level);
    fprintf(stdout, "}\n");
}

void tree_print(TreeNode *tree_root) {
    tree_print_rec(tree_root, 0);
}

// This function is intended to be used only for debugging purposes
void tokens_print(TokensManager *tokens_manager)
{
    char *tok_text = NULL;

    printf("Tokens {\n");
    for (uint16_t i = 0; i < tokens_manager->capacity; i++) {
        // This line could scare a lil bit, but it's just copying
        // the content from the text to 'tok_text', using the given position by the token
        // itself.
        tok_text = strndup(&tokens_manager->tokens[i].text[tokens_manager->tokens[i].position], tokens_manager->tokens[i].length);
        if (tok_text == NULL) {
            error_report(ERR_INSUFICIENT_MEMORY, NULL);
        }

        printf("\tToken %u::(text: %s, len: %u, pos: %u, type: %i)\n", 
                i, 
                tok_text, 
                tokens_manager->tokens[i].length, 
                tokens_manager->tokens[i].position, 
                tokens_manager->tokens[i].type);

        free(tok_text);
        tok_text = NULL;
    }
    printf("}\n");
}

void calculate_formula(char *formula)
{
    TokensManager tokens_manager = {0};
    tokenize_input(&tokens_manager, formula);
    tokens_print(&tokens_manager);

    //TreeNode *tree_root = parse_tokens(&tokens_manager);

    ////tree_sort_by_type(tree_root);
    //tree_print(tree_root);
}

#define DEBUG
int main(int argc, char **argv)
{
    switch (argc)
    {
        case 1:
            usage_print(argv[0]);
            break;
        case 2:
#ifdef DEBUG
            // TODO: Implement tests module
            if (strncmp(argv[1], "-t", 2) == 0 || strncmp(argv[0], "--test", 6) == 0) {
                return tests_run();
            }
#endif

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
