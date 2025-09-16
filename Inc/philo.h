/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:46:40 by eliagarc          #+#    #+#             */
/*   Updated: 2024/01/10 17:16:11 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				n_philo;
	unsigned long	time_die;
	int				time_eat;
	int				time_sleep;
	int				n_time_eat;
	unsigned long	actual_time;
	int				is_end;
}					t_philo;

typedef struct s_meeting
{
	t_philo			**philosophers;
	pthread_mutex_t	*forks;
	int				n_philos;
	int				is_dead;
	size_t			meet_time;
	int				all_eat;
	pthread_mutex_t	philo;
	pthread_mutex_t	dead;
	pthread_mutex_t	time;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
}					t_meeting;

typedef struct s_args
{
	t_philo		*philo;
	t_meeting	*round;
}				t_args;

/* AUXILIAR FUNCTIONS */
long	ft_atoi(const char *str);
void	free_round(t_meeting *round);
size_t	get_current_time(void);
int		all_philos_eat(t_meeting *round);
void	print_mut(char *message, t_meeting *round, t_philo *philo);
void	waiter(t_meeting *round);
void	ft_usleep(long time);
int		out_of_time(t_meeting *round, int i);

/* INIT FUNCTIONS*/
int		init_round(t_meeting **round, char **argv);
int		start_philo(int argc, char **argv, t_meeting *round);
int		init_threads(t_philo *philo, t_meeting *round, char **argv, int argc);

/* CHECKER FUNCTIONS */
int		is_nbrvalid(char *s);
int		check_input(int argc, char **argv);
int		ft_isdigit(int c);

/* PHILO FUNCTIONS */
void	*time_to_eat(void *arg);
int		ft_eat(t_args *param);
int		ft_sleep(t_args *param);
void	ft_end(t_args *param);
int		ft_dead(t_args *param);
int		ft_take_forks(t_args *param, int n_philo);
int		ft_leave_forks(t_args *param, int n_philo);
int		ft_think(t_args *param);

#endif