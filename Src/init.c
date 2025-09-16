/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:48:05 by eliagarc          #+#    #+#             */
/*   Updated: 2024/01/10 18:33:49 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/philo.h"

int	init_mutex(t_meeting **round)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(*round)->philo, NULL) != 0)
		return (free((*round)->philosophers), free(&(*round)), -1);
	if (pthread_mutex_init(&(*round)->dead, NULL) != 0)
		return (free((*round)->philosophers), free(&(*round)), -1);
	if (pthread_mutex_init(&(*round)->time, NULL) != 0)
		return (free((*round)->philosophers), free(&(*round)), -1);
	if (pthread_mutex_init(&(*round)->print, NULL) != 0)
		return (free((*round)->philosophers), free(&(*round)), -1);
	if (pthread_mutex_init(&(*round)->end, NULL) != 0)
		return (free((*round)->philosophers), free(&(*round)), -1);
	while (i < (*round)->n_philos)
	{
		if (pthread_mutex_init(&(*round)->forks[i], NULL) != 0)
			return (free((*round)->philosophers), free(&(*round)), -1);
		i++;
	}
	return (0);
}

int	init_round(t_meeting **round, char **argv)
{
	(*round) = (t_meeting *)malloc(sizeof(t_meeting));
	if (!(*round))
		return (-1);
	(*round)->n_philos = (int)ft_atoi(argv[1]);
	(*round)->forks = (pthread_mutex_t *)malloc((*round)->n_philos \
	* (sizeof(pthread_mutex_t)));
	(*round)->is_dead = 0;
	(*round)->all_eat = 0;
	(*round)->philosophers = (t_philo **)malloc((*round)->n_philos \
	* sizeof(t_philo *));
	if (!(*round)->philosophers)
		return (free((*round)), -1);
	if (init_mutex(round) == -1)
		return (-1);
	return (0);
}

int	start_philo(int argc, char **argv, t_meeting *round)
{
	int	i;

	i = 0;
	if (init_round(&round, argv) == -1)
		return (-1);
	while (i < round->n_philos)
	{
		round->philosophers[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!round->philosophers[i])
			return (free(round->philosophers), free(round), -1);
		round->philosophers[i]->n_philo = i + 1;
		if (init_threads(round->philosophers[i], round, argv, argc) == -1)
			return (free(round), -1);
		i++;
	}
	waiter(round);
	i = 0;
	while (i < round->n_philos)
	{
		if (pthread_join(round->philosophers[i]->thread_id, NULL) != 0)
			return (-1);
		i++;
	}
	free_round(round);
	return (0);
}

int	all_philos_eat(t_meeting *round)
{
	pthread_mutex_lock(&round->philo);
	if (round->all_eat == round->n_philos)
	{
		printf("All philosophers have finished!\n");
		pthread_mutex_unlock(&round->philo);
		return (1);
	}
	pthread_mutex_unlock(&round->philo);
	return (0);
}

int	init_threads(t_philo *philo, t_meeting *round, char **argv, int argc)
{
	t_args	*aux;

	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->is_end = -1;
	if (argc == 6)
		philo->n_time_eat = ft_atoi(argv[5]);
	else
		philo->n_time_eat = -1;
	aux = (t_args *)malloc(sizeof(t_args));
	if (!aux)
		return (-1);
	pthread_mutex_lock(&round->time);
	round->meet_time = get_current_time();
	pthread_mutex_unlock(&round->time);
	philo->actual_time = round->meet_time;
	aux->philo = philo;
	aux->round = round;
	if (pthread_create(&philo->thread_id, NULL, time_to_eat, aux) != 0)
		return (-1);
	return (0);
}
