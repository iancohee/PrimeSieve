#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "timer.h"

#define PRIME     0
#define NON_PRIME 1

/* Prototypes */
void prep_list(unsigned int**, unsigned int*);
void mark_multiples(unsigned int**, unsigned int*, unsigned int*);
void sieve(unsigned int**, unsigned int*);
void print_primes(unsigned int**, unsigned int*, double*);

int main(int argc, char *argv[]) {
    unsigned int N, i;
    unsigned int *list; 
    double time;

    /* Some initializations */
    N = i = 0;
    time = 0.0;
    list = NULL;

    /* Checks */
    if(argc != 2) {
        printf("Usage: %s <N> where N > 2\n", argv[0]);
        exit(1);
    }
    N = atoi(argv[1]);
    if(N <=2) {
        printf("Usage: %s <N> where N > 2\n", argv[0]);
        exit(1);
    }

    /* Allocate space for the list */
    list = (unsigned int *) malloc(sizeof(unsigned int) * (N+1));
    if(list == NULL) {
        printf("Could not allocate head memory. Fail.\n");
        exit(2);
    }

    /* Get our list ready */
    prep_list(&list, &N);

    /* do it */
    initialize_timer();
    start_timer();
    sieve(&list, &N);
    stop_timer();
    time = elapsed_time();

    /* Show 'em if ya got 'em */
    print_primes(&list, &N, &time);

    /* Free space */
    free(list);

    /* ANSI return */
    return 0;
}

void prep_list(unsigned int **list, unsigned int *N) {
    bzero(*list, sizeof(unsigned int) * (*N+1));

    /* We aren't concerned with values below 2 */
    (*list)[0] = NON_PRIME;
    (*list)[1] = NON_PRIME;
}

void mark_multiples(unsigned int **list, unsigned int *N, unsigned int *k) {
    unsigned int multiple = (*k) * (*k);
    while(multiple <= *N) {
        (*list)[multiple] = NON_PRIME;
        multiple += (*k);
    }
}

void sieve(unsigned int **list, unsigned int *N) {
    unsigned int k = 2;
    double sqrtN = sqrt(*N);

    while(k < sqrtN) {
        if((*list)[k] == PRIME)
            mark_multiples(list, N, &k);            
        ++k;
    }
}

void print_primes(unsigned int **list, unsigned int *N, double *time) {
    unsigned int i, count;
    i = count = 0;

    printf("Your lucky numbers are: ");
    for(; i <= *N; ++i) 
        if((*list)[i] == PRIME) {
            printf("%u ", i);
            ++count;
        }
    printf("\n\nJust found %u prime numbers, in %lf seconds!\n", count, *time);
}
