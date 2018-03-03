#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>
int isUserLine(const char *line);
struct user *parseUserLine(FILE *fp);
char *readLine(FILE *fp, char *line);
#endif
