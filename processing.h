#ifndef PROCESSING_H
#define PROCESSING_H
#include <stdio.h>
struct user *loadUsers(FILE *fp, unsigned *count);
unsigned processUsers(struct user *users, unsigned c_users, struct user *l_users, unsigned c_lusers);
void sortUsers(struct user *users, unsigned length);
#endif
