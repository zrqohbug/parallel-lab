#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "sys/time.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "sys/mman.h"


#define BILLION 1000000000L
#define Size 64

int P;

typedef struct simplelock{
    volatile int lock_data;
}lock;


extern void s_lock_init(lock *lkp);
extern void t_s_lock_init(lock *lkp);
extern void s_lock(lock *lkp);
extern void t_s_lock(lock *lkp);
extern void s_unlock(lock *lkp);
extern void t_s_unlock(lock *lkp);

#ifdef TICKET
typedef struct ticketlock{
    volatile unsigned short next_ticket;
    volatile unsigned short now_serving;
}ticket;

void ticket_lock_init(ticket *lkt)
{
    lkt -> now_serving = 0;
    lkt -> next_ticket = 0;
}
void ticket_lock(ticket *lkt, lock *lkp)
{
    unsigned short my_ticket;
    //lock by TTS
    s_lock(lkp);
    my_ticket = lkt -> next_ticket;
    lkt -> next_ticket += 1;
    //unlock by TTS
    s_unlock(lkp);
    while(my_ticket != lkt -> now_serving);
}
void ticket_unlock(ticket *lkt)
{
    lkt -> now_serving += 1;
}
#endif

#ifdef QUEUE
int* array;
volatile unsigned int next_loc;
void queue_lock_init(int* qarray){
    int i;
    for(i = 1; i < P ; i++)
        qarray[i * Size] = 0;
    qarray[0] = 1;    
    next_loc = 0;
}
void queue_lock(int* qarray, lock* lkp, unsigned int* que){
    //lock by TTS
    s_lock(lkp);
    *que = next_loc % P;
    next_loc = next_loc + 1;
    //unlock by TTS
    s_unlock(lkp);
    while(qarray[(*que) * Size] != 1);
}
void queue_unlock(int *qarray, unsigned int* que)
{
    qarray[(*que) * Size] = 0;
    qarray[(((*que) + 1) == P ? 0 : (*que) + 1 ) * Size] = 1;

}
#endif
typedef struct {
    unsigned int *start;
    unsigned int *end;
    int *a;
    int P, N, K, M;
    lock *lck;
#ifdef TICKET
    ticket *tck;
#endif

} GM;

GM *gm;

void *benchmark(void* b){
    register int i, j, p, q;
    register int pid, N, K, M;                                          
    N = gm -> N;
    K = gm -> K;
    M = gm -> M;
    int* temp = (int*)b;
    pid = *temp;
    p = 0;
    q = 0;
#ifdef QUEUE
    unsigned int que = 0;
#endif
    for(i = 0 ; i < N; i++)
    {
//acquire
#ifdef TS
        //printf("use TS\n");
        s_lock(gm -> lck);
#endif
#ifdef TTS
        //printf("use TTS\n");
        t_s_lock(gm -> lck);
#endif
#ifdef TICKET
        ticket_lock(gm -> tck, gm -> lck);
#endif
#ifdef QUEUE
        queue_lock(array, gm -> lck, &que);
#endif
        for(j = 0; j < K; j++)
            q++;
//release
#ifdef TS
        s_unlock(gm -> lck);
#endif
#ifdef TTS
        t_s_unlock(gm -> lck);
#endif
#ifdef TICKET
        ticket_unlock(gm -> tck);
#endif
#ifdef QUEUE
        queue_unlock(array, &que);
#endif
        for(j = 0; j < M; j++)
            p++;
    }
    gm -> a[pid] = p + q;
}


int main(int argc, char **argv) {

    unsigned int *start, *end;
    int M, k;
    int *a;
    int i;
    if(argc != 4) {
        printf("Usage: my_loc problem p M K\nAborting...\n");
        exit(0);
    }
    GM cur;
    gm = &cur;   
    P = atoi(argv[1]);  
    gm -> P = atoi(argv[1]);      // p -> threadnumber;
    gm -> N = 2000000;
    gm -> M = atoi(argv[2]);      
    gm -> K = atoi(argv[3]);
    a = gm -> a = (int*)malloc(P * sizeof(int));
    start = gm -> start = (unsigned int*)malloc(P * sizeof(unsigned int));
    end = gm -> end = (unsigned int*)malloc(P * sizeof(unsigned int));
    pthread_t *threads = (pthread_t*)malloc(P * sizeof(threads));
    gm -> lck = (lock*)malloc(sizeof(lock));

//init
#ifdef TS
    s_lock_init(gm -> lck);
#endif
#ifdef TTS
    t_s_lock_init(gm -> lck);
#endif
#ifdef TICKET
    gm -> tck = (ticket*)malloc(sizeof(ticket));
    s_lock_init(gm -> lck);
    ticket_lock_init(gm -> tck);
#endif
#ifdef QUEUE
    s_lock_init(gm -> lck);
    array = (int*)malloc(sizeof(int) * P * Size);
    queue_lock_init(array);
#endif
    for(i = 0; i < P; i++) {
        int *b = (int*)malloc(sizeof(int));
        *b = i;
        pthread_create(&threads[i], NULL, benchmark, (void*)b);
    }
    for(i = 0; i < P; i++)
        pthread_join(threads[i], NULL);
    free(threads);
    for(i = 0; i < P; i++)
    {
        printf("sum[%d] = %d\n", i , gm -> a[i]);
    }
    return 0;
}
