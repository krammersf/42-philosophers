/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 09:48:14 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	satisfied_or_someone_died(t_philo *philo)
{
	if (philo->table->num_of_meals && philo->meal_count == \
		philo->table->num_of_meals)
	{
		pthread_mutex_lock(&philo->status_mutex);
		philo->status = SATISFIED;
		pthread_mutex_unlock(&philo->status_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->table->dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead);
	return (0);
}

long long	now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * MILSEG + time.tv_usec / MILSEG);
}

void	try_to_pause_to_sleep(t_philo *philo, long long time_to_stop)
{
	long long	begin;

	begin = now();
	while (satisfied_or_someone_died(philo) == 0
		&& (now() - begin) < time_to_stop)
		usleep(100);
}

void	try_to_pause_to_eat(t_philo *philo, long long start_time)
{
	long long	time_start_eating;

	if (satisfied_or_someone_died(philo) == 0
		&& print_action(philo, EATING))
	{
		time_start_eating = now() - start_time;
		usleep((philo->table->time_to_eat - time_start_eating) * MILSEG);
		if (philo->table->num_of_meals > 0)
			philo->meal_count++;
	}
}
