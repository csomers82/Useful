#include <stdio.h>
#include <stdlib.h>
#include "salgs.h"

int * selection_sort(int * set, int n) {
	int min = NULL;
	int minpos = 0;
	int temp;
	int i;
	int pass;
	for(pass = 0; pass < n - 2; pass++) {
		min = set[pass];
		minpos = pass;
		for(i = pass; i < n; i++) {
			if(min > set[i]) {
				printf("%d -> %d\n", min, set[i]);
				min = set[i];
				minpos = i;
			}
		}
		if(minpos != pass) {
			temp = set[pass];
			set[pass] = min;
			set[minpos] = temp;
		}
		printarray(set, n);
	}
	return(set);
}

