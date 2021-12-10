#include "utils.h"

int get_timestamp(struct timeval *start)
{
    struct timeval now;
    gettimeofday(&now, 0);
    return (SEC_TO_MILLI * (now.tv_sec - start->tv_sec) + (now.tv_usec - start->tv_usec) / MILLI_TO_MICRO);
}

int get_diff_millisec(struct timeval *start, struct timeval *now)
{
    return (SEC_TO_MILLI * (now->tv_sec - start->tv_sec) + (now->tv_usec - start->tv_usec) / MILLI_TO_MICRO);
}
