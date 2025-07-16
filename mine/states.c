/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:14:32 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/16 19:07:11 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:14:32 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/16 19:00:00 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_content *curr)
{
	int	alive;

	pthread_mutex_lock(&curr->death_lock);
	alive = curr->death;
	pthread_mutex_unlock(&curr->death_lock);
	return (alive);
}

void is_still_alive(t_content *curr, int status)
{
	pthread_mutex_lock(&curr->death_lock);
	curr->death = status;
	pthread_mutex_unlock(&curr->death_lock);
}

void	thinking(t_pstats *p)
{
	put_message("is thinking\n", p);
	usleep(1000);
}

void	sleeping(t_pstats *p, t_content *curr)
{
	put_message("is sleeping\n", p);
	ft_usleep(curr->tsleep * 1000);
}

int eating(t_pstats *p)
{
	f_lock(p);
	put_message("is eating\n", p);
	meal_update(p);
	ft_usleep(p->in->teat * 1000);
	
	pthread_mutex_lock(p->meal_lock);
	p->eating = 0;
	pthread_mutex_unlock(p->meal_lock);
	
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);
	
	if (p->in->nmeals > 0 && p->in->counter[p->id] >= p->in->nmeals)
	{
		pthread_mutex_lock(p->meal_lock);
		p->full = 1;
		pthread_mutex_unlock(p->meal_lock);
		return (1);
	}
	return (0);
}

void	f_lock(t_pstats *p)
{	
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->lfork);
		put_message("has taken a fork\n", p);
		pthread_mutex_lock(p->rfork);
		put_message("has taken a fork\n", p);
	}
	else
	{
		pthread_mutex_lock(p->rfork);
		put_message("has taken a fork\n", p);
		pthread_mutex_lock(p->lfork);
		put_message("has taken a fork\n", p);
	}
}

void	meal_update(t_pstats *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->lastmeal = get_time();
	p->eating = 1;
	p->in->counter[p->id]++;
	pthread_mutex_unlock(p->meal_lock);
}

