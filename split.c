char * * split(const char * str, const char * delims, int * arrLen) {
	//LOCAL DECLARATIONS
	int ndelims;//# of delimiter characters in char *
	char * lense;//points to current part of string
	//char * keep;//points to lense top
	int i;//index of str
	int nstr;//number of str created
	int flag;//an indicator to expect a condition
	int tcount;//counter to place terminal character

	//EXECUTABLE STATEMENTS
	lense = malloc((strlen(str) + 1) * sizeof(char));
	ndelims = 0;
	strcpy(lense, str);
	i = 0;
	
	//determine # of delimiters if any
	while(lense[i] != '\0') {
		if(strchr(delims, lense[i]) != NULL) {
			ndelims++;
			while(strchr(delims, lense[i]) != NULL) {
				i++;
			}
		}
		else {
			i++;
		}
	}
	//allocate the data for each pointer in return **char
	char * * strArr = malloc((ndelims + 1) * sizeof(char *));
	flag = 0;
	// {increment through begining letters until first is not a delimiter}
	while((*lense != '\0') && (strchr(delims, *lense) != NULL))  {
		lense++;
	}
	// {if strlen(str) - beggining_delimiters != 1}	
	if(*lense != '\0') {
		// {initialize variables for explosions}
		strArr[0] = lense;
		nstr = 1;
		tcount = 0;
		while(nstr < ndelims + 1 && *lense != '\0') {
			if(*lense != '\0') {
				// {if last char was part of delimiter}
				if(flag == 1) {
					// {if curr char is not a delimiter}
					if(strchr(delims, *lense) == NULL) {
						// {if not last fragment: assign part and reset}
						if(nstr < ndelims + 1) {
							strArr[nstr++] = lense;
							flag = 0;
							tcount = 0;
						}
					}
				}// {check for delimiter at curr char: sever is found}
				else if(strchr(delims, *lense) != NULL) {
					flag = 1;
					strArr[nstr - 1][tcount] = '\0';
				}
				// {update curr char: update char in fragment}
				lense++;
				tcount++;
			}
		}
	}
	*arrLen = ndelims + 1;
	return(strArr);
}
