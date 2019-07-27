ROOTPATH = $(shell pwd)


# 1. create  /etc/ld.so.conf.d/vaynedu-test.conf
#         /usr/lib64/vaynedu
# 2. mkdir /usr/lib64/vaynedu 
#
# 3. \cp *.so /usr/lib64/vaynedu



CFLAGS  += -g 
#CFLAGS += -g -fvisibility=hidden

all:
	gcc  -fpic -c -o libqqmusic.o libqqmusic.c  $(CFLAGS)
	gcc  -shared -o libqqmusic.so libqqmusic.o   $(CFLAGS)
	gcc  -fpic -c -o libtmemusic.o libtmemusic.c  $(CFLAGS)
	gcc  -shared -o libtmemusic.so libtmemusic.o $(CFLAGS)
	\cp *.so /usr/lib64/vaynedu
	@ldconfig
	gcc -g -o main main.c -L. -lqqmusic -ltmemusic
	#gcc -g -o main main.c -L. -ltmemusic -lqqmusic
	@echo -e "\n\ncompile complete\n\n"

clean:
	rm -f *.so *.o  main



