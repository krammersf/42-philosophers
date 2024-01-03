/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:44:53 by fde-carv          #+#    #+#             */
/*   Updated: 2023/10/23 18:07:56 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

// define colours
# define RED_COLOR		"\033[1;31m"
# define GREEN_COLOR	"\033[1;32m"
# define YELLOW_COLOR	"\033[1;33m"
# define BLUE_COLOR		"\033[1;34m"
# define MAGENTA_COLOR	"\033[1;35m"
# define CYAN_COLOR		"\033[1;36m"
# define WHITE_COLOR	"\033[1;37m"
# define RED_BG			"\033[1;41m"
# define GREEN_BG		"\033[1;42m"
# define YELLOW_BG		"\033[1;43m"
# define BLUE_BG		"\033[1;44m"
# define MAGENTA_BG		"\033[1;45m"
# define CYAN_BG		"\033[1;46m"
# define WHITE_BG		"\033[1;47m"
# define BLACK_COLOR	"\033[1;30m"
# define RESET_COLOR	"\033[0m"

// define variables
# define TAKE "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED " died\n"

// define messages
# define FINISH_MSG "\n  \033[1;42m\033[1;30m All philosophers eat \
enough and are full !!! \033[0;0m  🍖 🍔 🍰\n"
# define MEALS_0_MSG "\n  \033[1;44m\033[1;97m Philosophers don't eat \
!!! \033[0;0m  😡 🍔 😭\n"
# define LINE "\n"
# define DEAD_MSG "\n  \033[1;41m\033[1;97m One philosopher is dead !!! \
\033[0;0m 😭 😡 👻\n"
# define DEAD_MSG_1 "\n  \033[1;41m\033[1;97m Philosopher"
# define DEAD_MSG_2 "is dead !!! \033[0;0m  😭 😡 👻\n%s"

# define MSG_1 "\033[1;31mError: \033[1;34mUsage: \033[1;33m<num_philos> <time_to_stop> \
<time_to_eat> <time_to_sleep> \033[1;93m[num_of_meals]\033[0m\n"

// define flags
# define EAT 1
# define SLEEP 2
# define DONE 1
# define SATISFIED 2
# define STOP 0
# define DIE 1

// define time
# define MILSEG 1000

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				status;
	int				l_fork;
	int				r_fork;
	long long		time_last_eat;
	pthread_mutex_t	status_mutex;
	pthread_t		thread;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_stop;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;

	int				*fork_taken;
	struct s_philo	*philos;
}				t_table;

/* ------ main.c ------ */
void		init_mutexes(t_table *table);
int			init_table(t_table *table);
int			put_args(int ac, char **av, t_table *table);

/* ------ print.c ------ */
const char	*get_color_for_id(int philosophers_id);
int			ft_strcmp(const char *s1, const char *s2);
int			print_action(t_philo *philo, char *status);

/* ------ routine_utils.c ------ */
int			satisfied_or_someone_died(t_philo *philo);
long long	now(void);
void		try_to_pause_to_sleep(t_philo *philo, long long time_to_stop);
void		try_to_pause_to_eat(t_philo *philo, long long start_time);

/* ------ routine.c ------ */
void		drop_forks(t_philo *philo, int id);
void		try_to_pick_up_forks(t_philo *philo, int id);
int			sleeping(t_philo *philo);
int			eat(t_philo *philo, int id);
void		*star_dinner(void *ptr);

/* ------ threads.c ------ */
void		print_dead(t_philo *philo);
void		print_finish_message(int satisfied_count, int num_philos, \
								t_table *t);
int			limit(t_philo *philo, t_table *table);
int			monitor(t_table *table);
int			threads(t_table *args);

/* ------ utils.c ------ */
void		free_table(t_table *table);
int			ft_atoi2(const char *str);
void		ft_bzero(void *str, size_t n);

#endif
