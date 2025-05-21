/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:27 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/21 12:35:22 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_arg(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        str + 1;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            printf(NOT_VALID);
            exit(EXIT_FAILURE);
        }       
    }
}

t_philo ft_parsing(int  ac, char **av)
{
    int i;

    i = 0;
    if (ac != 5 && ac != 6)
    {
        printf(ARG_NUMBER_ERR);
        exit(EXIT_FAILURE);
    }
    while (av[++i])
        check_arg(av[i]);
    
}


int main (int ac, char **av)
{
    ft_parsing(ac, av);
}