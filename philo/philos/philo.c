
#include "philo.h"

/* index of left fork is same with id of philosopher */

void dining_philos(char **argv)
{
    t_common_info common_info;
    t_philo_info *ph_infos;
    int id;

    init_common_info(&common_info, argv);
    ph_infos = malloc(common_info.num_philos * sizeof(t_philo_info));
    if (!ph_infos)
        printf("hi\n");
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
        pthread_create(&common_info.ph_treads[id], NULL, philo_act, ph_infos + id);
    }
    while (--id >= 0)
    {
        if (ph_infos[id].is_undetached)
            pthread_join(common_info.ph_treads[id], NULL);
    }
    free(ph_infos);
    //free , destroy common info
}

void init_common_info(t_common_info *info, char **argv)
{
    int i;

    info->time_to_die = ft_atoi(argv[ARGV_TIME_TO_DIE]);
    info->time_to_eat = ft_atoi(argv[ARGV_TIME_TO_EAT]);
    info->time_to_sleep = ft_atoi(argv[ARGV_TIME_TO_SLEEP]);
    info->num_philos = ft_atoi(argv[ARGV_NUM_PHILOS]);
    info->ph_treads = malloc(sizeof(pthread_t) * info->num_philos);
    pthread_mutex_init(&info->thread_work, NULL); 
    if (argv[ARGV_EATING_TIMES_QUOTA])
        info->quota = ft_atoi(argv[ARGV_EATING_TIMES_QUOTA]);
    else
        info->quota = LLONG_MAX;
    gettimeofday(&info->start, NULL);
    info->forks = malloc(info->num_philos * sizeof(int));
    i = -1;
    while (++i < info->num_philos)
        pthread_mutex_init(&info->forks[i], NULL);
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
        pthread_mutex_lock(&ph_info->common->thread_work);
        eat_spaghetti(ph_info);
        gettimeofday(&last_eating, NULL);
        printf("%dms %d is sleeping\n",
               get_timestamp(&ph_info->common->start),
               ph_info->id);
        usleep(MILLI_TO_MICRO * ph_info->common->time_to_sleep);
        printed_thinking = FALSE;
        //seperate here to a function think_until die
        if (!printed_thinking)
        {
            printf("%dms %d is thinking\n",
                   get_timestamp(&ph_info->common->start),
                   ph_info->id);
            printed_thinking = TRUE;
        }
        else
        {
            gettimeofday(&now, NULL);
            if (get_diff_millisec(&last_eating, &now) >= ph_info->common->time_to_die)
            {
                printf("%dms %d died\n",
                       get_diff_millisec(&ph_info->common->start, &now),
                       ph_info->id);
                ph_info->is_undetached = FALSE;
                pthread_detach(ph_info->common->ph_treads[ph_info->id]);
            }
        }
    }
}

void eat_spaghetti(t_philo_info *ph_info)
{
    struct timeval now;
    pthread_t *forks;

    forks = ph_info->common->forks;
    pthread_mutex_lock(forks[ph_info->first_fork]);
    printf("%dms %d has taken a fork\n",
           get_timestamp(&ph_info->common->start),
           ph_info->id);
    pthread_mutex_lock(forks[ph_info->second_fork]);
    printf("%dms %d has taken a fork\n",
           get_timestamp(&ph_info->common->start),
           ph_info->id);
    printf("%dms %d is eating\n",
           get_timestamp(&ph_info->common->start),
           ph_info->id);
    usleep(ph_info->common->time_to_eat * MILLI_TO_MICRO);
    pthread_mutex_lock(forks[ph_info->first_fork]);
    pthread_mutex_lock(forks[ph_info->second_fork]);
    ++ph_info->accumulated;
}