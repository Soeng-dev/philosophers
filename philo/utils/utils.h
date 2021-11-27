
#ifndef UTILS_H
#define UTILS_H

#include "../common_define.h"

#include <sys/time.h>


int ft_strcmp(char *s1, char *s2);
int compare_strnum(char *strnum1, char *sign, char *strnum2);
int ft_atoi(const char *str);
int get_timestamp(struct timeval *start);
int get_diff_millisec(struct timeval *start, struct timeval *now);

#endif