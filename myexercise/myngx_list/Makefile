# makefile用来编译自己写的nginx代码，以此来熟悉nginx的源码

# makefile按照nginx的makefile风格来写

# ROOTPATH  = $(shell pwd)

CUR_PATH  =  $(shell pwd)

NGX_ROOTPATH = /data4/nginx-1.16.0/
CC = cc
# CFLAGS =  -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
CFLAGS =  -O  -g
CPP = cc -E
LINK = $(CC)

TARGETS = myngx_list
TARGETS_C_FILE = $(TARGETS).c


CORE_INCS = -I $(NGX_ROOTPATH)src/core \
			-I $(NGX_ROOTPATH)src/event \
			-I $(NGX_ROOTPATH)src/event/modules \
			-I $(NGX_ROOTPATH)src/os/unix \
			-I $(NGX_ROOTPATH)objs 

MY_INCS = -I $(NGX_ROOTPATH)/mycommonlib/C
			
			
NGX_PALLOC = $(NGX_ROOTPATH)/objs/src/core/ngx_palloc.o
NGX_ALLOC = $(NGX_ROOTPATH)/objs/src/os/unix/ngx_alloc.o
NGX_LIST = $(NGX_ROOTPATH)/objs/src/core/ngx_list.o


all:$(TARGETS)
	
$(TARGETS):$(TARGETS_C_FILE)
	$(CC) $(CFLAGS) $(CORE_INCS) $(MY_INCS) $(NGX_PALLOC) $(NGX_ALLOC) $(NGX_LIST) $^ -o $@

clean:
	@echo "please rm"



