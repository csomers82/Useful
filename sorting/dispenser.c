#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	if(argc < 3) {
		printusage();
		return(EXIT_FAILURE);
	}
	int * set = dispenser(argc - 1, argv)
int * dispenser()
