#ifndef __MYLOG_H__
#define __MYLOG_H__

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#define SAFE_FREE(S) if((S) != NULL) {free((void*) (S)); (S)=NULL;}

#define should_no_judge(expression, ...) \
do{ \
    (expression); \
    MY_DEBUG("Assertion_no_judge '%s'", #expression); \
    MY_INFO(__VA_ARGS__); \
}while(0);

#define should_ok(expression, ...) \
({ \
	uint32_t __result = 0; \
	do{ \
		__result = (expression); \
        MY_DEBUG("Assertion_ok '%s=0x%x'", #expression, __result); \
		if(__result==0){ \
            MY_INFO(__VA_ARGS__); \
		}else{ \
            MY_ERROR(__VA_ARGS__); \
		} \
	}while(0); \
	__result; \
})

#define should_fail(expression, ...) \
({ \
	uint32_t __result = 0; \
	do{ \
		__result = (expression); \
        MY_DEBUG("Assertion_fail '%s=0x%x'", #expression, __result); \
		if(__result!=0){ \
            MY_INFO(__VA_ARGS__); \
		}else{ \
            MY_ERROR(__VA_ARGS__); \
		} \
	}while(0); \
    __result = (__result!=0)?0:(__result+1); \
	__result; \
})

typedef enum _log_level {
    LEVEL_TARCE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_ERROR
} log_level;

int log_init(int consle_log, char *file_log);

int log_exit();

void mylog(log_level logLevel, const char *file, const char *function, int line, const char *format, ...);

void myhex(log_level logLevel, const char *file, const char *function, int line, unsigned char *data, int len, const char *format, ...);

#define MY_DEBUG(...)  mylog(LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define MY_INFO(...)  mylog(LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define MY_ERROR(...)  mylog(LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define MY_HEX(data, len, ...)  myhex(LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, (unsigned char *)data, (int)len, __VA_ARGS__);
#define function_in_log  {mylog(LEVEL_TARCE, __FILE__, __FUNCTION__, __LINE__, "%s_TAG WELCOME_TO_MY_WORLD", __FUNCTION__);}
#define function_return_void_log  {mylog(LEVEL_TARCE, __FILE__, __FUNCTION__, __LINE__, "%s_TAG GOODBYE", __FUNCTION__);return;}
#define function_return_log(ret)  {mylog(LEVEL_TARCE, __FILE__, __FUNCTION__, __LINE__, "%s_TAG GOODBYE (%d, 0x%x)", __FUNCTION__, (ret), (ret));return (ret);}
#define function_break_ret_log  {mylog(LEVEL_TARCE,__FILE__, __FUNCTION__, __LINE__, "BREAK(%d)", ret);break;}

#define SLEEP(t)	sleep(t)

#include <pthread.h>
#include <stdlib.h>

typedef pthread_mutex_t *v_mutex_t;

#define v_mutex_init(m) for (;;) { m = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)); pthread_mutex_init(m, NULL); break; }

#define v_mutex_lock(m) pthread_mutex_lock(m)

#define v_mutex_unlock(m) pthread_mutex_unlock(m)

#define v_mutex_destroy(m) for (;;) { pthread_mutex_destroy(m); free(m); break; }

/*Set output foreground color*/
#define PRINT_FONT_BLA  printf("\033[30m"); //black
#define PRINT_FONT_RED  printf("\033[31m"); //red
#define PRINT_FONT_GRE  printf("\033[32m"); //green
#define PRINT_FONT_YEL  printf("\033[33m"); //yellow
#define PRINT_FONT_BLU  printf("\033[34m"); //blue
#define PRINT_FONT_PUR  printf("\033[35m"); //violet
#define PRINT_FONT_CYA  printf("\033[36m"); //Cyan
#define PRINT_FONT_WHI  printf("\033[37m"); //white
/*Set output background color*/
#define PRINT_BACK_BLA  printf("\033[40m"); //black
#define PRINT_BACK_RED  printf("\033[41m"); //red
#define PRINT_BACK_GRE  printf("\033[42m"); //green
#define PRINT_BACK_YEL  printf("\033[43m"); //yellow
#define PRINT_BACK_BLU  printf("\033[44m"); //blue
#define PRINT_BACK_PUR  printf("\033[45m"); //violet
#define PRINT_BACK_CYA  printf("\033[46m"); //Cyan
#define PRINT_BACK_WHI  printf("\033[47m"); //white
/*Output property settings*/
#define PRINT_ATTR_REC  printf("\033[0m");  //Reset the properties to the default settings
#define PRINT_ATTR_BOL  printf("\033[1m");  //Set bold 
#define PRINT_ATTR_LIG  printf("\033[2m");  //Set half brightness (simulate color of color monitor)
#define PRINT_ATTR_LIN  printf("\033[4m");  //Set underline (simulate color of color display)
#define PRINT_ATTR_GLI  printf("\033[5m");  //Set flicker 
#define PRINT_ATTR_REV  printf("\033[7m");  //Set reverse image
#define PRINT_ATTR_THI  printf("\033[22m"); //Set general density 
#define PRINT_ATTR_ULIN  printf("\033[24m");//Turn off underline
#define PRINT_ATTR_UGLI  printf("\033[25m");//Blink off
#define PRINT_ATTR_UREV  printf("\033[27m");//Turn off reverse image

#endif


