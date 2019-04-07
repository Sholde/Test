#include <stdio.h>
#include <stdlib.h> // atoi

int division(int nb, int diviseur) {
	int res, i;
	for(i = 0; i*diviseur <= nb; i++);
	res = (i-1);
	return res;
}

int modulo(int nb, int diviseur, int res) {
	return nb - (res * diviseur);
}

int main(int argc, char** argv) {
	if(argc < 3)
		return 0;
	int nb = atoi(argv[1]);
	int diviseur = atoi(argv[2]);
	int res;
	
	printf("div normal :\n");
	res = nb/diviseur;
	printf("div = %d\n", res);
	
	res = nb%diviseur;
	printf("modulo = %d\n", res);
	
	printf("\n");
	
	printf("ma div :\n");
	res = division(nb, diviseur);
	printf("div = %d\n", res);
	
	res = modulo(nb, diviseur, res);
	printf("modulo = %d\n", res);
	return 0;
}
