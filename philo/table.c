/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 23:48:18 by javmarti          #+#    #+#             */
/*   Updated: 2023/02/07 23:48:18 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_table(t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;

	index = 0;
	while (index < num_philo)
	{
		pthread_mutex_destroy(table[index].right_fork);
		free(table[index].right_fork);
		pthread_mutex_destroy(table[index].philo.last_meal_mtx);
		free(table[index].philo.last_meal_mtx);
		pthread_mutex_destroy(table[index].philo.num_meals_mtx);
		free(table[index].philo.num_meals_mtx);
		index++;
	}
	pthread_mutex_destroy(table->philo.attention);
	free(table->philo.attention);
	free(table);
	return ;
}

void	create_mutexes(t_philo *new_philo)
{
	new_philo->last_meal_mtx
		= (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (new_philo->last_meal_mtx != NULL
		&& pthread_mutex_init(new_philo->last_meal_mtx, NULL))
	{
		free(new_philo->last_meal_mtx);
		new_philo->last_meal_mtx = NULL;
	}
	new_philo->num_meals_mtx
		= (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (new_philo->num_meals_mtx != NULL
		&& pthread_mutex_init(new_philo->num_meals_mtx, NULL))
	{
		free(new_philo->num_meals_mtx);
		new_philo->num_meals_mtx = NULL;
	}
	return ;
}

static t_philo	copy_philo(unsigned int index, t_philo philo)
{
	t_philo	new_philo;

	new_philo.id = index + 1;
	new_philo.time_die = philo.time_die;
	new_philo.time_eat = philo.time_eat;
	new_philo.time_sleep = philo.time_sleep;
	new_philo.num_meals = philo.num_meals;
	new_philo.flag_meals = philo.flag_meals;
	new_philo.attention = philo.attention;
	create_mutexes(&new_philo);
	return (new_philo);
}

void	assing_fork(t_seat_philo *table, unsigned int index,
	pthread_mutex_t **right_fork, unsigned int num_philo)
{
	table[index].right_fork = *right_fork;
	if (index != num_philo - 1)
		table[index + 1].left_fork = *right_fork;
	else
		table[0].left_fork = *right_fork;
	return ;
}

t_seat_philo	*prepare_table(unsigned int num_philo, t_philo philo)
{
	t_seat_philo	*table;
	pthread_mutex_t	*right_fork;
	unsigned int	index;

	table = (t_seat_philo *)ft_calloc(num_philo, sizeof(t_seat_philo));
	if (table == NULL)
		return (NULL);
	index = 0;
	while (index < num_philo)
	{
		table[index].philo = copy_philo(index, philo);
		right_fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		if (right_fork == NULL || pthread_mutex_init(right_fork, NULL) != 0
			|| table[index].philo.num_meals_mtx == NULL
			|| table[index].philo.last_meal_mtx == NULL)
		{
			clean_table(table, index + 1);
			return (NULL);
		}
		assing_fork(table, index, &right_fork, num_philo);
		index++;
	}
	return (table);
}
