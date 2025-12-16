/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_12_set_player.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:06:41 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/23 19:20:57 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include <assert.h>

#include <stdio.h>

void	ft_set_player(t_tr *t)
{
	t->p->d = 0;
	if (t->map_player == 'N')
		t->p->d = M_PI_2;
	if (t->map_player == 'W')
		t->p->d = M_PI;
	if (t->map_player == 'S')
		t->p->d = M_PI + M_PI_2;
	t->p->d_sin = sin(t->p->d);
	t->p->x = (t->p->c + 0.5);
	t->p->y = (t->map_rows - t->p->r - 0.5);
}
