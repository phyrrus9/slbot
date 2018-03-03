#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <parsing.h>
#include <config.h>
int isUserLine(const char *line)
{
	return strstr(line, "<!-- start: online_row -->") != NULL;
}
char *parseUsername(const char *line)
{
	unsigned length;
	char *base, *username = NULL, *search = BRDURL "/User-";
	if ((base = strstr(line, search) + strlen(search)) > line)
	{
		length = strstr(base, "\">") - base;
		username = malloc(length + 1);
		memcpy(username, base, length);
		username[length] = 0;
	}
	return username;
}
char *parseDoing(const char *line)
{
	unsigned length;
	char *base, *doing = NULL;
	if ((base = strstr(strstr(line, "a href=") + strlen("a href="), "\">") + strlen("\">")) > line)
	{
		length = strstr(base, "</a>") - base;
		doing = malloc(length + 1);
		memcpy(doing, base, length);
		doing[length] = 0;
	}
	return doing;
}
struct user *parseUserLine(FILE *fp)
{
	char *tmpusername, *tmpdoing, *line = NULL;
	struct user *ruser = NULL;
	line = readLine(fp, line); // <td>
	line = readLine(fp, line); // username
	tmpusername = parseUsername(line);
	line = readLine(fp, line); // time
	line = readLine(fp, line); // doing
	tmpdoing = parseDoing(line);
	if (tmpusername != NULL && tmpdoing != NULL)
	{
		ruser = malloc(sizeof(struct user));
		memset(ruser, 0, sizeof(struct user));
		strncpy(ruser->name, tmpusername, UMAXLEN);
		strncpy(ruser->doing, tmpdoing, DMAXLEN);
	}
	return ruser;
}
char *readLine(FILE *fp, char *line)
{
	char scratch;
	if (line == NULL) line = malloc(4096);
	if (fscanf(fp, "%[^\n]%c", line, &scratch) <= 0)
	{ free(line); line = NULL; }
	return line;
}
