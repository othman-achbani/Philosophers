/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_and_waiting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:45:57 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/26 17:33:07 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	complete_printing_v2(int order, t_philo *philo)
{
	long	time;

	if (order == TAKE_FORK1)
	{
		time = get_curr_time() - philo->data->start_time;

		pthread_mutex_lock(&philo->data->mutex_printf);
		if (should_quit	(philo))
		{
			pthread_mutex_unlock(&philo->data->mutex_printf);
			return -1 ;
		}
		printf(FORK_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
	return (0);
}

int complete_printing(int order, t_philo *philo)
{
	long time;

	if (order == THINKING)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		if (should_quit(philo))
		{
			pthread_mutex_unlock(&philo->data->mutex_printf);
			return -1 ;
		}
		printf(THINKING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
	if (order == SLEEPING)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		if (should_quit	(philo))
		{
			pthread_mutex_unlock(&philo->data->mutex_printf);
			return -1;
		}
		printf(SLEEPING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
		wait_sleep(philo->data->time_to_sleep , philo);
	}
	else
		return(complete_printing_v2(order, philo));
	return (0);
}

int	print_situation(int order, t_philo *philo)
{
	long time;

	if (should_quit	(philo))
			return -1;
	if (order == TAKE_FORK2)
	{
		time = get_curr_time() - philo->data->start_time;
		if (should_quit(philo))
		{
			return -1;
		}
		pthread_mutex_lock(&philo->data->mutex_printf);
		printf(FORK_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
		// printf(EATING_MESSAGE, time, philo->id);
		pthread_mutex_lock(&philo->data->mutex_meal);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->data->mutex_meal);
		pthread_mutex_lock(&philo->data->mutex_lst_eat);
		philo->last_time_eat = get_curr_time();
		pthread_mutex_unlock(&philo->data->mutex_lst_eat);
		// wait_sleep(philo->data->time_to_eat , philo);
	}
	else
		return(complete_printing(order, philo));
	return (1);
}
