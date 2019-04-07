#include <stdlib.h> //NULL
#include <pthread.h> //ptrhead
#include <stdio.h> //printf
#include <sys/times.h> //times
#include <unistd.h> //fork
#include <sys/types.h> //wait
#include <sys/wait.h> //wait

#define TAILLE_MAX 10000

typedef struct {
	int rang;
	int *tab;
	int maxlocal;
} arg_t;

void* mainlocal(void* arg) {
	arg_t *a = (arg_t *) arg;
	int i;
	a->maxlocal = -1;
	for(i = a->rang * (TAILLE_MAX >> 2); i < (a->rang + 1) * TAILLE_MAX >> 2; ++i)
	{
		if(a->tab[i] > a->maxlocal)
			a->maxlocal = a->tab[i];
	}
	return NULL;
}

int* init_tab(int* T) {
	int i;
	srand(times(NULL));
	for(i = 0; i < TAILLE_MAX; ++i)
	{
		T[i] = rand()%20;
	}
	
	return T;
}

int popcount(int tab[]) {
	arg_t a[4];
	int i, max = -1;
	pthread_t tid[4];

	for(i = 0; i < 4; ++i)
	{
		a[i].rang = i; a[i].tab = tab;
		pthread_create(&(tid[i]), NULL, mainlocal, &(a[i]));
	}
	
	for(i = 0; i < 4; ++i)
	{
		pthread_join(tid[i], NULL);
		max = (a[i].maxlocal > max ? a[i].maxlocal : max);
	}
	
	return max;
}

int seq(int tab[]) {
	int i, max  = -1;
	for(i = 0; i < TAILLE_MAX; ++i)
	{
		if(tab[i] > max)
			max = tab[i];
	}
	return max;
}

int main () {
	int tab[TAILLE_MAX];
	init_tab(tab);
	int max;
	
	struct tms time;
	long deb, fin, res;
	
	deb = times(NULL);
	max = popcount(tab);
	fin = times(&time);
	res = fin - deb;
	printf("\nmax : %d\n", max);
	printf("Temps : %ld sec \n", res/sysconf(_SC_CLK_TCK));
	
	deb = times(NULL);
	max = seq(tab);
	fin = times(&time);
	res = fin - deb;
	printf("\nmax : %d\n", max);
	printf("Temps : %ld sec \n", res/sysconf(_SC_CLK_TCK));
}
