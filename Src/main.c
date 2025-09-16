/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:46:57 by eliagarc          #+#    #+#             */
/*   Updated: 2024/01/25 13:07:29 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/philo.h"

int	out_of_time(t_meeting *round, int i)
{
	pthread_mutex_lock(&round->time);
	if (((unsigned long)get_current_time() - \
	round->philosophers[i]->actual_time \
	> round->philosophers[i]->time_die))
	{
		pthread_mutex_unlock(&round->time);
		pthread_mutex_lock(&round->dead);
		round->is_dead = 1;
		pthread_mutex_unlock(&round->dead);
		return (1);
	}
	pthread_mutex_unlock(&round->time);
	return (0);
}

void	ft_usleep(long time)
{
	long	t;

	t = get_current_time();
	while (42)
	{
		usleep(100);
		if (((long)get_current_time() - t) >= time)
			break ;
	}
}

void	waiter(t_meeting *round)
{
	int	i;
	int	j;

	j = 0;
	pthread_mutex_lock(&round->dead);
	while (!round->is_dead && !all_philos_eat(round))
	{
		pthread_mutex_unlock(&round->dead);
		i = -1;
		while (++i < round->n_philos)
		{
			if (out_of_time(round, i))
			{
				pthread_mutex_lock(&round->print);
				printf("%zu ", get_current_time() - round->meet_time);
				printf("%d is dead\n", round->philosophers[i]->n_philo);
				pthread_mutex_unlock(&round->print);
				while (j < round->n_philos)
					pthread_mutex_unlock(&round->forks[j++]);
				break ;
			}
		}
		pthread_mutex_lock(&round->dead);
	}
	pthread_mutex_unlock(&round->dead);
}

void	print_mut(char *message, t_meeting *round, t_philo *philo)
{
	t_args	*aux;

	aux = (t_args *)malloc(sizeof(t_args));
	aux->philo = philo;
	aux->round = round;
	if (!ft_dead(aux) || philo->is_end == 1)
	{
		pthread_mutex_lock(&round->print);
		pthread_mutex_lock(&round->time);
		printf("%zu ", get_current_time() - round->meet_time);
		pthread_mutex_unlock(&round->time);
		printf("%d %s\n", philo->n_philo, message);
		pthread_mutex_unlock(&round->print);
	}
	pthread_mutex_unlock(&round->philo);
	free(aux);
}

int	main(int argc, char **argv)
{
	t_meeting	*round;

	round = NULL;
	if (argc > 4 && argc < 7)
	{
		if (check_input(argc, argv) == -1)
		{
			printf("Invalid input\n");
			return (1);
		}
		if (start_philo(argc, argv, round) == -1)
			return (1);
	}
	else
		return (printf("Invalid arguments\n"), 0);
}
