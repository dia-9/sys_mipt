//#ifndef DEBUG_H_INCLUDED
//#define DEBUG_H_INCLUDED
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

// FONT MACRO
#define CL_FT_BLACK             "\x1b[30m"
#define CL_FT_BLUE              "\x1b[34m"
#define CL_FT_BROWN             "\x1b[33m"
#define CL_FT_GRAY              "\x1b[37m"
#define CL_FT_GREEN             "\x1b[32m"
#define CL_FT_MAGENTA			"\x1b[36m"
#define CL_FT_PURPLE			"\x1b[35m"
#define CL_FT_RED               "\x1b[31m"

#define CL_BG_BLACK             "\x1b[40m"
#define CL_BG_BLUE              "\x1b[44m"
#define CL_BG_BROWN             "\x1b[43m"
#define CL_BG_GRAY				"\x1b[47m"
#define CL_BG_GREEN             "\x1b[42m"
#define CL_BG_MAGENTA			"\x1b[46m"
#define CL_BG_PURPLE			"\x1b[45m"
#define CL_BG_RED               "\x1b[41m"

#define TY_FT_BOLD				"\x1b[1m"
//#define TY_FT_BOLD			"\x1b[5m"
#define TY_FT_DEFAULT			"\x1b[0m"
#define TY_FT_HBOLD				"\x1b[2m"
#define TY_FT_REVERSE			"\x1b[7m"
#define TY_FT_UNDERLINE			"\x1b[4m"

#define SET_FONT(X) printf(X)
#define printf_color(color, ...) \
	{ \
		SET_FONT(color); \
		printf(__VA_ARGS__); \
		SET_FONT(TY_FT_DEFAULT); \
	}


// LOG MACRO
#if defined(DEBUG)
    #define LOG(format, ...) \
    { \
        char __tb[101]; \
        time_t t = time(NULL); \
        struct tm* tmp = localtime(&t); \
        strftime(__tb, 100, "%d.%m.%Y %H:%M:%S ", tmp); \
        const char* __filename__ = __FILE__; \
        char* __iterator__ = (char*)__filename__ + strlen(__filename__) - 1; \
        int __count__slash__ = 0; \
                while (__iterator__ > __filename__ && __count__slash__ < 2) { \
                    if (*__iterator__ == '/') \
                        __count__slash__ ++; \
                    if (__count__slash__ != 2) \
                        __iterator__--; \
                } \
                fprintf(stderr, "%s [pid=%d] [%s:%d] ", __tb, (int)getpid(), __iterator__, __LINE__); \
        fprintf(stderr, format, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
        fflush(stderr); \
    }
#else
    #define LOG(format, ...) ;
#endif

// PERROR MACRO
#define PERROR(format, ...) \
	{ \
		char __tb[101]; \
		time_t t = time(NULL); \
		struct tm* tmp = localtime(&t); \
		strftime(__tb, 100, "%d.%m.%Y %H:%M:%S ", tmp); \
		const char* __filename__ = __FILE__; \
                char* __iterator__ = (char*)__filename__ + strlen(__filename__) - 1; \
                int __count__slash__ = 0; \
                while (__iterator__ > __filename__ && __count__slash__ < 2) { \
                    if (*__iterator__ == '/') \
                        __count__slash__ ++; \
                    if (__count__slash__ != 2) \
                        __iterator__--; \
                } \
                fprintf(stderr, "%s [pid=%d] [%s:%d] ", __tb, (int)getpid(), __iterator__, __LINE__); \
		SET_FONT(CL_FT_RED); \
		fprintf(stderr, " ERROR! "); \
		SET_FONT(TY_FT_DEFAULT); \
		fprintf(stderr, format, ##__VA_ARGS__); \
		if (errno != 0) \
			fprintf(stderr, " (%s)\n", strerror(errno)); \
		else \
			fprintf(stderr, "\n"); \
		fflush(stderr); \
	}

//#endif // DEBUG_H_INCLUDED
