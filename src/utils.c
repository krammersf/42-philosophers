/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 09:48:24 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].status_mutex);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead);
	free(table->forks);
	free(table->fork_taken);
	free(table->philos);
}

int	ft_atoi2(const char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		else if (res > INT_MAX / 10 || (res == INT_MAX / 10 && \
		(*str - '0') > INT_MAX % 10))
			return (-1);
		else
			res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}

void	ft_bzero(void *str, size_t n)
{
	char	*p;

	p = str;
	while (n-- > 0)
		*p++ = '\0';
}
