#ifndef REPORTER_H_
#define REPORTER_H_

typedef enum {
    ERR_INVALID_CHAR,
    ERR_INVALID_FIRST_CHAR,
    ERR_INSUFICIENT_MEMORY,
} ErrorType;

void error_report(const ErrorType t_error, const char *text);

#endif // REPORTER_H_
