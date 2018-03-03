#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <config.h>
#include <parsing.h>
#include <processing.h>
const char *onlinepg = "https://" BRDURL "/online.php";
typedef void (*progressCallback)(unsigned, unsigned);
void waitLoop(unsigned ms, unsigned interval, progressCallback callback)
{
	unsigned i, j, s, count = ms/interval;
	for (i = 0, s = 0; i < ms; i += interval, ++s)
	{
		(*callback)(s % 4, (i * 100) / ms);
		usleep(interval * 1000);
	}
	(*callback)(0, 100);
}
void progress(unsigned spin, unsigned step)
{
	int i;
	const char *pgstep = "|\\-/";
	printf("\r"); for (i = 0; i < 109; ++i); printf(" "); printf("\r ["); // clear
	for (i = 0; i < step; ++i) printf("#"); // print bar
	for (; i < 100; ++i) printf(" "); // print blank space
	printf("] %c\b", step > 99 ? ' ' : pgstep[spin]);
	fflush(stdout);
}
#include <time.h>
int main()
{
	srand(time(NULL));
	waitLoop((rand() % 15 + 1) * 1000, 75, &progress);
	printf("\n");
	return 0;
}
