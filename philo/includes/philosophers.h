/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:55:29 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/17 21:55:29 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define MSG_FORK "has taken a fork"
# define MSG_THINKING "is thinking"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_DIED "died"

typedef struct s_philo {
	unsigned int	id;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	num_meals;
	unsigned int	flag_meals;
	long			sit_time;
	long			last_meal_time;
	pthread_mutex_t	*attention;
	pthread_mutex_t	*num_meals_mtx;
	pthread_mutex_t	*last_meal_mtx;
}	t_philo;

typedef struct s_seat_philo {
	t_philo			philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_seat_philo;

void			*ft_calloc(size_t count, size_t size);
unsigned int	check_uint(char *str_num);

t_seat_philo	*prepare_table(unsigned int num_philo, t_philo philo);
void			clean_table(t_seat_philo *table, unsigned int num_philo);

#endif