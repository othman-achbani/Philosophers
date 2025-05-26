/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_and_waiting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:45:57 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/26 20:11:33 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	complete_printing_v2(int order, t_philo *philo)
{
	long	time;

	if (order == TAKE_FORK1)
	{
		pthread_mutex_lock(&philo->data->mutex_printf);
		// if (should_quit	(philo))
		// {
		// 	pthread_mutex_unlock(&philo->data->mutex_printf);
		// 	return ;
		// }
		time = get_curr_time() - philo->data->start_time;
		printf(FORK_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
}

void complete_printing(int order, t_philo *philo)
{
	long time;

	if (order == THINKING)
	{
		pthread_mutex_lock(&philo->data->mutex_printf);
		// if (should_quit(philo))
		// {
		// 	pthread_mutex_unlock(&philo->data->mutex_printf);
		// 	return ;
		// }
		time = get_curr_time() - philo->data->start_time;
		printf(THINKING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
	if (order == SLEEPING)
	{
		pthread_mutex_lock(&philo->data->mutex_printf);
		// if (should_quit	(philo))
		// {
		// 	pthread_mutex_unlock(&philo->data->mutex_printf);
		// 	return ;
		// }
		time = get_curr_time() - philo->data->start_time;
		printf(SLEEPING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
		wait_sleep(philo->data->time_to_sleep , philo);
	}
	else
		complete_printing_v2(order, philo);
}

void	print_situation(int order, t_philo *philo)
{
	long time;

	if (should_quit	(philo))
			return ;
	if (order == TAKE_FORK2)
	{
		pthread_mutex_lock(&philo->data->mutex_printf);
		// if (should_quit(philo))
		// {
		// 	pthread_mutex_unlock(&philo->data->mutex_printf);
		// 	return ;
		// }
		time = get_curr_time() - philo->data->start_time;
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
		complete_printing(order, philo);
}
