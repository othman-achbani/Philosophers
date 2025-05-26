/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock_unlock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:48:28 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/26 19:03:28 by oachbani         ###   ########.fr       */
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

void	wait_sleep(int	sleep_time, t_philo *philo)
{
	// long	start;

	// start = get_curr_time();
	// while(get_curr_time() - start <= sleep_time)
	// {
	// 	if (should_quit(philo))
	// 		break;
	// 	usleep(100);
	// }
    long long    current_time;

    (void)philo;
    current_time = get_curr_time(philo);
    while (1)
    {
        if (should_quit(philo))
            break;
        if (get_curr_time(philo) >= sleep_time + current_time)
            break;
        usleep(500);
    }
}

long get_curr_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void mutex_lock_unlock_even(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(philo->right_fork);
		if (print_situation(TAKE_FORK1, philo) == -1)
			return ;
		pthread_mutex_lock(philo->left_fork);
		if(print_situation(TAKE_FORK2, philo) == -1)
			return ;
	}
	else if (key == UNLOCK)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void mutex_lock_unlock_odd(t_philo *philo, int key)
{
	if (key == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_situation(TAKE_FORK1, philo) == -1)
			return ;
		pthread_mutex_lock(philo->right_fork);
		if(print_situation(TAKE_FORK2, philo) == -1)
			return ;
	}
	else if (key == UNLOCK)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
