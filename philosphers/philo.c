#include  "philo.h"

#define Philospher_id int
typedef struct s_philo
{
    pthread_t   *thread; 
    pthread_mutex_t   *mutex;
    bool            *lock;
    long    *last_meal;
    bool    *eating;
    bool    *sleeping;
    int number;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int limit_times_must_eat;
    bool    Dead_flag;
}t_philo;

typedef struct  s_philospher
{
    Philospher_id id;
    struct s_philo  *philo;
}t_philospher;

void   mutex_end(t_philo    *philo)
{
    int i;

    i = 0;
    while(i < philo->number)
    {
        pthread_mutex_destroy(&philo->mutex[i]);
        i++;
    }
    free(philo->mutex);
}

void    ending_program(t_arg   *info, t_philo    *philo)
{
    free(info->data);
    mutex_end(philo);
    free(philo->thread);
    free(philo->last_meal);
    free(philo->sleeping);
    free(philo->eating);
}

long get_time()
{
    struct  timeval time; 
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000); // becouse 1s = 1000 milisecond && 1s = 1000000 microsecond
}

void    sleep_mili(int  mili)
{
    int start;
    int end;
    
    start = get_time();
    end = get_time();
    while (end - start < mili)
    {
        usleep(1000);
        end = get_time();
    }
}
int    checking_deads(t_philo *philo, long time)
{
    int i;

    i = 0;
    while (i < philo->number)
    {
        if (time - philo->last_meal[i] > philo->time_to_die && philo->eating[i] == false && philo->sleeping[i] == false)
            return (true);
        else
            i++;
    }
    return (false);
}

int taking_fork(t_philo     *philo, int position)
{

}

void    *start_life(void    *accept)
{
    t_philo *philo = (t_philo *)accept;////// the key is hererererrererer
    int position;
    int n_eat;
    int i;

    n_eat = 0;
    i = -1;
    while (i++ < philo->number)
        philo->last_meal[i] = get_time();
    if (philo->limit_times_must_eat == -1)
        n_eat = -10;
    /*
    * i have to check for his left and right fork
    * i have to take two fork or relase he fork
    * i have to start eating on eating the main thread should be checking if some one is dead
    * i have to be apply to select the philospher that how will eat
    */
    while (philo->Dead_flag == false && philo->limit_times_must_eat > n_eat)
    {
        if (n_eat == -10)
            n_eat = -10;
        else
            n_eat++;
        philo_taking_fork();
        philo_eating();
        philo_sleeping();
    }
}

void   philo_create(t_arg *info, t_philo *philo)
{
    int i;
    t_philospher    *P;

    i = 0;
    philo->mutex = malloc(sizeof(pthread_mutex_t) * info->data[0]);
    philo->thread = malloc(sizeof(pthread_t) * info->data[0]);
    philo->last_meal = malloc(sizeof(long) * info->data[0]);
    philo->eating  = malloc(sizeof(bool) * info->data[0]);
    philo->sleeping  = malloc(sizeof(bool) * info->data[0]);
    P = malloc(sizeof(t_philospher) * info->data[0]);
    philo->number = info->data[0];
    philo->time_to_die = info->data[1];
    philo->time_to_eat = info->data[2];
    philo->time_to_sleep = info->data[3];
    if (info->number == 6)
        philo->limit_times_must_eat = info->data[4];
    else
        philo->limit_times_must_eat = -1;
    while (i < philo->number)
    {
        philo->eating[i] = false;
        philo->sleeping[i] = false;
        philo->last_meal[i] = false;
        P[i].id = i;
        P[i].philo = philo;
        if(pthread_create(&philo->thread[i], NULL, start_life, &P[i]) != 0)
            exit(0);
        if (pthread_mutex_init(&philo->mutex[i], NULL) != 0)
            exit(0);
        i++;
    }
    i = 0;
    while (i < philo->number)
    {
        pthread_join(philo->thread[i], NULL);
        i++;
    }
    free(P);
}

int main(int argn, char **argv)
{
    t_arg   info;
    t_philo philo;
    int i;

    i = 0;
    if (argn == 6 || argn == 5)
    {
        info.number = argn;
        info.arg = argv;
        philo.Dead_flag = false;
        check_ready_arg(&info);
        philo_create(&info, &philo);
    }
    else
        error("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
    ending_program(&info, &philo);
}