/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/29 11:38:16 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *dta)
{
	t_philo	*philo;

	philo = (t_philo *)dta;
	while (!is_finish(philo->data))
	{
		if (philo->id % 2 != 0)
			usleep(500);
		get_forks(philo);
		ft_printf(philo, EATING_MESSAGE);
		pthread_mutex_lock(&philo->data->mutex_lst_eat);
		philo->last_time_eat = get_curr_time();
		pthread_mutex_unlock(&philo->data->mutex_lst_eat);
		pthread_mutex_lock(&philo->data->mutex_meal);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->data->mutex_meal);
		wait_sleep(philo->data->time_to_eat, philo);
		put_forks(philo);
		ft_printf(philo, SLEEPING_MESSAGE);
		wait_sleep(philo->data->time_to_sleep, philo);
		ft_printf(philo, THINKING_MESSAGE);
	}
	return (NULL);
}

void	check_meal_count(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mutex_meal);
	while (data->nb_eat_time != -1 && i < data->nb_philo)
	{
		if (data->philo[i].count_meals < data->nb_eat_time)
			break ;
		i++;
	}
	pthread_mutex_unlock(&data->mutex_meal);
	if (i == data->nb_philo)
	{
		pthread_mutex_lock(&data->mutex_death);
		data->is_dead = YES;
		pthread_mutex_unlock(&data->mutex_death);
	}
}

void	*check_death(void *arg)
{
	t_data			*data;
	int				i;
	unsigned long	time_eat;

	data = (t_data *)arg;
	while (!is_finish(data))
	{
		i = 0;
		while (i < data->nb_philo && !is_finish(data))
		{
			pthread_mutex_lock(&data->mutex_lst_eat);
			time_eat = get_curr_time() - data->philo[i].last_time_eat;
			pthread_mutex_unlock(&data->mutex_lst_eat);
			if (time_eat > (unsigned long)data->time_to_die)
			{
				print_modify_death(data, i);
				return (NULL);
			}
			i++;
		}
		check_meal_count(data);
		wait_sleep(5, data->philo);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;
	int	res;

	i = -1;
	get_time(&data);
	res = pthread_create(&data->monitor_th_id, NULL, check_death, data);
	if (res != 0)
		return (FAIL);
	while (++i < data->nb_philo)
	{
		res = pthread_create(&data->philo[i].thread_id, NULL, routine,
				&data->philo[i]);
		if (res != 0)
			return (FAIL);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	*ph_data;
	int		i;

	ph_data = ft_parsing(ac, av);
	if (!ph_data)
		return (EXIT_FAILURE);
	else if (ph_data->nb_philo == 1)
	{
		printf("0 : 1 : has taken a fork\n");
		usleep(ph_data->time_to_die * 1000);
		printf("%d : 1 died\n", ph_data->time_to_die);
		return (SUCCESS);
	}
	else if (init_mutex(ph_data) == -1)
		return (printf(MUTEX_FAIL), EXIT_FAILURE);
	else if (create_threads(ph_data) == -1)
		return (printf(THREAD_FAIL), ft_destroy(ph_data), EXIT_FAILURE);
	i = -1;
	while (++i < ph_data->nb_philo)
		pthread_join(ph_data->philo[i].thread_id, NULL);
	pthread_join(ph_data->monitor_th_id, NULL);
	ft_destroy(ph_data);
}
