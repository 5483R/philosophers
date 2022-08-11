/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:41:36 by schoukou          #+#    #+#             */
/*   Updated: 2022/08/11 01:09:48 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	current_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((((long)time.tv_sec) * 1000) + (time.tv_usec / 1000));
}

void	timeto(long int time_to_sleep)
{
	long int	s_time;

	s_time = current_time();
	while ((current_time() - s_time) < time_to_sleep)
		usleep(2000);
}

int	is_all_ate(t_table *data)
{
	int	i;

	i = 0;
	while (i < data->nmb_philo)
	{
		if (data->philo[i].nbr_time_eat < data->nbr_eat)
			return (0);
		i++;
	}
	return (1);
}

void	if_death(t_philo *philo)
{
	t_table	*data;
	int		i;

	data = philo->data;
	i = 0;
	while (1)
	{	
		i %= philo->data->nmb_philo;
		if (current_time() - philo[i].last_time_eat >= data->time_die
			&& !philo[i].eating)
		{
			data->die = 1;
			printf("%ld		Philo Number	%d		Died \n",
				(current_time() - philo->time_start), philo->index + 1);
			return ;
		}
		if (data->nbr_eat != -1 && is_all_ate(data))
			return ;
		i++;
	}
}

void	createthread(t_table *data)
{
	pthread_t	*tid;
	int			i;

	tid = malloc(sizeof(data->nmb_philo));
	i = 0;
	while (i < data->nmb_philo)
	{
		pthread_create(&tid[i], NULL, &routine, &data->philo[i]);
		usleep(60);
		i++;
	}
	if_death(data->philo);
		i = 0;
	while (i < data->nmb_philo)
		pthread_mutex_destroy(&data->philo->forks[i++]);
	pthread_mutex_destroy(&data->print);
}
