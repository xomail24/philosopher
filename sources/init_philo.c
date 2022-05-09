/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:37:04 by icheri            #+#    #+#             */
/*   Updated: 2022/05/09 18:50:29 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	parsing_arg(t_info *info, int argc, char *argv[])
{
	info->num_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_info *info, int argc)
{
	if (argc == 6 && info->num_of_must_eat <= 0)
		return (ft_puterror("ERROR: wrong num of must eat\n"));
	if (info->num_of_philosophers < 1)
		return (ft_puterror("ERROR: wrong num of philo\n"));
	if (info->time_to_die < 0)
		return (ft_puterror("ERROR: wrong time to die\n"));
	if (info->time_to_eat < 0)
		return (ft_puterror("ERROR: wrong time to eat\n"));
	if (info->time_to_sleep < 0)
		return (ft_puterror("ERROR: wrong time to sleep\n"));
	return (FT_SUCCESS);
}

static int	init_philosophers(t_info *info)
{
	int		i;

	pthread_mutex_init(&info->finish_mutex, NULL);
	if (ft_malloc(&info->philosophers, sizeof(t_philosopher) \
		* info->num_of_philosophers) || ft_malloc(&info->forks, \
		sizeof(pthread_mutex_t) * info->num_of_philosophers))
		return (ft_puterror("ERROR: malloc failed\n"));
	i = 0;
	while (i < info->num_of_philosophers)
	{
		info->philosophers[i].n = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philosophers[i].check_mutex, NULL);
		if (i == 0)
			info->philosophers[i].left \
				= &info->forks[info->num_of_philosophers - 1];
		else
			info->philosophers[i].left = &info->forks[i - 1];
		info->philosophers[i].right = &info->forks[i];
		info->philosophers[i].info = info;
		i++;
	}
	return (FT_SUCCESS);
}

int	initialization_philosophers(t_info *info, int argc, char *argv[])
{
	parsing_arg(info, argc, argv);
	if (check_info(info, argc))
		return (FT_ERROR);
	if (init_philosophers(info))
		return (FT_ERROR);
	return (FT_SUCCESS);
}
