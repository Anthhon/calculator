#ifndef REPORTER_H_
#define REPORTER_H_

typedef enum {
    ERR_INVALID_CHAR,
    ERR_INVALID_FIRST_CHAR,
    ERR_INVALID_LAST_CHAR,
    ERR_INSUFICIENT_MEMORY,
    ERR_NOT_FOUND_TOKEN_VALUE,
    ERR_COULD_NOT_TOKENIZE_INPUT,
    ERR_COULD_NOT_PARSE_TREE,
    ERR_MISSING_SYMBOL,
} ErrorType;

void error_report(const ErrorType t_error, const char *text);

#endif // REPORTER_H_
