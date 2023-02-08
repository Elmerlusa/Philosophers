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

void	print_state(struct timeval start, t_philo philo, char *action)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo.attention);
	printf("%ld %i %s\n", (time.tv_sec - start.tv_sec) * 1000
		+ (time.tv_usec - start.tv_usec) / 1000, philo.id, action);
	pthread_mutex_unlock(philo.attention);
	return ;
}

void	*routine(void *ptr)
{
	t_seat_philo	*seat;
	struct timeval	start;

	seat = (t_seat_philo *)ptr;
	gettimeofday(&start, NULL);
	while (seat->philo.num_meals)
	{
		pthread_mutex_lock(seat->right_fork);
		print_state(start, seat->philo, MSG_FORK);
		pthread_mutex_lock(seat->left_fork);
		print_state(start, seat->philo, MSG_FORK);
		print_state(start, seat->philo, MSG_EATING);
		if (usleep(seat->philo.time_eat * 1000) == -1)
			return (NULL);
		pthread_mutex_unlock(seat->right_fork);
		pthread_mutex_unlock(seat->left_fork);
		print_state(start, seat->philo, MSG_SLEEPING);
		if (usleep(seat->philo.time_sleep * 1000) == -1)
			return (NULL);
		print_state(start, seat->philo, MSG_THINKING);
		if (seat->philo.flag_meals == 1)
			seat->philo.num_meals -= 1;
	}
	if (seat->philo.num_meals != 0)
		print_state(start, seat->philo, MSG_DIED);
	return (NULL);
}

pthread_t	*create_threads(unsigned int num_threads)
{
	pthread_t	*threads;

	threads = (pthread_t *)ft_calloc(num_threads, sizeof(pthread_t));
	if (threads == NULL)
		return (NULL);
	return (threads);
}

void	start_threads(t_seat_philo *table, unsigned int num_threads)
{
	pthread_t		*threads;
	unsigned int	index;

	index = 0;
	threads = create_threads(num_threads);
	if (threads == NULL)
		return ;
	while (index < num_threads)
	{
		if (pthread_create(threads + index, NULL, routine,
				(void *) &table[index]) || usleep(100) == -1)
		{
			free(threads);
			return ;
		}
		index++;
	}
	index = 0;
	while (index < num_threads)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
	free(threads);
	return ;
}
