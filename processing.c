#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <processing.h>
#include <parsing.h>
#include <config.h>
struct user *loadUsers(FILE *fp, unsigned *count)
{
	struct user *l_users, *r_users, *rduser;
	char *line;
	int valid;
	*count = 0;
	valid = 1;
	line = NULL;
	r_users = NULL;
	l_users = malloc(sizeof(struct user) * MAXUSR);
	while ((line = readLine(fp, line)) != NULL && *count < MAXUSR && valid)
		if (isUserLine(line))
		{
			if ((rduser = parseUserLine(fp)) != NULL)
			{
				memcpy(&l_users[*count++], rduser, sizeof(struct user));
				free(rduser);
			}
			else valid = 0;
		}
	if (*count > 0)
	{
		r_users = malloc(sizeof(struct user) * *count);
		memcpy(r_users, l_users, sizeof(struct user) * *count);
	}
	free(l_users);
	return r_users;
}
int userIsInList(struct user *users, unsigned length, const char *name)
{
	int i;
	for (i = 0; i < length; ++i) if (!strcmp(users[i].name, name)) return i;
	return -1;
}
unsigned processUsers(struct user *users, unsigned c_users, struct user *l_users, unsigned c_lusers)
{
	int i, userind;
	for (i = 0; i < c_lusers; ++i)
	{
		if ((userind = userIsInList(users, c_users, l_users[i].name)) >= 0) // user exists, check for changes
			if (strcmp(l_users[i].doing, users[userind].doing)) // changed
				++users[userind].changes;
		else // user doesn't exist, insert at end of list
		{
			memcpy(&users[c_users], &l_users[i], sizeof(struct user)); // copy in the structure
			if (c_users < MAXUSR) ++c_users;
		}
	}
	return c_users;
}
void swapUser(struct user *users, unsigned x, unsigned y)
{
	struct user tmp;
	memcpy(&tmp, &users[x], sizeof(struct user));
	memcpy(&users[x], &users[y], sizeof(struct user));
	memcpy(&users[y], &tmp, sizeof(struct user));
}
void sortUsers(struct user *users, unsigned length)
{
	unsigned i, j;
	for (i = 0; i < length - 1 && length != 0; ++i)
		for (j = 0; j < length - i - 1; ++j)
			if (users[j].changes < users[j + 1].changes)
				swapUser(users, j, j + 1);
}
