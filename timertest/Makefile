SRC=test.c
EXE=testtimer
EXTRACFLAGS=
EXTRALDFLAGS=
export SRC
export EXE
export EXTRACFLAGS
export EXTRALDFLAGS

all: fast

fast: phony
	$(MAKE) -f Makefile.fast.gcc

debug: phony
	$(MAKE) -f Makefile.dev.gcc

clean:
	rm -rf $(SRC:.c=.gcno) $(SRC:.c=.gcda) $(SRC:.c=.gcov) $(SRC:.c=.o)
	rm -rf html gmon.out docs.html $(EXE) *.dyn *.dpi *.lock *.stackdump *.db

phony: 
	true
