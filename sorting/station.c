#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "salgs.h"

#define RSETSIZE 10

void printarray(int * set, int len); 
int * genarray(int * len); 

int main(int argc, char * argv[]){
	// get 
	int * array;
	int len = 0;
	if(argc != 2) {
		array = genarray(&len);
	}
	else {
		if(readfile(argv[1], array, &len)) {
			array = genarray(&len);
		}
		return(1);
	}
	// print
	printarray(array, len);
	// sort
	selection_sort(array, len);
	// print
	printarray(array, len);
	// study
	// free
	free(array);
	// quit
	return(EXIT_SUCCESS);
}

int * genarray(int * len) {
	int check[RSETSIZE] = {0};
	int * set = malloc(sizeof(int) * RSETSIZE);
	int count = 0;
	int flag = 1;
	int bogus = 0;
	int val = 0;
	int	mod = RSETSIZE;
	for(count = 1; count < RSETSIZE; count++) {
		while(flag) {
			flag = 0;
			val = rand() % mod;
			for(bogus = 0; bogus < RSETSIZE; bogus++) {
				if(val == check[bogus]) {
					//printf("a");
					flag = 1;
				}
			}
		}
		set[count] = val;
		check[count] = val;
		flag = 1;
	}
	*len = 10;
	return(set);
}

void printarray(int * set, int len) {
	int count;
	printf("{");
	for(count  = 0; count < len; count++) {
		printf("%2d", set[count]);
		if(count < len - 1) {
			printf(", ");
		}	
	}
	printf("}\n");
	return;
}



int readfile(char * filename, int * array, int * len) {
	FILE * fp = fopen(filename, 


}
