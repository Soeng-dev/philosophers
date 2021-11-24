#include "philo.h"

int is_invalid_arg(int argc, char **argv)
{
    int i;
    
    i = 1;
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0)
            return FALSE;
        ++i;
    }

    return (compare_strnum(argv[ARGV_TIME_TO_DIE], "<=", argv[ARGV_TIME_TO_EAT])
        || compare_strnum(argv[ARGV_TIME_TO_SLEEP], ">=", argv[ARGV_TIME_TO_DIE]));
}


int main(int argc, char **argv)
{
    if (argc < 4 || argc > 5 || is_invalid_arg(argc, argv))
        return (0);
    
}