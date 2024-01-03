/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 10:09:47 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_philo *philo)
{
	print_action(philo, SLEEPING);
	if (print_action(philo, SLEEPING))
		try_to_pause_to_sleep(philo, philo->table->time_to_sleep);
	return (satisfied_or_someone_died(philo) == 0);
}

void	drop_forks(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->table->forks[id - 1]);
	philo->table->fork_taken[id - 1] = 0;
	pthread_mutex_unlock(&philo->table->forks[id - 1]);
	pthread_mutex_lock(&philo->table->forks[id % philo->table->num_philos]);
	philo->table->fork_taken[id % philo->table->num_philos] = 0;
	pthread_mutex_unlock(&philo->table->forks[id % philo->table->num_philos]);
}

void	try_to_pick_up_forks(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->table->forks[id - 1]);
	while (philo->table->fork_taken[id - 1])
	{
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		satisfied_or_someone_died(philo);
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	}
	philo->table->fork_taken[id - 1] = 1;
	pthread_mutex_unlock(&philo->table->forks[id - 1]);
	print_action(philo, TAKE);
	pthread_mutex_lock(&philo->table->forks[id % philo->table->num_philos]);
	while (philo->table->fork_taken[id % philo->table->num_philos])
	{
		pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
		satisfied_or_someone_died(philo);
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	}
	philo->table->fork_taken[id % philo->table->num_philos] = 1;
	pthread_mutex_unlock(&philo->table->forks[id % philo->table->num_philos]);
	print_action(philo, TAKE);
}

int	eat(t_philo *philo, int id)
{
	long long	current_time;

	if (philo->table->num_philos == 1)
		return (print_action(philo, TAKE), STOP);
	try_to_pick_up_forks(philo, id);
	current_time = now();
	pthread_mutex_lock(&philo->status_mutex);
	philo->time_last_eat = current_time;
	pthread_mutex_unlock(&philo->status_mutex);
	try_to_pause_to_eat(philo, current_time);
	drop_forks(philo, id);
	return (satisfied_or_someone_died(philo) == 0);
}

void	*star_dinner(void *ptr)
{
	t_philo		*philo;
	long long	time_pause_even;

	philo = (t_philo *)ptr;
	time_pause_even = philo->table->time_to_eat * (philo->id % 2 == 0) * MILSEG;
	usleep(time_pause_even);
	while (1)
	{
		if (eat(philo, philo->id) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (print_action(philo, THINKING) == 0)
			break ;
	}
	return (NULL);
}
