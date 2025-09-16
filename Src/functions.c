/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:14:41 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/07 15:20:10 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/philo.h"

int	ft_eat(t_args *param)
{
	if (ft_dead(param))
		return (1);
	print_mut("is eating", param->round, param->philo);
	pthread_mutex_lock(&param->round->time);
	param->philo->actual_time = get_current_time();
	pthread_mutex_unlock(&param->round->time);
	ft_usleep(param->philo->time_eat);
	if (ft_dead(param))
		return (1);
	if (ft_leave_forks(param, param->philo->n_philo))
		return (1);
	if (param->philo->n_time_eat != -1)
	{
		param->philo->n_time_eat--;
		if (param->philo->n_time_eat == 0)
		{
			pthread_mutex_lock(&param->round->end);
			param->philo->is_end = 1;
			pthread_mutex_unlock(&param->round->end);
		}
	}
	return (0);
}

int	ft_sleep(t_args *param)
{
	if (ft_dead(param))
		return (1);
	print_mut("is sleeping", param->round, param->philo);
	ft_usleep(param->philo->time_sleep);
	return (0);
}

void	ft_end(t_args *param)
{
	pthread_mutex_lock(&param->round->end);
	if (param->philo->is_end == 1)
	{
		pthread_mutex_unlock(&param->round->end);
		print_mut("have finished", param->round, param->philo);
		pthread_mutex_lock(&param->round->philo);
		param->round->all_eat += 1;
		pthread_mutex_unlock(&param->round->philo);
		free(param);
	}
	else
	{
		pthread_mutex_unlock(&param->round->end);
		pthread_mutex_lock(&param->round->dead);
		param->round->is_dead = 1;
		pthread_mutex_unlock(&param->round->dead);
		free(param);
	}
}

int	ft_think(t_args *param)
{
	if (ft_dead(param))
		return (1);
	print_mut("is thinking", param->round, param->philo);
	return (0);
}

void	*time_to_eat(void *arg)
{
	t_args	*argmnt;

	argmnt = (t_args *)arg;
	if (argmnt->round->n_philos > 1 && argmnt->philo->n_philo % 2 != 0)
		ft_usleep(argmnt->philo->time_sleep);
	pthread_mutex_lock(&argmnt->round->dead);
	while (argmnt->round->is_dead == 0)
	{
		pthread_mutex_unlock(&argmnt->round->dead);
		if (ft_take_forks(argmnt, argmnt->philo->n_philo))
			break ;
		if (ft_eat(argmnt))
			break ;
		if (ft_sleep(argmnt))
			break ;
		if (ft_think(argmnt))
			break ;
		pthread_mutex_lock(&argmnt->round->dead);
	}
	pthread_mutex_unlock(&argmnt->round->dead);
	ft_end(argmnt);
	return ((void *)1);
}
