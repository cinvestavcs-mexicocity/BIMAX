CCOMP= gcc
CLINK=gcc
LFLAGS= -std=c99
CFLAGS= -std=c99 -Wall -c
EXEC=exec
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(CPPS))
$(EXEC): $(OBJS) 
	$(CCOMP) $(LFLAGS)  -o $@ $(OBJS) -lm
%.o: %.c 
	$(CCOMP) $(CFLAGS) $< -o $@
optimized:
	make -f Makefile CFLAGS="-O3 -std=c99 -Wno-unused-result -D NDEBUG -c" LFLAGS="-O3 -std=c99 -Wno-unused-result"
debug:
	make -f Makefile CFLAGS="-std=c99 -g -c -v " LFLAGS="-g -std=c99"
clean:
	rm -f $(OBJS) 	
cleanall:
	rm -f $(OBJS) $(EXEC)
	
	
	