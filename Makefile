#可参考

AR = /usr/bin/ar
CC = /usr/bin/gcc
INSTALL = /usr/bin/install
RM = /usr/bin/rm

LOCAL_PWD = $(shell pwd)

DIR_INC = $(LOCAL_PWD)/include
DIR_SRC = $(LOCAL_PWD)/src
DIR_OBJ = $(LOCAL_PWD)/obj
DIR_BIN = $(LOCAL_PWD)/bin
DIR_LIB = $(LOCAL_PWD)/lib

CFLAGS += -g -W
CFLAGS += -I$(DIR_INC) -I$(DIR_SRC)

all: prepare libmy_lib demo_bin

prepare:
	$(INSTALL) -d $(DIR_OBJ)
	$(INSTALL) -d $(DIR_BIN)
	$(INSTALL) -d $(DIR_LIB)

libmy_lib:$(DIR_OBJ)/mylog.o
	$(AR) crv $(DIR_LIB)/libmy-log.a $(DIR_OBJ)/mylog.o

demo_bin:$(DIR_OBJ)/mylog.o $(DIR_OBJ)/demo.o
	$(CC) $(DIR_OBJ)/mylog.o $(DIR_OBJ)/demo.o -o $(DIR_BIN)/mydemo

clean:
	$(RM) -rf $(DIR_BIN) $(DIR_LIB) $(DIR_OBJ)

$(DIR_OBJ)/mylog.o:$(DIR_SRC)/mylog.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)/demo.o:$(DIR_SRC)/demo.c
	$(CC) $(CFLAGS) -c $< -o $@
