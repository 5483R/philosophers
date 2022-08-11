/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:27:11 by schoukou          #+#    #+#             */
/*   Updated: 2022/06/28 00:40:43 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	organis_data(int ac, char **av, t_table *data)
{
	data->nmb_philo = ft_atoi(av[1]);
	data->philo = malloc(sizeof(t_philo) * data->nmb_philo);
	if (!data->philo)
	{
		return (0);
	}
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->die = 0;
	if (ac == 6)
		data->nbr_eat = ft_atoi(av[5]);
	else
		data->nbr_eat = -1;
	if (!organis_philos(data))
		return (0);
	return (1);
}

int	organis_philos(t_table *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nmb_philo);
	if (!forks)
		return (0);
	i = 0;
	while (i < data->nmb_philo)
	{
		data->philo[i].index = i;
		data->philo[i].nbr_time_eat = 0;
		data->philo[i].eating = 0;
		data->philo[i].time_start = current_time();
		data->philo[i].last_time_eat = current_time();
		data->philo[i].forks = forks;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

void	mutex(t_table *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->nmb_philo)
		pthread_mutex_init(&data->philo->forks[i++], NULL);
}

void	print(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->print);
	if (i == 1)
		printf("%ld		Philo Number	%d		Taken fork\n",
			(current_time() - philo->time_start), philo->index + 1);
	if (i == 2)
		printf("%ld		Philo Number	%d		Taken fork\n",
			(current_time() - philo->time_start), philo->index + 1);
	if (i == 3)
		printf("%ld		Philo Number	%d		is Eating\n",
			(current_time() - philo->time_start), philo->index + 1);
	if (i == 4)
		printf("%ld		Philo Number	%d		is sleeping\n",
			(current_time() - philo->time_start), philo->index + 1);
	if (i == 5)
		printf("%ld		Philo Number	%d		is Thinking\n",
			(current_time() - philo->time_start), philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!philo->data->die && philo->nbr_time_eat != philo->data->nbr_eat)
	{
		pthread_mutex_lock(&philo->forks[philo->index]);
		print(philo, 1);
		pthread_mutex_lock(&philo->forks[(philo->index + 1)
			% philo->data->nmb_philo]);
		print(philo, 2);
		print(philo, 3);
		philo->eating = 1;
		philo->last_time_eat = current_time();
		timeto(philo->data->time_eat);
		print(philo, 4);
		philo->nbr_time_eat++;
		philo->eating = 0;
		pthread_mutex_unlock(&philo->forks[philo->index]);
		pthread_mutex_unlock(&philo->forks[(philo->index + 1)
			% philo->data->nmb_philo]);
		timeto(philo->data->time_sleep);
		print(philo, 5);
	}
	return (0);
}
