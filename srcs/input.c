/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:40:38 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/30 11:40:38 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_atoui(const char *str);
char			*ft_uitoa(unsigned int num);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

unsigned int	check_uint(char *str_num)
{
	unsigned int	number;
	char			*num;

	if (*str_num == '-')
		return (0);
	number = ft_atoui(str_num);
	num = ft_uitoa(number);
	if (num == NULL)
		return (0);
	if (ft_strncmp(str_num, num, ft_strlen(str_num)) != 0)
		number = 0;
	free(num);
	return (number);
}

t_philo	parse_input(char **argv, int argc)
{
	t_philo			philo;
	int				index;

	index = 2;
	philo.id = 0;
	philo.time_die = check_uint(argv[index++]);
	philo.time_eat = check_uint(argv[index++]);
	philo.time_sleep = check_uint(argv[index++]);
	philo.num_meals = 1;
	philo.flag_meals = 0;
	if (argc == 6)
	{
		philo.num_meals = check_uint(argv[index]);
		philo.flag_meals = 1;
	}
	return (philo);
}
