/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:51:59 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/27 09:21:44 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_data *philo)
{
	int	i;

	i = -1;
	while (philo->mutex && ++i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->mutex[i]);
	}
	free(philo->mutex);
	free(philo->philo);
	free(philo);
}
