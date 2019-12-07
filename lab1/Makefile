TARGETS= pbksb

CROSS_TOOL = 
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -pthread -lrt

all: clean $(TARGETS)

pbksb_zhu: pbksb_zhu.c
	$(CC_CPP) $(CFLAGS) -std=c++11 $@.c -o $@

bksb_base:
	$(CC_C) $(CFLAGS) $@.c -o $@

pbksb: pbksb.c
	$(CC_C) $(CFLAGS) $@.c -o $@ 

run_pbksb:
	qsub -v n=10000,p=8 run.sh

run_bksb:
	qsub -v n=10000 run.sh

clean:
	rm -f $(TARGETS)
