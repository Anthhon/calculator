#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdbool.h>

#include "includes.h"

void operation_push(OperationsManager *operations_manager, int64_t value, OperationType operation, bool needs_new_operation);
void tokenize_and_parse_input(OperationsManager *operations_manager, char *formula);

#endif // _TOKENIZER_H_
