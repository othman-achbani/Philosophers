/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/25 09:31:19 by oachbani         ###   ########.fr       */
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
	pthread_mutex_init(&philo->mutex_printf, NULL);
	pthread_mutex_init(&philo->mutex_lst_eat, NULL);
	pthread_mutex_init(&philo->mutex_death, NULL);
	return (0);
}

void	wait_sleep(int	sleep_time, t_philo *philo)
{
	long	start;

	start = get_curr_time();
	while(get_curr_time() - start <= sleep_time)
	{
		if (should_quit(philo))
			break;
		usleep(100);
	}
}

long get_curr_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void complete_printing(int order, t_philo *philo)
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
		wait_sleep(philo->data->time_to_sleep , philo);
	}
}

void 	print_situation(int order, t_philo *philo)
{
	long time;

	if (should_quit	(philo))
		return ;
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
		philo->last_time_eat = get_curr_time();
		pthread_mutex_unlock(&philo->data->mutex_printf);
		wait_sleep(philo->data->time_to_eat , philo);
	}
	else
		complete_printing(order, philo);
}

void mutex_lock_unlock_even(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(philo->right_fork);
		print_situation(TAKE_FORK1, philo);
		pthread_mutex_lock(philo->left_fork);
		print_situation(TAKE_FORK2, philo);
		// pthread_mutex_lock (&philo->data->mutex_lst_eat);
	}
	else if (key == UNLOCK)
	{
		// pthread_mutex_unlock(&philo->data->mutex_lst_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void mutex_lock_unlock_odd(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		print_situation(TAKE_FORK1, philo);
		pthread_mutex_lock(philo->right_fork);
		print_situation(TAKE_FORK2, philo);
		// pthread_mutex_lock (&philo->data->mutex_lst_eat);
	}
	else if (key == UNLOCK)
	{
		// pthread_mutex_unlock(&philo->data->mutex_lst_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

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
		usleep(90);
	while (!should_quit(philo))
	{
		if (philo->id % 2 == 0)
		{
			mutex_lock_unlock_even(philo, LOCK);
			// philo->last_time_eat = get_curr_time();
			mutex_lock_unlock_even(philo, UNLOCK);
		}
		else
		{
			mutex_lock_unlock_odd(philo, LOCK);
			// philo->last_time_eat = get_curr_time();
			mutex_lock_unlock_odd(philo, UNLOCK);
		}
		print_situation(SLEEPING, philo);
		print_situation(THINKING, philo);
	}
	return (NULL);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	i = -1;
	while(data->is_dead == NO)
	{
		i++;
		if (get_curr_time() - data->philo[i].last_time_eat >(unsigned long) data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_death);
			data->is_dead = YES;
			printf(DEAD_MESSAGE, get_curr_time() - data->start_time, data->philo[i].id);
			pthread_mutex_unlock(&data->mutex_death);
		}
		if (data->philo[i].id == data->nb_philo)
			i = -1;
		usleep(data->time_to_die);
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
		return (printf(THREAD_FAIL), EXIT_FAILURE);
	i = -1;
	while (++i < ph_data->nb_philo)
		pthread_join(ph_data->philo[i].thread_id, NULL);
}
