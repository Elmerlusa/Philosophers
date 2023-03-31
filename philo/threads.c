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

void	set_num_meals(int n, t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;

	index = 0;
	while (index < num_philo)
	{
		pthread_mutex_lock(table[index].philo.num_meals_mtx);
		table[index].philo.num_meals = n;
		pthread_mutex_unlock(table[index].philo.num_meals_mtx);
		index++;
	}
	return ;
}

int	all_finished(t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;
	unsigned int	num_meals;

	index = 0;
	while (index < num_philo)
	{
		pthread_mutex_lock(table[index].philo.num_meals_mtx);
		num_meals = table[index].philo.num_meals;
		pthread_mutex_unlock(table[index].philo.num_meals_mtx);
		if (num_meals != 0)
			return (0);
		index++;
	}
	return (1);
}

void	check_deads(t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;
	long			last_meal_time;
	unsigned int	num_meals;

	index = 0;
	while (all_finished(table, num_philo) == 0)
	{
		pthread_mutex_lock(table[index].philo.num_meals_mtx);
		num_meals = table[index].philo.num_meals;
		pthread_mutex_unlock(table[index].philo.num_meals_mtx);
		if (num_meals > 0)
		{
			pthread_mutex_lock(table[index].philo.last_meal_mtx);
			last_meal_time = table[index].philo.last_meal_time;
			pthread_mutex_unlock(table[index].philo.last_meal_mtx);
			if (get_exec_time() - last_meal_time > table[index].philo.time_die)
			{
				print_state(table[index].philo, MSG_DIED);
				set_num_meals(0, table, num_philo);
				break ;
			}
		}
		if (++index == num_philo)
			index = 0;
	}
}

void	wait_threads(pthread_t *threads, unsigned int num_threads)
{
	unsigned int	index;

	if (num_threads == 1)
	{
		pthread_detach(threads[0]);
		return ;
	}
	index = 0;
	while (index < num_threads)
		pthread_join(threads[index++], NULL);
	return ;
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
				(void *) &table[index]) || usleep(25) == -1)
		{
			free(threads);
			set_num_meals(0, table, num_threads);
			return ;
		}
		index++;
	}
	check_deads(table, num_threads);
	wait_threads(threads, num_threads);
	free(threads);
	return ;
}
