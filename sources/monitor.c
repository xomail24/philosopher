/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:39:41 by icheri            #+#    #+#             */
/*   Updated: 2022/05/09 18:40:22 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;

	info = argv;
	while (!info->finish)
	{
		pthread_mutex_lock(&info->finish_mutex);
		if (info->num_of_eat_finish_philosophers == info->num_of_philosophers)
			info->finish = 1;
		pthread_mutex_unlock(&info->finish_mutex);
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philosopher	*philosopher;
	struct timeval	now;
	long long		ms;

	philosopher = argv;
	while (!philosopher->info->finish)
	{
		pthread_mutex_lock(&philosopher->check_mutex);
		pthread_mutex_lock(&philosopher->info->finish_mutex);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philosopher->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philosopher->info->time_to_die \
			&& philosopher->info->finish == 0)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philosopher->info->create_at), \
				philosopher->n + 1, "died");
			philosopher->info->finish = 1;
		}
		pthread_mutex_unlock(&philosopher->info->finish_mutex);
		pthread_mutex_unlock(&philosopher->check_mutex);
	}
	return (NULL);
}
