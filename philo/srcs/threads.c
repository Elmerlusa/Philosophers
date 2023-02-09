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

void	print_state(t_philo philo, char *action);
void	*routine(void *ptr);
long	get_exec_time(void);

int	all_finished(t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;

	index = 0;
	while (index < num_philo)
	{
		if (table[index].philo.num_meals != 0)
			return (0);
		index++;
	}
	return (1);
}

void	check_deads(t_seat_philo *table, unsigned int num_philo)
{
	long			time;
	unsigned int	index;

	index = 0;
	while (all_finished(table, num_philo) == 0)
	{
		time = get_exec_time();
		if (time - table[index].philo.last_meal_time
			> table[index].philo.time_die
			&& table[index].philo.num_meals != 0)
		{
			pthread_mutex_lock(table[index].philo.attention);
			print_state(table[index].philo, MSG_DIED);
			pthread_mutex_unlock(table[index].philo.attention);
			break ;
		}
		index++;
		if (index == num_philo)
			index = 0;
	}
}

void	start_threads(t_seat_philo *table, unsigned int num_threads)
{
	pthread_t		*threads;
	unsigned int	index;

	threads = (pthread_t *)ft_calloc(num_threads, sizeof(pthread_t));
	if (threads == NULL)
		return ;
	index = 0;
	while (index < num_threads)
	{
		if (pthread_create(threads + index, NULL, routine,
				(void *) &table[index]) || usleep(100) == -1)
		{
			free(threads);
			return ;
		}
		pthread_detach(threads[index]);
		index++;
	}
	check_deads(table, num_threads);
	free(threads);
	return ;
}
