/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:02:45 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/14 09:02:45 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:02:45 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/16 19:00:00 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_pstats *p, t_content *curr)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	
	if(curr->nmeals == -1)
		return(0);
		
	while (i < curr->nphilos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (p[i].full == 1)
			count++;
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	
	if (count == curr->nphilos)
		return (1);
	return (0);
}

int	check_args(int ac, char *av[])
{
	int		i;
	long	nb;

	i = 1;
	nb = 0;
	if (ac < 5 || ac > 6)
		error(1);
	while (i < ac)
	{
		if (!checkarg(av[i]))
			error(2);
		i++;
	}
	i = 1;
	while (i < ac)
	{
		nb = ft_atoi(av[i]);
		if (nb <= 0 || nb > INT_MAX)
			error(2);
		i++;
	}
	return (1);
}

int	checkarg(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	error(int code)
{
	if (code == 1)
	{
		printf(RED "Error: Wrong number of arguments\n" RESET);
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	else if (code == 2)
	{
		printf (RED "Error: Invalid arguments - only positive integers allowed\n"RESET);
		exit(1);
	}
	else if (code == 3)
	{
		printf(RED "Error: Invalid number of meals\n" RESET);
		exit(1);
	}
	else if (code == 4)
	{
		printf(RED "Error: Mutex initialization failed\n" RESET);
		exit(1);
	}
	else if (code == 5)
	{
		printf(RED "Error: Thread creation failed\n" RESET);
		exit(1);
	}
}


