/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/21 17:39:23 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_arg(char *str)
{
    int i;

    i = -1;
    if (str[0] == '-' || str[0] == '+')
    {
        if (str[0] == '-')
        {
            printf(NEGATIVE);
            exit(EXIT_FAILURE);
        }
        str += 1;
    }
    while (str[++i])
        if (!ft_isdigit(str[i]))
        {
            printf(NOT_VALID);
            exit(EXIT_FAILURE);
        }
    if (ft_atoi(str) > INT_MAX || ft_atoi(str) == 0)
    {
        printf(NOT_LOGIC);
        exit(EXIT_FAILURE);
    }
}

t_philo fill_struct(char **av)
{
    t_philo philo;

    philo.nb_philo = ft_atoi(av[1]);
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep= ft_atoi(av[4]);
    if (av[5])
        philo.nb_eat_time= ft_atoi(av[5]);
    return(philo);
}

t_philo ft_parsing(int  ac, char **av)
{
    int i;
    t_philo philo;

    i = 0;
    if (ac != 5 && ac != 6)
    {
        printf(ARG_NUMBER_ERR);
        exit(EXIT_FAILURE);
    }
    while (av[++i])
        check_arg(av[i]);
    philo = fill_struct(av);
    return(philo);   
}


int main (int ac, char **av)
{
    t_philo ph_data;

    ph_data = ft_parsing(ac, av);
    printf("the number of philos is %d\n", ph_data.nb_philo);
    printf("the time to die is %d\n", ph_data.time_to_die);
    printf("the time to eat is %d\n", ph_data.time_to_eat);
    printf("the time to sleep is %d\n", ph_data.time_to_sleep);
    printf("the number of times each philo should eat is %d\n ", ph_data.nb_eat_time);
        
        

}