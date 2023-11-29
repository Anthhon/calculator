#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>

#include "includes.h"
#include "tokenizer.h"

void usage_print(char *program)
{
    char *program_name = basename(program);

    LogInfo("Usage: %s <formula>\n", program_name);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    switch (argc)
    {
        case 1:
            usage_print(argv[0]);
            break;
        case 2:
            tokenize_input(argv[1]);
            break;
        default:
            LogExit("Invalid input provided\n");
            break;
    }

    return 0;
}
