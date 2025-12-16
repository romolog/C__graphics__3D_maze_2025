/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_25_calc_height_point.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:35 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/23 19:23:12 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include <stdio.h>

void	ft_get_height(char *master, int r, int c, t_tr *t)
{
	double		dist;
	double		cs;

	cs = cos(t->ray_angle);
	if (fabs(t->ray_angle - M_PI_2) < 0.001 || \
		fabs(t->ray_angle - M_PI_2 * 3) < 0.001)
	{
		if (fabs(t->ray_angle - M_PI_2) < 0.001)
			dist = (t->map_rows - t->p->y - r - 1);
		else
			dist = (t->p->y - (t->map_rows - r));
		t->vert_height = \
			(int)round(t->mlx_hght / fabs((dist * 2.0) * t->p->d_sin));
		return ;
	}
	dist = (t->ray_x - t->p->x) / cs;
	t->vert_height = (int)round(t->mlx_hght / \
		fabs((dist * 2) * cos(t->ray_angle - t->p->d)));
	(void)master;
	c = r + c;
}

void	ft_get_tex_point(t_tr *t)
{
	double		dist;

	dist = 0;
	if (!t->vert_tex_idx)
		dist = ceil(t->ray_x) - t->ray_x;
	else if (t->vert_tex_idx == 1)
		dist = t->ray_x - floor(t->ray_x);
	else if (t->vert_tex_idx > 1 && t->ray_quarter < 2)
	{
		dist = \
			fabs((t->ray_x - t->p->x) * t->ray_tan) + t->p->y - floor(t->p->y);
		dist = ceil(dist) - dist;
	}
	else if (t->vert_tex_idx > 1 && t->ray_quarter > 1)
	{
		dist = \
			fabs((t->ray_x - t->p->x) * t->ray_tan) + ceil(t->p->y) - t->p->y;
		dist = dist - floor(dist);
	}
	t->vert_tex_point = (int)(10000 * dist);
}
