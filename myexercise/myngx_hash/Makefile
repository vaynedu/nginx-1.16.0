# makefile用来编译自己写的nginx代码，以此来熟悉nginx的源码

# makefile按照nginx的makefile风格来写

# https://blog.csdn.net/livelylittlefish/article/details/6636229

# ROOTPATH  = $(shell pwd)

CUR_PATH  =  $(shell pwd)

NGX_ROOTPATH = /data/lotluck/nginx-1.16.0
CC = cc
#CFLAGS =  -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
CFLAGS =  -g -O0
CPP = cc -E
LINK = $(CC)

TARGETS = myngx_hash
TARGETS_C_FILE = $(TARGETS).c


CORE_INCS = -I $(NGX_ROOTPATH)/src/core \
			-I $(NGX_ROOTPATH)/src/event \
			-I $(NGX_ROOTPATH)/src/event/modules \
			-I $(NGX_ROOTPATH)/src/os/unix \
			-I $(NGX_ROOTPATH)/objs 
		
MY_INCS = -I $(NGX_ROOTPATH)/mycommonlib/C	
			
NGX_PALLOC = $(NGX_ROOTPATH)/objs/src/core/ngx_palloc.o
NGX_STRING = $(NGX_ROOTPATH)/objs/src/core/ngx_string.o
NGX_ALLOC = $(NGX_ROOTPATH)/objs/src/os/unix/ngx_alloc.o
NGX_ARRAY = $(NGX_ROOTPATH)/objs/src/core/ngx_array.o
NGX_HASH = $(NGX_ROOTPATH)/objs/src/core/ngx_hash.o


all:$(TARGETS)
	
$(TARGETS):$(TARGETS_C_FILE)
	$(CC) $(CFLAGS) $(CORE_INCS) $(MY_INCS) $(NGX_PALLOC) $(NGX_STRING) $(NGX_ALLOC) $(NGX_ARRAY) $(NGX_HASH) $^ -o $@

clean:
	@echo "please rm"



