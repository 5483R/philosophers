/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:45:18 by schoukou          #+#    #+#             */
/*   Updated: 2022/08/10 23:32:19 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct s_table	t_table;
typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int					index;
	pthread_t			thread;
	int					nbr_time_eat;
	int					eating;
	long				time_start;
	long				last_time_eat;
	pthread_mutex_t		*forks;
	t_table				*data;
}	t_philo;

struct s_table
{
	t_philo			*philo;
	int				nmb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	int				die;
	pthread_mutex_t	print;
};

int			check_char(char *str);
int			ft_atoi(const char *str);
int			check_argc(int ac, char **av);
int			print_return(char *s1, char *s2);
int			organis_data(int ac, char **av, t_table *data);
int			organis_philos(t_table *data);
void		mutex(t_table *data);
void		createthread(t_table *data);
void		*routine(void *arg);
long		current_time(void);
void		timeto(long int time_to_sleep);
void		print(t_philo *philo, int i);
int			is_all_ate(t_table *data);
void		if_death(t_philo *philo);

#endif
