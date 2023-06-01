/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:24:37 by msintas-          #+#    #+#             */
/*   Updated: 2023/05/12 12:17:45 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int ft_atoi(const char *str)
{
    int result;
    int i;
    int neg;

    result = 0;
    i = 0;
    neg = 1;
    while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            neg = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (str[i] - '0');
        str++;
    }
    result = result * neg;
    return (result);
}

long int	ft_long_atoi(const char *str)
{
	int			i;
	long int	sum;
	int			neg;

	i = 0;
	sum = 0;
	neg = 1;
	while (str[i])
	{
		while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' || \
					str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
			i++;
		if (str[i] == '-' || str[i] == '+')
			if (str[i++] == '-')
				neg = -1;
		while (str[i] && ((str[i] >= '0' && str[i] <= '9')))
		{
			sum = (sum * 10) + (str[i] - '0');
			i++;
		}
		return (sum * neg);
	}
	return (0);
}


