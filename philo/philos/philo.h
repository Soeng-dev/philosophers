
#ifndef PHILO_H
#define PHILO_H

#include "../common_define.h"
#include "../utils/utils.h"
#include "./define.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_common_info
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_philos;
    pthread_t *ph_treads;
    long long quota;
    pthread_mutex_t *forks;
    // pthread_mutex_t thread_work;
    struct timeval start;
} t_common_info;

typedef struct s_philo_info
{
    t_common_info *common;
    int id;
    int is_undetached;
    int accumulated;
    int first_fork;
    int second_fork;
} t_philo_info;

void dining_philos(char **arg);
void init_common_info(t_common_info *info, char **argv);
void philo_act(t_philo_info *ph_info);
void eat_spaghetti(t_philo_info *ph_info);
int has_picked_fork(t_philo_info *info, int fork_index);
void drop_fork(t_common_info *info, int fork_index);

#endif
