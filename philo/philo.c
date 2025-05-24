/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/24 17:37:57 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex(t_data *philo)
{
	int i;
	int checker;

	i = -1;
	while (++i < philo->nb_philo)
	{
		checker = pthread_mutex_init(&philo->mutex[i], NULL);
		if (checker != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philo->mutex[i]);
			return (FAIL);
		}
	}
	checker = pthread_mutex_init(&philo->mutex_printf, NULL);
	if (checker != 0)
	{
		pthread_mutex_destroy(&philo->mutex_printf);
		return (FAIL);
	}
	return (0);
}

long get_curr_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void complete_printing(int order, t_philo *philo) // no need
{
	long time;

	if (order == THINKING)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		printf(THINKING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
	else if (order == SLEEPING)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		printf(SLEEPING_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

void print_situation(int order, t_philo *philo)
{
	long time;

	if (order == TAKE_FORK1)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		printf(FORK_MESSAGE, time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_printf);
	}
	else if (order == TAKE_FORK2)
	{
		time = get_curr_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->mutex_printf);
		printf(FORK_MESSAGE, time, philo->id);
		printf(EATING_MESSAGE, time, philo->id);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->data->mutex_printf);
		usleep(philo->data->time_to_eat * 1000);
	}
	else
		complete_printing(order, philo);
}

void mutex_lock_unlock_even(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(&philo->data->mutex[(philo->id + 1) % philo->data->nb_philo]);
		print_situation(TAKE_FORK1, philo);
		pthread_mutex_lock(&philo->data->mutex[philo->id]);
		print_situation(TAKE_FORK2, philo);
	}
	else if (key == UNLOCK)
	{
		pthread_mutex_unlock(&philo->data->mutex[(philo->id + 1) % philo->data->nb_philo]);
		pthread_mutex_unlock(&philo->data->mutex[philo->id]);
	}
}

void mutex_lock_unlock_odd(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(&philo->data->mutex[philo->id]);
		print_situation(TAKE_FORK1, philo);
		pthread_mutex_lock(&philo->data->mutex[(philo->id + 1) % philo->data->nb_philo]);
		print_situation(TAKE_FORK2, philo);
	}
	else if (key == UNLOCK)
	{
		pthread_mutex_unlock(&philo->data->mutex[philo->id]);
		pthread_mutex_unlock(&philo->data->mutex[(philo->id + 1) % philo->data->nb_philo]);
	}
}

int should_quit(t_philo *philo)
{
	if (philo->data->nb_eat_time != -1 && philo->count_meals == philo->data->nb_eat_time)
		return (1);
	return (0);
}

void *routine(void *dta)
{
	t_philo *philo = (t_philo *)dta;

	if (philo->id % 2 == 0)
		usleep(100);
	while (!should_quit(philo))
	{
		if (philo->id % 2 == 0)
		{
			mutex_lock_unlock_even(philo, LOCK);
			mutex_lock_unlock_even(philo, UNLOCK);
		}
		else
		{
			mutex_lock_unlock_odd(philo, LOCK);
			mutex_lock_unlock_odd(philo, UNLOCK);
		}
		print_situation(SLEEPING, philo);
		print_situation(THINKING, philo);
	}
	return (NULL);
}

int create_threads(t_data *data)
{
	int i;
	int res;

	i = -1;
	get_time(&data);
	while (++i < data->nb_philo)
	{
		res = pthread_create(&data->philo[i].thread_id, NULL, routine, &data->philo[i]);
		if (res != 0)
			return (FAIL);
	}
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_data *ph_data;
	int i;

	ph_data = ft_parsing(ac, av);
	if (!ph_data)
		return (EXIT_FAILURE);
	else if (init_mutex(ph_data) == -1)
		return (printf(MUTEX_FAIL), EXIT_FAILURE);
	else if (create_threads(ph_data) == -1)
		return (printf(THREAD_FAIL), EXIT_FAILURE);
	i = -1;
	while (++i < ph_data->nb_philo)
		pthread_join(ph_data->philo[i].thread_id, NULL);
}
