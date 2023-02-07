/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:15:18 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/30 13:15:18 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(int philosopher, char *action)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %i %s\n", time.tv_usec / 1000, philosopher, action);
	return ;
}

void	*routine(void *ptr)
{
	t_seat_philo	*seat;

	seat = (t_seat_philo *)ptr;
	printf(">>%i\n", seat->philo.id);
	// while (1)
	// {
	// 	print_message(philo->philo_id, MSG_THINKING);
	// 	print_message(philo->philo_id, MSG_FORK);
	// 	print_message(philo->philo_id, MSG_EATING);
	// 	if (usleep(philo->time_eat) == -1)
	// 		return (NULL);
	// 	print_message(1, MSG_SLEEPING);
	// 	if (usleep(philo->time_sleep) == -1)
	// 		return (NULL);
	// }
	// print_message(1, MSG_DIED);
	return (NULL);
}
