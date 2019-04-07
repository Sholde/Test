#include <stdio.h> //printf
#include <string.h> //strlen

// read/write
#include <unistd.h>
#include <fcntl.h>

// wait
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	const int taille = 256;
	
	int tab[2];
	pipe(tab);
	
	pid_t pid;
	pid = fork();
	
	if(!pid)
	{
		// écris dans le tube
		char* buffer1 = "son says hello\n";
		write(tab[1], buffer1, strlen(buffer1));
		
		// attends que le père écris puis lis
		char buffer2[taille];
		read(tab[0], buffer2, taille);
		printf("son : %s", buffer2);
		
		// ferme le tube
		close(tab[0]); close(tab[1]);
		return 0;
	}
	else
	{
		int retour;
		
		// attends que le fils écris et lis
		char buffer2[taille];
		read(tab[0], buffer2, taille);
		printf("dad : %s", buffer2);
		
		// écris dans le tube
		char* buffer1 = "dad says hello\n";
		write(tab[1], buffer1, strlen(buffer1));
		
		// ferme le tube
		close(tab[0]); close(tab[1]);
		
		// pour attendre le traitement du fils
		wait(&retour);
		return 0;
	}
}
