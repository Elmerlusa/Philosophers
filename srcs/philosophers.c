/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:58:41 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/17 21:58:41 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	parse_input(char **argv, int argc);
int		check_input(t_philo philo, int argc);
void	start_threads(t_seat_philo *table, unsigned int num_threads);

int	main(int argc, char *argv[])
{
	t_philo			philo;
	int				num_threads;
	t_seat_philo	*table;

	if (argc != 5 && argc != 6)
		return (0);
	printf("HOLA");
	philo = parse_input(argv, argc);
	num_threads = check_uint(argv[1]);
	if (philo.time_die == 0 || philo.time_eat == 0 ||
		philo.time_sleep == 0 || philo.num_meals == 0 ||
		num_threads == 0)
		return (0);
	table = prepare_table(num_threads, philo);
	start_threads(table, num_threads);
	clean_table(table, num_threads);
	return (0);
}
