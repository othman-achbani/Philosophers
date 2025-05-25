/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:30:52 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/24 17:36:54 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_arg(char *str, int key)
{
	int i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
		{
			printf(NEGATIVE);
			return (-1);
		}
		i = 0;
	}
	while (str[++i])
		if (!ft_isdigit(str[i]))
		{
			printf(NOT_VALID);
			return (-1);
		}
	if (ft_atoi(str) > INT_MAX || ft_atoi(str) <= 0)
	{
		if (key == 5 && ft_atoi(str) == 0)
			return(0);
		return (printf(NOT_LOGIC), -1);
	}
	return (0);
}

void	fill_private_philo_data(t_data *data)
{
	int	i;

	i = -1;
	while(++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].count_meals = 0;
		data->philo[i].last_time_eat = get_curr_time();
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->mutex[i];
		data->philo[i].right_fork = &data->mutex[(i + 1) %  data->nb_philo];
	}
}

t_data *fill_struct(char **av)
{
	t_data *philo;

	philo = (t_data *)malloc(sizeof(t_data));
	if (!philo)
		return (NULL);
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->is_dead = NO;
	philo->philo = malloc((philo->nb_philo) * sizeof(t_philo));
	if (av[5])
		(philo)->nb_eat_time = ft_atoi(av[5]);
	else
		(philo)->nb_eat_time = -1;
	(philo)->mutex = malloc((philo)->nb_philo * sizeof(pthread_mutex_t));
	if (!(philo)->mutex)
		return (NULL);
	fill_private_philo_data(philo);
	return (philo);
}

void	get_time(t_data **data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*data)->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

t_data *ft_parsing(int ac, char **av)
{
	int i;
	t_data *philo;

	i = 0;
	philo = NULL;
	if (ac != 5 && ac != 6)
	{
		printf(ARG_NUMBER_ERR);
		return (NULL);
	}
	while (av[++i])
		if (check_arg(av[i], i) == -1)
			return (NULL);
	philo = fill_struct(av);
	return (philo);
}
