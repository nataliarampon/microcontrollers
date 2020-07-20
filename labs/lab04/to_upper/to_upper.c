#include <stdio.h>
#include <asmops.h>

int main(int argc, char *argv[]) {

	const int ERROR = -1;
	const int SUCCESS = 0;

	if (argc != 2) {
		printf("Usage:\n\t%s <string>\n", argv[0]);
		return ERROR;
	}

	print_uppercase(argv[1]);
	printf("\n");

	return SUCCESS;

}