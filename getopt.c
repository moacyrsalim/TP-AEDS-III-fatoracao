#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv){
	FILE* arquivo;
	int opt;

	while ((opt = getopt(argc, argv, "i:o")) > 0){
		if(opt == 'i'){
			printf("%s\n", optarg);
		}
	}

	return 0;
}