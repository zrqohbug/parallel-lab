#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <atomic>
#include "sys/time.h"
#define BILLION 1000000000L
#define Size 8
//std::atomic<int> Cur;
pthread_barrier_t mybarrier;
pthread_mutex_t lock; 
pthread_cond_t condP;
//volatile int flag;
//volatile double temp2[Size];
int flag;
double temp2[Size];
typedef struct {
    double **a, *b,*sum;
    int *c, n, p, pid;
} GM;

void *pbksb(void *varg) {
    GM *arg = (GM*)varg;
    register int i, j, start, end, round, k, l;
    register int inner,inner2;
    register int cur;
    register double sumP;
    register double tem;
    register int axi;
    struct timeval t0, t1, dt;
    int pid, block, n, p;
    double **a, *b;
    double *sum;
    a = arg->a;
    b = arg->b;
    n = arg->n;
    p = arg->p;
    pid = arg->pid;
    sum = arg->sum;
    block = n / (p * Size);
    start = 0;
    end = p - 1;
    for(round = block - 1; round >= 0 ; round--)
    {
        i = (round * p + p - pid) * Size - 1;  // the first line each thread in each round need to deal with
        for(k = p - 1 ; k >= 0 ; k--)   // need to loop for p times in each block
        {            
            axi = (round * p + 1 + k) * Size - 1;
            //gettimeofday(&t0, NULL);            
            pthread_mutex_lock(&lock);
            if( (k + 1) != (i - round * p * Size + 1) / Size){
                //printf("k + 1:%d || %d\n", k + 1 , (i - round * p * Size + 1) / Size);
                while(flag == round * p  + k)
                {
                    //printf("flag:%d, threadid: %d\n", flag2.load(), pid);
                    pthread_cond_wait(&condP, &lock);
                    //printf("flag:%d, threadid: %d\n", flag2.load(), pid);
                }
            }
            else 
            {
                for(inner = 0 ; inner < Size ; inner++)
                {
                    sumP = 0;
                    for(inner2 = 0; inner2 < inner; inner2++)
                        sumP += temp2[inner2] * a[i - inner][i - inner2];
                    b[i - inner] = (sum[i - inner] - sumP) / a[i - inner][i - inner];
                    temp2[inner] = b[i - inner];
                    //printf("temp2[%d] = %lf\n", inner , temp2[inner]);
                }
                flag--;
                pthread_cond_broadcast(&condP);
            }
            pthread_mutex_unlock(&lock);  
            // parallel update the sum value
            //for(l = i; l >= 0 ; l = l - Size * p)
            //for(l = i; l >= 0 ; l = l - Size * p)
            for(l = (p - pid) * Size - 1; l <= i ; l += Size * p)  // for loop form small to big prevent the cahce data
            {   
                #pragma unroll
                for(inner = 0; inner < Size ; inner++)
                {
                    tem = sum[l - inner];
                    #pragma unroll
                    for(inner2 = 0; inner2 < Size ; inner2++)
                    {
                        tem -= a[l - inner][ axi - inner2 ] * temp2[inner2];                      
                    }
                    sum[l - inner] = tem;
                }
            }
            pthread_barrier_wait(&mybarrier);
            //gettimeofday(&t1, NULL);
            //timersub(&t1, &t0, &dt);
            //if(pid == 0)
            //{
            //fprintf(stderr, "doSomeThing (thread %ld) took %d.%06d sec\n",
            //    (long)pthread_self(), dt.tv_sec, dt.tv_usec);
            //}
        }

    }
    return NULL;
}


int main(int argc, char **argv) {
    struct timespec start, end;
    int i, j, p, n, *c;
    int newn, on;
    double **a, *b, time, count = 1.0;
    double *sum;
    if(argc != 3) {
        printf("Usage: pbksb n p\nAborting...\n");
        exit(0);
    }
    n = atoi(argv[1]); 
    p = atoi(argv[2]);
    on = n;
    if(n % (Size * p) != 0)
        newn = (n /(Size * p) + 1) * Size * p;
    else
        newn = n;
    a = (double **) malloc(newn * sizeof(double *));
    for(i = 0; i < newn ; i++)
    {
        a[i] = (double *) malloc(newn * sizeof(double));
        for(j = 0; j < newn; j++) {
            a[i][j] = 1;
        }        
    }
    for(i = 0; i < n; i++) {
        for(j = i; j < n; j++) {
            a[i][j] = count;
            count++;
        }
    }  
    b = (double *) malloc(newn * sizeof(double));
    sum = (double *)malloc(newn * sizeof(double));
    for(i = 0; i < newn; i++)
    {
        b[i] = 0;
        sum[i] = 0;
    }
    for(i = 0; i < n; i++) {
        b[i] = count;
        sum[i] = count;
        count++;
    }
    n = newn;
    flag = n / Size - 1;
    pthread_mutex_init(&lock, NULL); 
    pthread_cond_init (&condP, NULL);
    pthread_barrier_init(&mybarrier,NULL,p);
    clock_gettime(CLOCK_MONOTONIC, &start);
    pthread_t *threads = (pthread_t*)malloc(p * sizeof(threads));
    for(i = 0; i < p; i++) {
        GM *arg = (GM*)malloc(sizeof(*arg));
        arg->a = a;                 // a store the value of matrix
        arg->b = b;                 // b store the input b & result
        arg->c = c;                 // shared lock
        arg->n = n;                 // size of the matrix
        arg->p = p;                 // number of the threads
        arg->sum = sum;             // current sum
        arg->pid = i;               // thread pid
        pthread_create(&threads[i], NULL, pbksb, arg);
    }
    for(i = 0; i < p; i++)
        pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_MONOTONIC, &end);
    free(threads);
    
    time = BILLION *(end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec);
    time = time / BILLION;
    printf("Elapsed time: %lf seconds (n = %d, p = %d)\n", time, n, p);
    for(i = 0; i < on; i++)
        printf("%lf\n", b[i]);
    printf("\n");
    return 0;
}
