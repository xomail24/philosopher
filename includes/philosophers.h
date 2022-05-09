/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:32:42 by icheri            #+#    #+#             */
/*   Updated: 2022/05/09 18:33:17 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FT_SUCCESS	0
# define FT_ERROR	1

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_info	*info;
	struct timeval	last_time_to_eat;
}				t_philosopher;

typedef struct s_info
{
	int				num_of_philosophers;
	int				num_of_eat_finish_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	struct timeval	create_at;
}				t_info;

int			ft_puterror(char *err_msg);
int			ft_atoi(const char *nptr);
void		print_philosophers_msg(t_philosopher *philosopher, char *str);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);

void		*action_philosopher(void *argv);
int			initialization_philosophers(t_info *info, int argc, char *argv[]);
void		*monitor_each_must_eat(void *argv);
void		*monitor(void *argv);

#endif
