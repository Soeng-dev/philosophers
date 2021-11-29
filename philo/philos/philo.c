

#include "philo.h"

/* index of left fork is same with id of philosopher */

void init_common_info(t_common_info *info, char **argv)
{
    info->time_to_die = ft_atoi(argv[ARGV_TIME_TO_DIE]);
    info->time_to_eat = ft_atoi(argv[ARGV_TIME_TO_EAT]);
    info->time_to_sleep = ft_atoi(argv[ARGV_TIME_TO_SLEEP]);
    info->num_philos = ft_atoi(argv[ARGV_NUM_PHILOS]);
    if (argv[ARGV_EATING_TIME_QUOTA])
        info->quota = ft_atoi(argv[ARGV_EATING_TIME_QUOTA]);
    else
        info->quota = LLONG_MAX;
    pthread_mutex_init(&info->mutex, NULL);
    info->forks = calloc(info->num_philos, sizeof(int));
}

void philo_act(t_philo_info *ph_info)
{
    struct timeval last_eating;
    struct timeval now;
    int printed_thinking;

    gettimeofday(&last_eating, NULL);
    printed_thinking = FALSE;
    while ((long long)ph_info->accumulated < ph_info->common->quota)
    {
        if (has_eaten_spaghetti(ph_info))
        {
            gettimeofday(&last_eating, NULL);
            printf("%dms %d is sleeping\n",
                   get_timestamp(&ph_info->common->start),
                   ph_info->id);
            usleep(MICRO_TO_MILLI * ph_info->common->time_to_sleep);
            printed_thinking = FALSE;
        }
        if (!printed_thinking)
        {
            printf("%dms %d is thinking\n",
                   get_timestamp(&ph_info->common->start),
                   ph_info->id);
            printed_thinking = TRUE;
        }
        gettimeofday(&now, NULL);
        if (get_diff_millisec(&last_eating, &now) >= ph_info->common->time_to_die)
            printf("%dms %d is thinking\n",
                   get_diff_millisec(&ph_info->common->start, &now),
                   ph_info->id);
    }
}


void dining_philos(char **argv)
{
    t_common_info common_info;
    t_philo_info *ph_infos;
    pthread_t *threads;
    int id;

    threads = malloc(common_info.num_philos * sizeof(pthread_t));
    init_common_info(&common_info, argv);
    if (!common_info.forks)
        return;
    id = -1;
    while (++id < common_info.num_philos)
    {
        // init ph_info
        ph_infos[id].common = &common_info;
        ph_infos[id].id = id;
        ph_infos[id].accumulated = 0;
        int left_fork = id;
        int right_fork;

        if (id == common_info.num_philos - 1)
            right_fork = 0;
        else
            right_fork = id + 1;
        if (id % 2)
        {
            ph_infos->first_fork = left_fork;
            ph_infos->second_fork = right_fork;
        }
        else
        {
            ph_infos->first_fork = right_fork;
            ph_infos->second_fork = left_fork;
        }
        pthread_create(threads + id, NULL, philo_act, ph_infos + id);
    }
    while (--id >= 0)
        pthread_join(threads[id], NULL);
    free(ph_infos);
    free(threads);
    //free , destroy common info
}

int has_picked_fork(t_philo_info *info, int fork_index)
{
    int has_picked;
    struct timeval now;

    pthread_mutex_lock(&info->common->mutex);
    if (info->common->forks[fork_index] == FORK_NOT_USING)
    {
        info->common->forks[fork_index] = FORK_USING;
        gettimeofday(&now, NULL);
        printf("%dms %d has taken a fork\n", get_timestamp(&info->common->start), info->id);
        has_picked = TRUE;
    }
    else
        has_picked = FALSE;
    pthread_mutex_unlock(&info->common->mutex);
    return has_picked;
}

void drop_fork(t_common_info *info, int fork_index)
{
    pthread_mutex_lock(&info->mutex);
    info->forks[fork_index] = FORK_NOT_USING;
    pthread_mutex_unlock(&info->mutex);
}

int has_eaten_spaghetti(t_philo_info *ph_info)
{
    struct timeval now;
    int has_eaten;

    has_eaten = FALSE;
    if (has_picked_fork(ph_info,
                        ph_info->first_fork))
    {
        if (has_picked_fork(ph_info,
                            ph_info->second_fork))
        {
            printf("%dms %d is eating\n",
                   get_timestamp(&ph_info->common->start),
                   ph_info->id);
            usleep(ph_info->common->time_to_eat / MICRO_TO_MILLI);
            ph_info->accumulated += ph_info->common->time_to_eat;
            has_eaten = TRUE;
            drop_fork(ph_info->common,
                      ph_info->second_fork);
        }
        drop_fork(ph_info->common,
                  ph_info->first_fork);
    }

    return has_eaten;
}
