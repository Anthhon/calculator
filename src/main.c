#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include <math.h>

#include "includes.h"
#include "tokenizer.h"

void usage_print(char *program)
{
    char *program_name = basename(program);

    LogInfo("Usage: %s <formula>\n", program_name);
    exit(EXIT_SUCCESS);
}

void calculate_formula(char *formula)
{
    OperationsManager operations_manager = {0};

    operations_manager.capacity = 1;
    operations_manager.operations = realloc(operations_manager.operations, sizeof(Operation));
    if (operations_manager.operations == NULL) {
        LogExit("Could not allocate memory to store operations!\n");
    }

    tokenize_and_parse_input(&operations_manager, formula);

    int64_t accumulator = operations_manager.operations[0].value;
    for (int i = 0; i < operations_manager.capacity; ++i) {
        int64_t next_value = operations_manager.operations[i + 1].value;
        OperationType operation = operations_manager.operations[i].operation;

        switch (operation) {
            case OPERATION_ADD:
                accumulator += next_value;
                break;
            case OPERATION_SUBTRACT:
                accumulator -= next_value;
                break;
            case OPERATION_MULTIPLY:
                accumulator *= next_value;
                break;
            case OPERATION_DIVIDE:
                accumulator /= next_value;
                break;
            case OPERATION_POWER:
                accumulator = pow(accumulator, next_value);
                break;
            default:
                break;
        }
    }

    LogInfo("%li\n", accumulator);

    free(operations_manager.operations);
    operations_manager.operations = NULL;
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
            LogExit("Invalid input provided\n");
            break;
    }

    return 0;
}
