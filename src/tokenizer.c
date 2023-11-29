#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "includes.h"

OperationsManager operations_manager = {0};

void operation_push(int64_t value, uint8_t operation, bool need_new_oper)
{
    Operation new_operation = {
        .value = value,
        .operation = operation,
    };

    memcpy(&(operations_manager.operations[operations_manager.capacity - 1]), &new_operation, sizeof(Operation));

    if (need_new_oper) {
        ++operations_manager.capacity;

        operations_manager.operations = realloc(operations_manager.operations, (operations_manager.capacity * sizeof(Operation)));
        if (operations_manager.operations == NULL) {
            LogExit("Could not allocate memory to store operation!");
        }
    }

}

void tokenize_input(char *formula)
{
    // Creates a copy of the original formula to avoid errors due to
    // 'strtok' function manipulating the original formula when parsing
    char formula_cpy[strlen(formula) - 1];
    strncpy(formula_cpy, formula, strlen(formula));

    char *token = NULL;
    char *base_ptr = formula;
    char delimiter = formula_cpy[0];
    uint8_t operation_type = OPER_NONE;

    operations_manager.capacity = 1;
    operations_manager.operations = realloc(operations_manager.operations, sizeof(Operation));

    // TODO: Implement a better parser which supports 'priority' into each operation
    //       taking into account for '{[()]}' symbols
    while ((token = strtok_r(base_ptr, "+-*/", &base_ptr))) {
        int64_t operation_value = atoi(token);
        bool next_operation_exists = false;
        operation_type = OPER_NONE;

        if (*base_ptr) {
            delimiter = formula_cpy[(base_ptr - formula) - 1];
            switch (delimiter)
            {
                case '+':
                    operation_type = OPER_SUM;
                    break;
                case '-':
                    operation_type = OPER_MIN;
                    break;
                case '*':
                    operation_type = OPER_MUL;
                    break;
                case '/':
                    operation_type = OPER_DIV;
                    break;
                case '^':
                    operation_type = OPER_POW;
                    break;
                default:
                    operation_type = OPER_NONE;
                    break;
            }

            next_operation_exists = true;
        }

        operation_push(operation_value, operation_type, next_operation_exists);
    }
}
