/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:25:05 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/24 17:37:27 by oachbani         ###   ########.fr       */
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
	int last_time_eat;
	int count_meals;
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
	pthread_mutex_t *mutex;
	pthread_mutex_t	mutex_printf;
	t_philo			*philo;
} ;

void	get_time(t_data **data);
int check_arg(char *str, int key);
t_data *ft_parsing(int ac, char **av);
t_data *fill_struct(char **av);
void	fill_private_philo_data(t_data *data);
long ft_atoi(char *str);
int ft_isdigit(int c);


#endif
