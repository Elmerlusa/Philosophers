/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:39:11 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/30 11:39:11 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	len;

	len = count * size;
	if (len && len / count != size && count != 0)
		return (NULL);
	mem = malloc(len);
	if (mem == NULL)
		return (NULL);
	memset(mem, 0, len);
	return (mem);
}

unsigned int	ft_atoui(const char *str)
{
	unsigned int	num;

	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\v' || *str == '\r')
		str++;
	num = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (num + (*str - '0') > UINT_MAX / 10)
			return (0);
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && (s1[index] || s2[index]))
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

static size_t	num_len(int n)
{
	size_t	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int num)
{
	char	*str_num;
	size_t	size;

	size = num_len(num);
	str_num = (char *)ft_calloc(size + 1, sizeof(char));
	if (str_num == NULL)
		return (NULL);
	while (size > 0)
	{
		str_num[size - 1] = (num % 10) + '0';
		num /= 10;
		size--;
	}
	return (str_num);
}
