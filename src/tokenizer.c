#include <stdio.h>
#include <string.h>

#include "includes.h"

void tokenize_input(char *formula)
{
        char formula_cpy[strlen(formula) - 1];
        strncpy(formula_cpy, formula, strlen(formula));

        char *token = NULL;
        char *base_ptr = formula;

        size_t node_count = 1;

        LogInfo("Parsing:: %s\n", formula);
        while ((token = strtok_r(base_ptr, "+-*/", &base_ptr))) {
                LogInfo("-- %u Node --\n", node_count);
                LogInfo("val::%s\n", token);

                char delimiter = formula_cpy[(base_ptr - formula) - 1];
                if (*base_ptr) {
                        LogInfo("oper:: %c\n", delimiter);
                        LogInfo("nval::%s\n", base_ptr);
                }

                ++node_count;
        }
}
