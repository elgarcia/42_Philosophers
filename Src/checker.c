/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 00:45:57 by eliagarc          #+#    #+#             */
/*   Updated: 2024/01/10 01:43:01 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/philo.h"

long	ft_atoi(const char *str)
{
	char		*s;
	long		aux;
	int			signmin;

	aux = 0;
	signmin = 0;
	s = (char *)str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			signmin++;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9'))
	{
		aux = (aux * 10) + *s - 48;
		s++;
	}
	if (signmin % 2 != 0)
		aux *= -1;
	return (aux);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_nbrvalid(argv[i]) == -1 && argv[i][0])
			return (-1);
		i++;
	}
	return (0);
}

int	is_nbrvalid(char *s)
{
	int		i;
	long	j;

	i = 0;
	j = ft_atoi(s);
	if (j < 0 || j > INT_MAX)
		return (-1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && (s[i] != '-' && s[i] != '+'))
			return (-1);
		if (i != 0 && (s[i] == '-' || s[i] == '+'))
			return (-1);
		i++;
	}
	if (!ft_isdigit(s[i - 1]))
		return (-1);
	return (i);
}
