/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:19:52 by eliagarc          #+#    #+#             */
/*   Updated: 2024/01/25 17:22:29 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	free_round(t_meeting *round)
{
	int	i;

	i = 0;
	while (i < round->n_philos)
	{
		pthread_mutex_unlock(&round->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&round->print);
	pthread_mutex_destroy(&round->philo);
	pthread_mutex_destroy(&round->time);
	pthread_mutex_destroy(&round->end);
	i = 0;
	while (i < round->n_philos)
	{
		pthread_mutex_destroy(&round->forks[i]);
		free(round->philosophers[i]);
		i++;
	}
	free(round->forks);
	free(round->philosophers);
	free(round);
}

int	ft_dead(t_args *param)
{
	pthread_mutex_lock(&param->round->end);
	if (param->philo->is_end == 1)
	{
		pthread_mutex_unlock(&param->round->end);
		return (1);
	}
	pthread_mutex_unlock(&param->round->end);
	pthread_mutex_lock(&param->round->dead);
	if (param->round->is_dead == 1)
	{
		pthread_mutex_unlock(&param->round->dead);
		return (1);
	}
	pthread_mutex_unlock(&param->round->dead);
	if (out_of_time(param->round, param->philo->n_philo - 1))
	{
		print_mut("is dead", param->round, param->philo);
		return (1);
	}
	return (0);
}

int	ft_take_forks(t_args *param, int n_philo)
{
	if (ft_dead(param))
		return (1);
	if (n_philo == param->round->n_philos)
	{
		pthread_mutex_lock(&param->round->forks[n_philo - 1]);
		print_mut("has taken left fork", param->round, param->philo);
		pthread_mutex_lock(&param->round->forks[0]);
		print_mut("has taken rigth fork", param->round, param->philo);
	}
	else
	{
		pthread_mutex_lock(&param->round->forks[n_philo - 1]);
		print_mut("has taken left fork", param->round, param->philo);
		pthread_mutex_lock(&param->round->forks[n_philo]);
		print_mut("has taken right fork", param->round, param->philo);
	}
	return (0);
}

int	ft_leave_forks(t_args *param, int n_philo)
{
	if (ft_dead(param))
		return (1);
	if (n_philo == param->round->n_philos)
	{
		pthread_mutex_unlock(&param->round->forks[n_philo - 1]);
		print_mut("has put down left fork", param->round, param->philo);
		pthread_mutex_unlock(&param->round->forks[0]);
		print_mut("has put down right fork", param->round, param->philo);
	}
	else
	{
		pthread_mutex_unlock(&param->round->forks[n_philo - 1]);
		print_mut("has put down left fork", param->round, param->philo);
		pthread_mutex_unlock(&param->round->forks[n_philo]);
		print_mut("has put down right fork", param->round, param->philo);
	}
	pthread_mutex_unlock(&param->round->philo);
	return (0);
}
