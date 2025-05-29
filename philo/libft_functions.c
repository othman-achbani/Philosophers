/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:28:50 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/29 09:56:36 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	long	d;
	long	r;

	i = 0;
	d = 1;
	r = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			d = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * d);
}

int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

int	is_finish(t_data *data)
{
	pthread_mutex_lock(&data->mutex_death);
	if (data->is_dead == YES)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_death);
	return (0);
}

void	ft_printf(t_philo *philo, char *msg)
{
	unsigned long	current_time;

	pthread_mutex_lock(&philo->data->mutex_printf);
	if (is_finish(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mutex_printf);
		return ;
	}
	current_time = get_curr_time();
	printf("%lu %d %s", current_time - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, FORK_MESSAGE);
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, FORK_MESSAGE);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, FORK_MESSAGE);
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, FORK_MESSAGE);
	}
}
