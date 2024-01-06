#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#define LogInfo(...) fprintf(stdout, "[+] "); \
    fprintf(stdout, __VA_ARGS__)
#define LogExit(...) fprintf(stderr, "[!] "); \
    fprintf(stderr, __VA_ARGS__); \
    exit(EXIT_FAILURE)

#ifdef DEBUG
#define _Debug(code) \
    do { \
        code \
    } while(0)
#else
#define _Debug(code)
#endif

#endif // _INCLUDES_H_
