/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:42:24 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/27 08:17:55 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define LOCK 2
# define UNLOCK 1
# define FAIL -1
# define SUCCESS 1
# define THINKING 9
# define SLEEPING 8
# define EATING 7
# define TAKE_FORK1 11
# define TAKE_FORK2 10
# define YES 1
# define NO 0

# define ARG_NUMBER_ERR "Error: Invalid number of arguments. try again\n"
# define NOT_VALID "Error: the number is not valid try another one\n"
# define NEGATIVE "Error : negative numbers is invalid\n"
# define NOT_LOGIC "Error : please use a logic number and try again\n"
# define MUTEX_FAIL "Error : the mutex fail to initialise try again\n"
# define MALLOC_FAIL "Error : the malloc just faild\n"
# define THREAD_FAIL "Error : failed to create a thread\n"
# define FORK_MESSAGE "has taken a fork\n"
# define EATING_MESSAGE "is eating\n"
# define SLEEPING_MESSAGE "is sleeping\n"
# define THINKING_MESSAGE "is thinking\n"
# define DEAD_MESSAGE "died\n"

#endif
