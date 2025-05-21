/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:25:05 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/21 11:55:23 by oachbani         ###   ########.fr       */
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


typedef struct s_philo
{
    int     nb_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     nb_eat_time;
}           t_philo;


long    ft_atoi(char *str);
int	    ft_isdigit(int c);
#endif