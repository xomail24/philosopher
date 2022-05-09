/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:37:48 by icheri            #+#    #+#             */
/*   Updated: 2022/05/09 18:38:23 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	join_and_free_philosophers(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_join(info->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&info->philosophers[i++].check_mutex);
	}
	free(info->philosophers);
	i = 0;
	while (i < info->num_of_philosophers)
		pthread_mutex_destroy(&info->forks[i++]);
	free(info->forks);
}

static void	create_philosophers(t_info *info)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		info->philosophers[i].last_time_to_eat = info->create_at;
		pthread_create(&info->philosophers[i].thread, NULL, \
			action_philosopher, &info->philosophers[i]);
		pthread_create(&thread, NULL, monitor, &info->philosophers[i]);
		pthread_detach(thread);
		++i;
	}
	if (info->num_of_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitor_each_must_eat, info);
		pthread_detach(thread);
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (ft_puterror("ERROR: wrong arg's\n"));
	if (initialization_philosophers(&info, argc, argv))
		return (1);
	create_philosophers(&info);
	join_and_free_philosophers(&info);
	return (0);
}
