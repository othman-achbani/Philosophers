/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:25:05 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/26 10:55:14 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include "defines.h"
#include <sys/time.h>


typedef struct s_data t_data;

typedef struct s_philo
{
	int		 id;
	pthread_t thread_id;
	unsigned long	 last_time_eat;
	int count_meals;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data *data;
} 		t_philo;

struct s_data
{
	int 			nb_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			nb_eat_time;
	unsigned long	start_time;
	unsigned long	current_time;
	int				is_dead;
	pthread_t		monitor_th_id;
	pthread_mutex_t *mutex;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t mutex_lst_eat;
	pthread_mutex_t mutex_death;
	t_philo			*philo;
} ;

void	ft_destroy(t_data *philo);
int init_mutex(t_data *philo);
void	wait_sleep(int	sleep_time, t_philo *philo);
void mutex_lock_unlock_even(t_philo *philo, int key);
void mutex_lock_unlock_odd(t_philo *philo, int key);
int should_quit(t_philo *philo);
void	get_time(t_data **data);
int check_arg(char *str, int key);
t_data *ft_parsing(int ac, char **av);
t_data *fill_struct(char **av);
void	fill_private_philo_data(t_data *data);
long ft_atoi(char *str);
int ft_isdigit(int c);
long get_curr_time();
void 	print_situation(int order, t_philo *philo);
void complete_printing(int order, t_philo *philo);
void	complete_printing_v2(int order, t_philo *philo);


#endif
