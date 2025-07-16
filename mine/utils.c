/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:35:36 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/14 09:35:36 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:35:36 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/16 19:00:00 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long ms)
{
	long long	start;
	long long	target;

	start = get_time() * 1000;
	target = start + ms;
	while ((get_time() * 1000) < target)  // ✅ CORRETTO
	{
		usleep(50);
	}
}

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign *= (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res * sign);
}

void	put_time(t_content curr)
{
	size_t	time;

	time = get_time() - curr.start;
}

void	put_message(char *s, t_pstats *p)
{
	pthread_mutex_lock(&p->in->print);
	put_time(*p->in);
	printf("philosopher %d %s", p->id, s);
	pthread_mutex_unlock(&p->in->print);
}

