/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:41:04 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/17 11:47:50 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_one(t_pstats *p, size_t tdie)
{
	pthread_mutex_lock(p->lfork);
	put_message("has taken a fork\n", p);
	ft_usleep(tdie);
	pthread_mutex_unlock(p->lfork);
	return (NULL);
}

void	life_cycle(t_pstats *p)
{
	t_content	*curr;

	curr = p->in;
	while (is_alive(curr))
	{
		if (eating(p))
			break ;
		sleeping(p);
		if (!is_alive(curr))
			break ;
		thinking(p);
	}
}

void	*routine(void *arg)
{
	t_pstats	*p;
	int			nphilos;
	size_t		tdie;
	size_t		teat;

	p = (t_pstats *)arg;
	philo_born(p, &nphilos, &tdie, &teat);
	if (nphilos == 1)
		return (is_one(p, tdie));
	if (p->id % 2 == 0)
		usleep(1000);
	life_cycle(p);
	return (NULL);
}

int	end_death(t_pstats *p, t_content *curr)
{
	int		i;
	size_t	time;
	int		nphilos;
	size_t	tdie;

	pthread_mutex_lock(&curr->death_lock);
	nphilos = curr->nphilos;
	tdie = curr->tdie;
	pthread_mutex_unlock(&curr->death_lock);
	i = 0;
	time = get_time();
	while (i < nphilos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if ((time - p[i].lastmeal) >= tdie)
		{
			if (curr->death == 0)
				put_dead(curr, p[i].id);
			pthread_mutex_unlock(p[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	return (0);
}

int	is_alive(t_content *curr)
{
	int i;
	pthread_mutex_lock(&curr->death_lock);
	i = curr->death;
	pthread_mutex_unlock(&curr->death_lock);
	if (i == 1)
		return (0);
	return (1);
}
