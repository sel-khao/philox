/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:41:04 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/16 19:14:37 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	t_timeval	tv;
	long long	timelaps;

	gettimeofday(&tv, NULL);
	timelaps = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timelaps);
}

int end_death(t_pstats *p, t_content *curr)
{
    int i;
    size_t time;
    size_t current_time;

    i = 0;
    current_time = get_time();
    
    while (i < curr->nphilos)
    {
        pthread_mutex_lock(p[i].meal_lock);
        time = p[i].lastmeal;
        int is_eating = p[i].eating;
        pthread_mutex_unlock(p[i].meal_lock);
        
        if (!is_eating && (current_time - time) > curr->tdie)
        {
            pthread_mutex_lock(&curr->death_lock);
            if (curr->death == 0)
            {
                curr->death = 1;
               put_message("is died\n", p);
            }
            pthread_mutex_unlock(&curr->death_lock);
            return (1);
        }
        i++;
    }
    return (0);
}

void	*monitoring(void *arg)
{
	t_pstats	*p;
	t_content	*curr;

	p = (t_pstats *)arg;
	curr = p->in;
	while (is_alive(p->in) == 0)
	{
		if (check_full(p, curr) != 0)
		{
			is_still_alive(curr, 1);
			break ;
		}
		if (end_death(p, curr))
		{
			is_still_alive(curr, 1);
			break ;
		}
		usleep(1000);
	}
	return	(NULL);
}

void	*routine(void *arg)
{
	t_pstats	*p;
	t_content	*curr;

	p = (t_pstats *)arg;
	curr = p->in;
	if (curr->nphilos == 1)
	{
		pthread_mutex_lock(p->lfork);
		put_message("has taken a fork\n", p);
		ft_usleep(curr->tdie * 1000);
		pthread_mutex_unlock(p->lfork);
		return (NULL);
	}
	
	if (p->id % 2 == 0)
		ft_usleep(1000);
		
	while (is_alive(curr) == 0)
	{
		if (eating(p) != 0)
			break ;
		sleeping(p, curr);
		thinking(p);
	}
	return (NULL);
}




