#include "philo.h"

int	ft_dead_check(t_philo *philo)
{
	int	j;

	pthread_mutex_lock(&philo->datas->dead);
	j = 0;
	while (j < philo->datas->total_philos)
	{
		if (philo[j].is_dead == 1)
		{
			printf("%lld %d is dead.\n", \
				get_tick_count() - philo->datas->start_time, philo[j].who);
			return (j);
		}
		j++;
	}
	pthread_mutex_unlock(&philo->datas->dead);
	return (-1);
}

int	check(t_philo *philo)
{
	pthread_mutex_lock(&philo->datas->dead);
	if (get_tick_count() >= philo->datas->time_to_die + philo->last_eat)
	{
		philo->datas->is_dead = 1;
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->datas->dead);
		pthread_mutex_lock(&philo->datas->pprint);
		return (0);
	}
	pthread_mutex_unlock(&philo->datas->m_stop);
	pthread_mutex_unlock(&philo->datas->dead);
	return (0);
}
