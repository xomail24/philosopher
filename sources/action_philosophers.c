/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:34:55 by icheri            #+#    #+#             */
/*   Updated: 2022/05/14 19:20:04 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	take_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right);
	print_philosophers_msg(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->left);
	print_philosophers_msg(philosopher, "has taken a fork");
}

static void	eating(t_philosopher *philosopher)
{
	long long	ms;

	pthread_mutex_lock(&philosopher->check_mutex);
	gettimeofday(&philosopher->last_time_to_eat, NULL);
	ms = time_to_ms(philosopher->last_time_to_eat) - \
		time_to_ms(philosopher->info->create_at);
	pthread_mutex_lock(&philosopher->info->finish_mutex);
	if (!philosopher->info->finish)
		printf("%lld\t%d\t %s\n", ms, philosopher->n + 1, "is eating");
	philosopher->num_of_eat += 1;
	if (philosopher->num_of_eat == philosopher->info->num_of_must_eat)
		philosopher->info->num_of_eat_finish_philosophers += 1;
	pthread_mutex_unlock(&philosopher->info->finish_mutex);
	usleep(philosopher->info->time_to_eat * 1000);
	pthread_mutex_unlock(philosopher->right);
	pthread_mutex_unlock(philosopher->left);
	pthread_mutex_unlock(&philosopher->check_mutex);
}

static void	sleeping(t_philosopher *philosopher)
{
	print_philosophers_msg(philosopher, "is sleeping");
	usleep(philosopher->info->time_to_sleep * 1000);
}

static void	thinking(t_philosopher *philosopher)
{
	print_philosophers_msg(philosopher, "is thinking");
}

void	*action_philosopher(void *argv)
{
	t_philosopher	*philosopher;

	philosopher = argv;
	if (philosopher->n % 2 == 0)
		usleep(philosopher->info->time_to_eat * 1000);
	while (!philosopher->info->finish)
	{
		take_fork(philosopher);
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
