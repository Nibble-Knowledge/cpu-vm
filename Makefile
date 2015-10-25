EXE=vm4
SRCDIR=src

all: fast


fast: phony
	$(MAKE) -C $(SRCDIR) fast
	cp $(SRCDIR)/$(EXE) .

debug: phony
	$(MAKE) -C $(SRCDIR)
	cp $(SRCDIR)/$(EXE) .

distw32: phony
	$(MAKE) -C $(SRCDIR) distw32
	cp $(SRCDIR)/$(EXE) .
	cp $(SRCDIR)/cygwin1.dll .

clean:
	$(MAKE) -C $(SRCDIR) clean
	rm -rf $(EXE) gmon.out cygwin1.dll

phony: 
	true
