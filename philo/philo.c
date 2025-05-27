/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/27 08:39:29 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_finish(t_data *data)
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
void ft_printf(t_philo *philo, char *msg)
{
	unsigned long current_time;

	pthread_mutex_lock(&philo->data->mutex_printf);
	if (!is_finish(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mutex_printf);
		return ;
	}

	current_time = get_curr_time();
	printf("%ld  %d  %s", current_time - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

void get_forks(t_philo *philo)
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

void put_forks(t_philo *philo)
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

void *routine(void *dta)
{
	t_philo *philo = (t_philo *)dta;

	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_finish(philo->data))
	{
		get_forks(philo);

		pthread_mutex_lock(&philo->data->mutex_lst_eat);
		philo->last_time_eat = get_curr_time();
		pthread_mutex_unlock(&philo->data->mutex_lst_eat);
		ft_printf(philo, EATING_MESSAGE);
		wait_sleep(philo->data->time_to_eat, philo);

		put_forks(philo);
		ft_printf(philo, SLEEPING_MESSAGE);
		wait_sleep(philo->data->time_to_sleep, philo);

		ft_printf(philo, THINKING_MESSAGE);
	}
	return (NULL);
}

void *check_death(void *arg)
{
	t_data *data;
	int i;
	unsigned long time_eat;

	data = (t_data *)arg;

	while (!is_finish(data))
	{
		usleep(100);
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->mutex_lst_eat);
			time_eat = get_curr_time()- data->philo[i].last_time_eat;
			pthread_mutex_unlock(&data->mutex_lst_eat);

			if ( time_eat >= (unsigned long)data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_death);
				data->is_dead = YES;
				pthread_mutex_unlock(&data->mutex_death);

				pthread_mutex_lock(&data->mutex_printf);
				printf("%ld %d is died\n", get_curr_time() - data->start_time, data->philo[i].id);
				pthread_mutex_unlock(&data->mutex_printf);

				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int create_threads(t_data *data)
{
	int i;
	int res;

	if (data->nb_philo == 1)
	{
		printf("0 : 1 : has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%d : 1 died\n", data->time_to_die);
		return (SUCCESS);
	}
	i = -1;
	get_time(&data);
	res = pthread_create(&data->monitor_th_id, NULL, check_death, data);
	if (res != 0)
		return (FAIL);
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
		return (printf(THREAD_FAIL), ft_destroy(ph_data), EXIT_FAILURE);
	i = -1;
	while (++i < ph_data->nb_philo)
		pthread_join(ph_data->philo[i].thread_id, NULL);
	pthread_join(ph_data->monitor_th_id, NULL);
	ft_destroy(ph_data);
}
