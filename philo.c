#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork));
	pthread_mutex_lock(&philo->datas->pprint);
	printf("%llu  %d has taken a fork \n",
		get_tick_count() - philo->datas->start_time, philo->who);
	pthread_mutex_unlock(&philo->datas->pprint);
	one_philo(philo);
	pthread_mutex_lock((philo->right_fork));
	pthread_mutex_lock(&philo->datas->pprint);
	printf("%llu  %d has taken a fork \n",
		get_tick_count() - philo->datas->start_time, philo->who);
	pthread_mutex_unlock(&philo->datas->pprint);
}

void	ft_sleep_time(int ttime, t_philo *philo)
{
	t_time	time;

	time = get_tick_count();
	while (get_tick_count() - time < (t_time)ttime && !check(philo))
		usleep(100);
}

void	free_data(t_data *data)
{
	long	i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_mutex_destroy(&(data->philo[i].left_fork));
		usleep(50);
	}
	free(data->philo);
	pthread_mutex_destroy(&(data->dead));
	pthread_mutex_destroy(&(data->m_stop));
	pthread_mutex_destroy(&(data->m_eat));
	pthread_mutex_destroy(&(data->pprint));
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments.\n");
		exit(0);
	}
	data = malloc(sizeof(t_data));
	ft_set_args(argc, argv, data);
	data->philo = malloc(sizeof(t_philo) * data->total_philos);
	ft_set_philos(data);
	while (1)
	{
		if (ft_dead_check(data->philo) != -1)
			break ;
		if (data->eat_count_max == -2)
		{
			printf("There's no food left in the pot. \n");
			break ;
		}
		usleep(500);
	}
	free_data(data);
	return (0);
}
