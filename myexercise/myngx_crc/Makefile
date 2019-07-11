# makefile用来编译自己写的nginx代码，以此来熟悉nginx的源码

# makefile按照nginx的makefile风格来写


# ROOTPATH  = $(shell pwd)

CUR_PATH  =  $(shell pwd)

NGX_ROOTPATH = /data4/nginx-1.16.0/
CC = cc
CFLAGS += -g -Wall -Wextra -Wformat=0
CPP = cc -E
LINK = $(CC)

TARGETS = myngx_crc32
TARGETS_C_FILE = $(TARGETS).c


CORE_INCS = -I $(NGX_ROOTPATH)src/core \
			-I $(NGX_ROOTPATH)src/event \
			-I $(NGX_ROOTPATH)src/event/modules \
			-I $(NGX_ROOTPATH)src/os/unix \
			-I $(NGX_ROOTPATH)objs 
			
			
NGX_CRC = $(NGX_ROOTPATH)/objs/src/core/ngx_crc32.o
NGX_PALLOC = $(NGX_ROOTPATH)/objs/src/core/ngx_palloc.o
NGX_ALLOC = $(NGX_ROOTPATH)/objs/src/os/unix/ngx_alloc.o


all:$(TARGETS)
	@echo -e "\n\n$(TARGETS) compile success!\n\n"	
$(TARGETS):$(TARGETS_C_FILE)
	$(CC) $(CFLAGS) $(CORE_INCS) $(NGX_CRC)  $(NGX_PALLOC) $(NGX_ALLOC) $^ -o $@

clean:
	@echo "please rm"



