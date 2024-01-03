/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/24 09:48:11 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

const char	*get_color_for_id(int philosophers_id)
{
	const char	*colors[] = {
		RED_COLOR,
		GREEN_COLOR,
		YELLOW_COLOR,
		BLUE_COLOR,
		MAGENTA_COLOR,
		CYAN_COLOR,
		WHITE_BG RED_COLOR,
		RED_BG BLACK_COLOR,
		GREEN_BG BLACK_COLOR,
		YELLOW_BG BLACK_COLOR,
		BLUE_BG BLACK_COLOR,
		MAGENTA_BG BLACK_COLOR,
		CYAN_BG BLACK_COLOR,
		WHITE_BG BLACK_COLOR,
		RED_BG WHITE_COLOR,
		GREEN_BG RED_COLOR,
		YELLOW_BG RED_COLOR,
		BLUE_BG WHITE_COLOR,
		MAGENTA_BG WHITE_COLOR,
		CYAN_BG WHITE_COLOR,
		WHITE_BG BLUE_COLOR,
	};

	return (colors[philosophers_id % (sizeof(colors) / sizeof(colors[0]))]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	print_action(t_philo *philo, char *status)
{
	const char	*color;
	long long	time;

	pthread_mutex_lock(&philo->table->dead);
	if (philo->table->someone_died)
		return (pthread_mutex_unlock(&philo->table->dead), 0);
	pthread_mutex_unlock(&philo->table->dead);
	pthread_mutex_lock(&philo->table->print);
	time = now() - philo->table->start_time;
	if (ft_strcmp(status, EATING) == 0)
	{
		color = get_color_for_id(philo->id);
		printf("%lld %s%d %s\033[0m\n", time, color,
			philo->id, status);
	}
	else
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}
