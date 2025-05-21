/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:30:52 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/21 11:54:47 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    ft_atoi(char *str)
{
	int 	    i;
	long	    d;
	long        r;

	i = 0;
	d = 1;
	r = 0;
	while ((str[i] >= '\t' && str[i] <= '\r' ) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			d = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * d);
}

int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}