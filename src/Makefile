SRC=main.c inst.c mem.c util.c fileIO.c GPIO.c
EXE=vm4
EXTRACFLAGS=-lm -lrt
EXTRACFLAGS+=$(shell ./ispi.sh)
EXTRALDFLAGS=-lm -lrt
export SRC
export EXE
export EXTRACFLAGS
export EXTRALDFLAGS

all: debug

fast: phony
	$(MAKE) -f Makefile.fast.gcc

debug: phony
	$(MAKE) -f Makefile.dev.gcc

distw32: phony
	$(MAKE) -f Makefile.dist.mingw32

docs:
	rm -f docs.html
	doxygen
	ln -s html/index.html docs.html

clean:
	rm -rf $(SRC:.c=.gcno) $(SRC:.c=.gcda) $(SRC:.c=.gcov) $(SRC:.c=.o)
	rm -rf html gmon.out docs.html $(EXE) *.dyn *.dpi *.lock *.stackdump *.db cygwin1.dll

phony: 
	true
