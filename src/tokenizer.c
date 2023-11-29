#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "includes.h"

void operation_push(OperationsManager *operations_manager, int64_t value, OperationType operation, bool needs_new_operation)
{
    Operation new_operation = {
        .value = value,
        .operation = operation,
    };

    memcpy(&(operations_manager->operations[operations_manager->capacity - 1]), &new_operation, sizeof(Operation));

    if (needs_new_operation) {
        ++operations_manager->capacity;

        operations_manager->operations = realloc(operations_manager->operations, (operations_manager->capacity * sizeof(Operation)));
        if (operations_manager->operations == NULL) {
            LogExit("Could not allocate memory to store operations!\n");
        }
    }
}

void tokenize_and_parse_input(OperationsManager *operations_manager, char *formula)
{
    // Creates a copy of the original formula to avoid errors due to
    // 'strtok' function manipulating the original formula when parsing
    char formula_cpy[strlen(formula) - 1];
    strncpy(formula_cpy, formula, strlen(formula));

    char *token = NULL;
    char *base_ptr = formula;
    char delimiter = formula_cpy[0];
    uint8_t operation_type = OPERATION_NONE;

    // TODO: Implement a better parser which supports 'priority' into each operation
    //       taking into account for '{[()]}' symbols
    while ((token = strtok_r(base_ptr, "+-*/", &base_ptr))) {
        int64_t operation_value = atoi(token);
        bool next_operation_exists = false;
        operation_type = OPERATION_NONE;

        if (*base_ptr) {
            delimiter = formula_cpy[(base_ptr - formula) - 1];
            switch (delimiter)
            {
                case '+':
                    operation_type = OPERATION_ADD;
                    break;
                case '-':
                    operation_type = OPERATION_SUBTRACT;
                    break;
                case '*':
                    operation_type = OPERATION_MULTIPLY;
                    break;
                case '/':
                    operation_type = OPERATION_DIVIDE;
                    break;
                case '^':
                    operation_type = OPERATION_POWER;
                    break;
                default:
                    LogExit("Unknown operator has been taken\n");
                    break;
            }

            next_operation_exists = true;
        }

        operation_push(operations_manager, operation_value, operation_type, next_operation_exists);
    }
}
