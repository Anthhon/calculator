#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <stdint.h>
#include "lexer.h"

void replace_tokens(TokensManager *tokens_manager, uint16_t index, uint16_t offset);
TokenType get_greater_type(TokensManager *tokens_manager);
double interpret_tree(TokensManager *tokens_manager);

#endif // INTERPRETER_H_
