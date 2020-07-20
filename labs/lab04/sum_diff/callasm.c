#include <stdio.h>
#include <stdlib.h>
#include <asmops.h>

int main(int argc, char *argv[]) {
	const int ERROR = -1;
	const int SUCCESS = 0;

	int a, b, s, d;

	if (argc != 3) {
		printf("Usage:\n\t%s <int> <int>\n", argv[0]);
		return ERROR;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	s = sum(a,b);
	d = diff(&a, &b);

	printf("%d+%d=%d\n%d-%d=%d\n\n", a,b,s,a,b,d);

	return SUCCESS;
}
