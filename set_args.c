#include "philo.h"

int	check_args(t_data *data, int ac)
{
	if (data->total_philos <= 0)
		return (1);
	if (ac == 6)
		if (data->eat_count_max <= 0)
			return (1);
	if (data->time_to_eat < 60 || data->time_to_die < 60)
		return (1);
	if (data->time_to_sleep < 60)
		return (1);
	return (0);
}

void	ft_set_args(int ac, char **av, t_data *data)
{
	data->total_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_count_max = ft_atoi(av[5]);
	if (check_args(data, ac))
	{
		printf("Invalid arguments. \n");
		free(data);
		exit(0);
	}
	if (ac != 6)
		data->eat_count_max = -1;
	data->start_time = get_tick_count();
	pthread_mutex_init(&(data->m_stop), NULL);
	pthread_mutex_init(&(data->dead), NULL);
	pthread_mutex_init(&(data->pprint), NULL);
	pthread_mutex_init(&(data->m_eat), NULL);
}

void	ft_set_philos(t_data *data)
{
	long	i;

	i = -1;
	while (++i < data->total_philos)
	{
		data->philo[i].who = i + 1;
		data->philo[i].last_eat = get_tick_count();
		data->philo[i].datas = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].left_fork), NULL);
		if (i == data->total_philos - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		pthread_create(&data->philo[i].thread, NULL, \
			&philo_life, &(data->philo[i]));
		pthread_detach(data->philo[i].thread);
	}
}
