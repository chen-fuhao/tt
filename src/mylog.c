#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include "my-log/log.h"

#define HIGHLIGHT "1"
#define DIM "2"
#define NOT_HIGHLIGHT "22"


static char *log_str[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "ERR"
};

static int local_console = 1;
static FILE *local_fp = NULL;
static v_mutex_t local_mutex = NULL;

int log_init(int consle_log, char *file_log)
{
    local_console = consle_log;
    if(file_log && strlen(file_log)) {
        if(access(file_log, 0) != 0) {
            local_fp = fopen(file_log, "wb");
        } else {
            local_fp = fopen(file_log, "ab");;
        }
        if(!local_fp) {
            printf("exception!!! cannot open file %s for log\n", file_log);
            return -1;
        }
    }

    v_mutex_init(local_mutex);
    if(local_mutex == NULL) {
        if(local_fp) {
            fclose(local_fp);
            local_fp = NULL;
        }
        printf("exception!!! create mutex error\n");
        return -1;
    } else {
        return 0;
    }
}

int log_exit()
{
    if(local_mutex) {
        v_mutex_lock(local_mutex);
    }
    if(local_fp) {
        fclose(local_fp);
        local_fp = NULL;
    }
    if(local_mutex) {
        v_mutex_unlock(local_mutex);
    }


    if(local_mutex) {
        v_mutex_destroy(local_mutex);
        local_mutex = NULL;
    }
    return 0;
}

static void myprint(log_level logLevel, const char *format, ...)
{
    /*color set*/
    if(logLevel == LEVEL_INFO) {
        PRINT_FONT_GRE
    } else if (logLevel == LEVEL_ERROR) {
        PRINT_FONT_RED
    } else if (logLevel == LEVEL_DEBUG) {
        PRINT_FONT_BLU
        PRINT_ATTR_LIN
    } else if(logLevel == LEVEL_TARCE) {
        PRINT_FONT_YEL
        PRINT_ATTR_LIG
    }
    char buf[4096] = {0};

    va_list list;

    int ret = -1;
    va_start(list, format);
    ret = vsnprintf(buf, 4096, format, list);
    va_end(list);

    if(local_mutex) {
        v_mutex_lock(local_mutex);
    }

    if(local_console && (ret>0)) {
        printf("%s", buf);
    }
    if(local_fp && (ret>0)) {
        fwrite(buf, 1, ret, local_fp);
    }
    if(local_mutex) {
        v_mutex_unlock(local_mutex);
    }

    /*color recovery*/
    PRINT_FONT_WHI
    PRINT_BACK_BLA
    PRINT_ATTR_REC
}

static char* mytime()
{
    static char stime[128] = {0};
    time_t seconds;
    time(&seconds);
    struct tm *t = localtime(&seconds);
    sprintf(stime, "%4d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return stime;
}


void mylog(log_level logLevel, const char *file, const char *function, int line, const char *format, ...)
{
    if(file) {}
    char buf[4090] = {0};
    size_t max = sizeof(buf);
    size_t off = 0;
    size_t rc = 0;
    va_list list;
    va_start(list, format);
    do{
        int tmp = 0;
        tmp = snprintf(buf+off, max-off, "[%s][%s][%s,%d] ", mytime(), log_str[logLevel], function, line);
        if(tmp < 0){
            break;
        }
        if((tmp<0) || (rc=tmp)>=(max-off)){
            break;
        }
        off = off+rc;

        tmp = vsnprintf(buf+off, max-off, format, list);
        if((tmp<0) || (rc=tmp)>=(max-off)){
            break;
        }
        off = off+rc;
    }while(0);
    va_end(list);

    myprint(logLevel, "%s\n", buf);
}


void myhex(log_level logLevel, const char *file, const char *function, int line, unsigned char *data, int len, const char *format, ...)
{
    if(file) {}
    char buf[1024] = {0};
    sprintf(buf, "[%s][%s][%s,%d] ", mytime(), log_str[logLevel], function, line);
    va_list list;
    va_start(list, format);
    vsprintf(buf+strlen(buf), format, list);
    va_end(list);
    sprintf(buf+strlen(buf), ": %d bytes\n", len);

#if 1
    myprint(logLevel, "%s", buf);
    int i = 0;
    for(i=0; i<len; i++) {
        myprint(logLevel, "%02x ", data[i]);
        if((i+1)%16 == 0 && (i<(len-16))) {
            myprint(logLevel, "\n");
            if(i>2048) {
                break;
            }
        }
    }
    myprint(logLevel, "\n");
#endif
}



