TARGETS= test
N = 2
P = 2
M = 2
CROSS_TOOL = 
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -pthread -m32 -std=gnu99
DFLAGS = -D QUEUE

all: clean $(TARGETS)

test: 
	$(CC_C) $(DFLAGS) $(CFLAGS) lock.s my_lock.c -o $@

run_local: test
	./test $(P) $(N) $(M)

run_production: test
	qsub -v n=$(N),p=$(P) run.sh

clean:
	rm -f $(TARGETS)
