/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:46:54 by javmarti          #+#    #+#             */
/*   Updated: 2023/02/09 12:46:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_exec_time(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	print_state(t_philo philo, char *action)
{
	if (philo.num_meals == 0)
		return ;
	pthread_mutex_lock(philo.attention);
	printf("%ld %i %s\n", get_exec_time() - philo.sit_time, philo.id, action);
	pthread_mutex_unlock(philo.attention);
	return ;
}

void	philo_eat(t_seat_philo *seat)
{
	pthread_mutex_lock(seat->left_fork);
	print_state(seat->philo, MSG_FORK);
	pthread_mutex_lock(seat->right_fork);
	print_state(seat->philo, MSG_FORK);
	print_state(seat->philo, MSG_EATING);
	seat->philo.last_meal_time = get_exec_time();
	return ;
}

void	*routine(void *ptr)
{
	t_seat_philo	*seat;

	seat = (t_seat_philo *)ptr;
	seat->philo.sit_time = get_exec_time();
	seat->philo.last_meal_time = seat->philo.sit_time;
	while (1)
	{
		philo_eat(seat);
		if (usleep(seat->philo.time_eat * 1000) == -1)
			return (NULL);
		pthread_mutex_unlock(seat->left_fork);
		pthread_mutex_unlock(seat->right_fork);
		if (seat->philo.flag_meals == 1)
			seat->philo.num_meals -= 1;
		if (seat->philo.num_meals == 0)
			break ;
		print_state(seat->philo, MSG_SLEEPING);
		if (usleep(seat->philo.time_sleep * 1000) == -1)
			return (NULL);
		print_state(seat->philo, MSG_THINKING);
	}
	return (NULL);
}
