#include <parsing.h>
struct user
{
	char name[UMAXLEN + 1];
	char doing[DMAXLEN + 1];
	unsigned changes;
};
