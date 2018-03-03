#ifndef CONFIG_H
#define CONFIG_H
#define BRDURL	"example.com"	/* URL of MyBB board to check */
#define MAXUSR	16		/* max number of tracked users */
#define UMAXLEN	64		/* maximum length of a username */
#define DMAXLEN 64		/* maximum length of doing string */
#define RFTIME	10		/* seconds between refreshing */
#define CHKCNT	24		/* iterations before each check */
#define CHMAX	20		/* max number of changed before trigger */
struct user
{
	char name[UMAXLEN + 1];
	char doing[DMAXLEN + 1];
	unsigned changes;
};
#endif
