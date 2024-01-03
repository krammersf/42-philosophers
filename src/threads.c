/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 09:48:27 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d%s", now() - philo->table->start_time - DIE,
		philo->id, DIED);
	usleep(200);
	printf(DEAD_MSG_1 " %d " DEAD_MSG_2, philo->id, LINE);
	pthread_mutex_unlock(&philo->table->print);
}

void	print_finish_message(int satisfied_count, int num_philos, t_table *t)
{
	if (t->num_of_meals == 0)
	{
		usleep(200);
		printf("%s\n", MEALS_0_MSG);
	}
	else if (satisfied_count == num_philos)
	{
		usleep(200);
		printf("%s\n", FINISH_MSG);
	}
}

int	limit(t_philo *philo, t_table *table)
{
	return (now() - philo->time_last_eat > table->time_to_stop);
}

int	monitor(t_table *table)
{
	int			i;
	static int	satisfied_count;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].status_mutex);
		if (table->philos[i].status == SATISFIED)
		{
			satisfied_count++;
			table->philos[i].status = DONE;
		}
		if (table->philos[i].status != DONE && limit(&table->philos[i], table))
		{
			pthread_mutex_lock(&table->dead);
			table->someone_died = 1;
			pthread_mutex_unlock(&table->dead);
			print_dead(&table->philos[i]);
			pthread_mutex_unlock(&table->philos[i].status_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].status_mutex);
	}
	print_finish_message(satisfied_count, table->num_philos, table);
	return (satisfied_count != table->num_philos);
}

int	threads(t_table *args)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&args->dead);
	while (++i < args->num_philos)
	{
		if (pthread_create(&args->philos[i].thread, NULL, \
			star_dinner, &args->philos[i]) != 0)
			return (printf("Error: Failed to create thread\n"));
	}
	args->start_time = now();
	pthread_mutex_unlock(&args->dead);
	while (monitor(args))
		continue ;
	i = -1;
	while (++i < args->num_philos)
	{
		if (pthread_join(args->philos[i].thread, NULL) != 0)
			return (printf("Error: Failed to join thread\n"));
	}
	return (0);
}
