#ifndef MAIN_H_
#define MAIN_H_

#include "lexer.h"

int main(int argc, char **argv);
double calculate_formula(char *formula);
void usage_print(char *program);
void tokens_print(TokensManager *tokens_manager);

#endif // MAIN_H_
