#include "philo.h"

void	ft_check_finish(t_philo *philo, t_data *data)
{
	int	i;
	int	x;

	if (philo->who == philo->datas->total_philos)
	{
		i = -1;
		while (++i < philo->datas->total_philos)
		{
			if (data->philo[i].m_count == data->eat_count_max)
				x = 1;
			else
				x = 0;
		}
		if (philo->datas->eat_count_max == philo->m_count && x == 1)
		{
			pthread_mutex_lock(&philo->datas->m_stop);
			pthread_mutex_lock(&philo->datas->pprint);
			philo->datas->eat_count_max = -2;
		}
	}
}

void	ft_print(t_philo *philo, char c)
{
	if (c == 'e')
	{
		pthread_mutex_lock(&philo->datas->pprint);
		printf("%llu  %d is eating \n", \
			get_tick_count() - philo->datas->start_time, philo->who);
		pthread_mutex_unlock(&philo->datas->pprint);
	}
	else if (c == 's')
	{
		pthread_mutex_lock(&philo->datas->pprint);
		printf("%llu  %d is sleeping \n", \
			get_tick_count() - philo->datas->start_time, philo->who);
		pthread_mutex_unlock(&philo->datas->pprint);
	}
	else if (c == 't')
	{
		pthread_mutex_lock(&philo->datas->pprint);
		printf("%llu  %d is thinking \n", \
			get_tick_count() - philo->datas->start_time, philo->who);
		pthread_mutex_unlock(&philo->datas->pprint);
	}
}

void	one_philo(t_philo *philo)
{
	if (philo->datas->total_philos == 1)
	{
		ft_sleep_time(philo->datas->time_to_die, philo);
		philo->is_dead = 1;
		philo->datas->is_dead = 1;
	}
}

void	*checks_3(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1 && !(philo->datas->eat_count_max > 0))
	{
		pthread_mutex_lock(&philo->datas->dead);
		if (get_tick_count() > philo->last_eat + philo->datas->time_to_die)
		{
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->datas->dead);
			pthread_mutex_lock(&philo->datas->pprint);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->datas->dead);
		usleep(1000);
	}
	return ((void *)0);
}

void	*philo_life(void *philos)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philos;
	pthread_create(&tid, NULL, &checks_3, philos);
	pthread_detach(tid);
	if (philo->who % 2 == 0)
		ft_sleep_time(philo->datas->time_to_eat, philo);
	while (!(check(philo)) && philo->datas->eat_count_max != philo->m_count)
	{
		take_fork(philo);
		pthread_mutex_lock(&philo->datas->m_stop);
		check(philo);
		ft_print(philo, 'e');
		last_eat(philo);
		philo_finished_eating(philo);
		ft_print(philo, 's');
		ft_sleep_time(philo->datas->time_to_sleep, philo);
		ft_print(philo, 't');
	}
	ft_check_finish(philo, philo->datas);
	return (NULL);
}
