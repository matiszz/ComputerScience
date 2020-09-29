#include <unistd.h>

main() {
	int num;
	char c[128];

	read(0, &num, sizeof(int));
	sprintf(c, "%d\n", num);
	write(1, c, strlen(c));
}
