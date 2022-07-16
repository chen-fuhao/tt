#include <stdio.h>
#include <stdlib.h>

#include "my-log/log.h"

/**
 * return 1:fail, 0:success
 */
static int mydemo(){
    function_in_log
    int ret = 1;
    char *buffer = NULL;
    do{
        if(!(buffer = malloc(1000))){
            MY_ERROR("space is not enough!");
            function_break_ret_log
        }
        ret = 0;
    }while(0);
    SAFE_FREE(buffer);
    function_return_log(ret)
}

int main(void)
{
    MY_ERROR("info %s", "error");
    MY_HEX("data", 4, "info %s", "hex");
    MY_DEBUG("info %s", "debug");
    MY_INFO("info test");
    int ret = 0;
    ret = should_ok(mydemo(), "fun should return %s", "success");
    ret = should_fail(mydemo(), "fun should return %s", "fail");
    should_no_judge(mydemo(), "do need judge it's return code");
    return 0;
}