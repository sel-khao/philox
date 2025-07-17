/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:14:32 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/17 11:45:55 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_pstats *p)
{
	long	time_since_last_meal;
	long	think_time;

	pthread_mutex_lock(p->meal_lock);
	time_since_last_meal = get_time() - p->lastmeal;
	pthread_mutex_unlock(p->meal_lock);
	think_time = p->in->tdie - time_since_last_meal - p->in->teat - 10;
	if (think_time > 0)
	{
		put_message("is thinking...\n", p);
		usleep(1000);
	}
	
}

void	sleeping(t_pstats *p)
{
	put_message("is sleeping\n", p);
	ft_usleep(p->in->tsleep);
}

int	eating(t_pstats *p)
{
	int	stop;

	stop = 0;
	f_lock(p);
	meal_update(p);
	put_message("started eating\n", p);
	ft_usleep(p->in->teat);
	if (p->in->nmeals > 0 && p->in->counter[p->id - 1] >= p->in->nmeals)
	{
		pthread_mutex_lock(p->meal_lock);
		p->full = 1;
		pthread_mutex_unlock(p->meal_lock);
		stop = 1;
	}
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);
	return (stop);
}

void	f_lock(t_pstats *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->rfork);
		put_message("has taken a fork\n", p);
		pthread_mutex_lock(p->lfork);
		put_message("has taken a fork\n", p);
	}
	else
	{
		pthread_mutex_lock(p->lfork);
		put_message("has taken a fork\n", p);
		pthread_mutex_lock(p->rfork);
		put_message("has taken a fork\n", p);
	}
}

void	meal_update(t_pstats *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->lastmeal = get_time();
	p->in->counter[p->id -1]++;
	pthread_mutex_unlock(p->meal_lock);
}
