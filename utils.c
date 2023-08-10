#include "philo.h"

t_time	get_tick_count(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	size_t	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		result = result * 10;
		result += (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->datas->m_stop);
	philo->m_count++;
	philo->last_eat = get_tick_count();
	pthread_mutex_unlock(&philo->datas->m_stop);
}

void	philo_finished_eating(t_philo *philo)
{
	ft_sleep_time(philo->datas->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->left_fork));
	pthread_mutex_unlock(philo->right_fork);
}
