/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:20:43 by schoukou          #+#    #+#             */
/*   Updated: 2022/06/28 00:26:57 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
			sign = -sign;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}	
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (sign * nb);
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_argc(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!check_char(av[i])
			|| ft_atoi(av[i]) <= 0)
		{
			printf("Wrong input");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*data;

	if (ac == 6 || ac == 5)
	{
		if (!check_argc(ac, av))
			return (0);
		data = malloc(sizeof(t_table));
		if (!data)
			return (0);
		if (!organis_data(ac, av, data))
		{
			return (0);
		}
		mutex(data);
		createthread(data);
	}
	else
		printf("wrong Arguments");
	return (0);
}
