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

void    print_state(struct timeval start, t_philo philo, char *action)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    printf("%ld %i %s\n", (time.tv_sec - start.tv_sec) * 1000 +
        (time.tv_usec - start.tv_usec) / 1000, philo.id, action);
    return ;
}

void    *routine(void *ptr)
{
    t_seat_philo    *seat;
    struct timeval  start;

    seat = (t_seat_philo *)ptr;
    gettimeofday(&start, NULL);
    while (seat->philo.num_meals)
    {
        print_state(start, seat->philo, MSG_THINKING);
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
		if (seat->philo.flag_meals == 1)
			seat->philo.num_meals -= 1;
    }
	if (seat->philo.num_meals != 0)
    	print_state(start, seat->philo, MSG_DIED);
    return (NULL);
}

