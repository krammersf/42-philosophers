/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 09:48:08 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->dead, NULL);
	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philos[i].status_mutex, NULL);
	}
}

int	init_table(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->fork_taken = malloc(sizeof(int) * table->num_philos);
	ft_bzero(table->fork_taken, sizeof(int) * table->num_philos);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	ft_bzero(table->philos, sizeof(t_philo) * table->num_philos);
	if (table->philos == NULL || table->forks == NULL)
		return (printf("Error: Failed to allocate memory\n"), 0);
	init_mutexes(table);
	table->start_time = now();
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].time_last_eat = table->start_time;
		table->philos[i].table = table;
		table->philos[i].l_fork = i;
		table->philos[i].r_fork = (i + 1) % table->num_philos;
	}
	return (1);
}

int	put_args(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		return (printf(MSG_1));
	if (ft_atoi2(av[1]) < 1 || ft_atoi2(av[2]) < 1
		|| ft_atoi2(av[3]) < 1 || ft_atoi2(av[4]) < 1
		|| (ac == 6 && ft_atoi2(av[5]) < 0))
		return (printf("Error: Invalid arguments\n"));
	if (ac == 6 && ft_atoi2(av[5]) == 0)
		return (1);
	table->num_philos = ft_atoi2(av[1]);
	table->time_to_stop = ft_atoi2(av[2]);
	table->time_to_eat = ft_atoi2(av[3]);
	table->time_to_sleep = ft_atoi2(av[4]);
	if (ac == 6)
		table->num_of_meals = ft_atoi2(av[5]);
	else
		table->num_of_meals = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	ft_bzero(&table, sizeof(t_table));
	put_args(ac, av, &table);
	init_table(&table);
	threads(&table);
	free_table(&table);
	return (0);
}
