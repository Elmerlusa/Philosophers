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

static void	clean_table_error(t_seat_philo *table, unsigned int index)
{
	while (index + 1 > 0)
	{
		pthread_mutex_destroy(table[index].right_fork);
		index--;
	}
	free(table);
	return ;
}

static t_philo	copy_philo(unsigned int index, t_philo philo)
{
	t_philo	new_philo;

	new_philo.id = index;
	new_philo.time_die = philo.time_die;
	new_philo.time_eat = philo.time_eat;
	new_philo.time_sleep = philo.time_sleep;
	new_philo.num_meals = philo.num_meals;
	new_philo.flag_meals = philo.flag_meals;
	return (new_philo);
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
		right_fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		if (right_fork == NULL || pthread_mutex_init(right_fork, NULL) != 0)
		{
			clean_table_error(table, index - 1);
			return (NULL);
		}
		table[index].philo = copy_philo(index, philo);
		table[index].right_fork = right_fork;
		if (index != num_philo - 1)
			table[index + 1].left_fork = right_fork;
		else
			table[0].left_fork = right_fork;
		index++;
	}
	return (table);
}

void	clean_table(t_seat_philo *table, unsigned int num_philo)
{
	unsigned int	index;

	index = 0;
	while (index < num_philo)
	{
		pthread_mutex_destroy(table[index].right_fork);
		index++;
	}
	free(table);
	return ;
}
