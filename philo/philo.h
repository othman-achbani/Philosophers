/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:25:05 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/29 09:59:25 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	unsigned long		last_time_eat;
	int					count_meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat_time;
	unsigned long		start_time;
	unsigned long		current_time;
	int					is_dead;
	pthread_t			monitor_th_id;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		wake_up;
	pthread_mutex_t		mutex_printf;
	pthread_mutex_t		mutex_lst_eat;
	pthread_mutex_t		mutex_death;
	pthread_mutex_t		mutex_meal;
	t_philo				*philo;
};

void					print_modify_death(t_data *data, int i);
void					put_forks(t_philo *philo);
void					ft_destroy(t_data *philo);
int						init_mutex(t_data *philo);
void					wait_sleep(int sleep_time, t_philo *philo);
void					get_time(t_data **data);
int						check_arg(char *str);
t_data					*ft_parsing(int ac, char **av);
t_data					*fill_struct(char **av);
void					fill_private_philo_data(t_data *data);
long					ft_atoi(char *str);
int						ft_isdigit(int c);
long					get_curr_time(void);
int						is_finish(t_data *data);
void					ft_printf(t_philo *philo, char *msg);
void					get_forks(t_philo *philo);

#endif
