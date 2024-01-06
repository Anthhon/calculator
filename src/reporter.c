#include <stdio.h>
#include <stdlib.h>

#include "includes.h"
#include "reporter.h"

void error_report(const ErrorType t_error, const char *text)
{
    switch (t_error) {
        case ERR_INVALID_CHAR:
            LogExit("Invalid char '%c' found at expression\n", *text);
            break;
        case ERR_INVALID_FIRST_CHAR:
            LogExit("Invalid char '%c' at expression start\n", *text);
            break;
        case ERR_INVALID_LAST_CHAR:
            LogExit("Invalid char '%c' at expression start\n", *text);
            break;
        case ERR_INSUFICIENT_MEMORY:
            LogExit("Could not allocate memory to new token\n");
            break;
        case ERR_NOT_FOUND_TOKEN_VALUE:
            LogExit("Token value not found when parsing it\n");
            break;
        case ERR_COULD_NOT_TOKENIZE_INPUT:
            LogExit("Could not tokenize input\n");
            break;
        case ERR_COULD_NOT_PARSE_TREE:
            LogExit("Parsing tree was found empty after parsing process\n");
            break;
        default:
            LogExit("Congratulations, you invoked a non existent error code!\n");
            break;
    }
}
