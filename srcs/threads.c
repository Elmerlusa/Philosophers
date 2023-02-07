/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:04:28 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/30 13:04:28 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr);

void	start_threads(t_seat_philo *table, unsigned int num_threads)
{
	pthread_t		threads[num_threads];
	unsigned int	index;

	index = 0;
	while (index < num_threads)
	{
		pthread_create(threads + index, NULL, routine, (void *) &table[index]);
		index++;
	}
	index = 0;
	while (index < num_threads)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
	return ;
}
