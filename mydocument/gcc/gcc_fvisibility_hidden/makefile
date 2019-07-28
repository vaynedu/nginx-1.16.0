ROOTPATH = $(shell pwd)


# 1. create  /etc/ld.so.conf.d/vaynedu-test.conf
#         /usr/lib64/vaynedu
# 2. mkdir /usr/lib64/vaynedu 
#
# 3. \cp *.so /usr/lib64/vaynedu



CFLAGS  = -g 
CFLAGS += -D_ATTRIBUTE_FLAG -fvisibility=hidden

all:
	gcc -fpic -shared -o libqqmusic.so libqqmusic.c -I.  $(CFLAGS)
	gcc -fpic -shared -o libtmemusic.so libtmemusic.c -I. $(CFLAGS)
	\cp *.so /usr/lib64/vaynedu
	@ldconfig
	gcc -g -o main main.c -L. -lqqmusic -ltmemusic 
	#gcc -g -o main main.c -L. -ltmemusic -lqqmusic
	@echo -e "\n\ncompile complete\n\n"

clean:
	rm -f *.so *.o  main



