/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:36:36 by icheri            #+#    #+#             */
/*   Updated: 2022/05/09 18:36:55 by icheri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_puterror(char *err_msg)
{
	char	*begin_msg;

	begin_msg = err_msg;
	while (*err_msg)
		err_msg++;
	write(2, begin_msg, err_msg - begin_msg);
	return (FT_ERROR);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	while (*nptr == '\f' || *nptr == '\r' || *nptr == ' '
		|| *nptr == '\t' || *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		result = (result * 10) + (*nptr++ - '0');
	return (result * sign);
}

void	print_philosophers_msg(t_philosopher *philosopher, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philosopher->info->finish_mutex);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philosopher->info->create_at);
	if (!philosopher->info->finish)
		printf("%lld\t%d\t %s\n", ms, philosopher->n + 1, str);
	pthread_mutex_unlock(&philosopher->info->finish_mutex);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (FT_ERROR);
	memset(*(void **)dst, 0, size);
	return (FT_SUCCESS);
}

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}
