/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock_unlock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:48:28 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/29 09:58:56 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *philo)
{
	int	i;
	int	checker;

	i = -1;
	while (++i < philo->nb_philo)
	{
		checker = pthread_mutex_init(&philo->mutex[i], NULL);
		if (checker != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philo->mutex[i]);
			free(philo->mutex);
			free(philo->philo);
			free(philo);
			return (FAIL);
		}
	}
	pthread_mutex_init(&philo->mutex_meal, NULL);
	pthread_mutex_init(&philo->mutex_printf, NULL);
	pthread_mutex_init(&philo->mutex_lst_eat, NULL);
	pthread_mutex_init(&philo->mutex_death, NULL);
	pthread_mutex_init(&philo->wake_up, NULL);
	return (0);
}

void	wait_sleep(int sleep_time, t_philo *philo)
{
	long	start;

	start = get_curr_time();
	while (get_curr_time() - start < sleep_time)
	{
		usleep(100);
		if (is_finish(philo->data))
			return ;
	}
}

void	print_modify_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_death);
	data->is_dead = YES;
	pthread_mutex_unlock(&data->mutex_death);
	pthread_mutex_lock(&data->mutex_printf);
	printf("%lu %d %s", get_curr_time() - data->start_time, data->philo[i].id,
		DEAD_MESSAGE);
	pthread_mutex_unlock(&data->mutex_printf);
}

long	get_curr_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
