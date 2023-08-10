#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef long long	t_time;

typedef struct s_philo
{
	int				who;
	int				m_count;
	int				is_eating;
	long int		last_eat;
	long int		limit;
	struct s_data	*datas;
	int				is_dead;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
}		t_philo;

typedef struct s_data
{
	int				total_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_dead;
	int				eat_count_max;
	unsigned long	start_time;
	t_philo			*philo;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	pprint;
	pthread_mutex_t	check_d;
}		t_data;

int		ft_dead_check(t_philo *philo);
void	*philo_life(void *philos);
void	ft_set_args(int ac, char **av, t_data *data);
t_time	get_tick_count(void);
int		check(t_philo *philo);
void	take_fork(t_philo *philo);
void	ft_sleep_time(int ttime, t_philo *philo);
void	ft_set_philos(t_data *data);
int		ft_atoi(char *str);
void	free_data(t_data *data);
void	one_philo(t_philo *philo);
void	last_eat(t_philo *philo);
void	philo_finished_eating(t_philo *philo);
void	ft_sleep_time_2(int ttime, t_philo *philo);

#endif