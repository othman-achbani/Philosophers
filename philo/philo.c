/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/26 11:27:06 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int should_quit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->is_dead == YES)
	{
		pthread_mutex_unlock(&philo->data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
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
		usleep(500);
		print_situation(THINKING, philo);
	}
	return (NULL);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;
	unsigned	long time_eat;

	data = (t_data *) arg;
	i = -1;
	while(data->is_dead == NO)
	{
		usleep(1000);
		i++;
		pthread_mutex_lock(&data->mutex_lst_eat);
		time_eat = data->philo->last_time_eat;
		pthread_mutex_unlock(&data->mutex_lst_eat);
		if (get_curr_time() - time_eat >(unsigned long) data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_death);
			data->is_dead = YES;
			printf(DEAD_MESSAGE, get_curr_time() - data->start_time, data->philo[i].id);
			pthread_mutex_unlock(&data->mutex_death);
		}
		if (data->philo[i].id == data->nb_philo)
			i = -1;
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
	res= pthread_create(&data->monitor_th_id, NULL, check_death, data);
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
		return (printf(THREAD_FAIL),ft_destroy(ph_data), EXIT_FAILURE);
	i = -1;
	while (++i < ph_data->nb_philo)
		pthread_join(ph_data->philo[i].thread_id, NULL);
	pthread_join(ph_data->monitor_th_id, NULL);
	ft_destroy(ph_data);
}
