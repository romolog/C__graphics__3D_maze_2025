/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_15_calc_maze.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:22:01 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:43:52 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include <assert.h>
#include <errno.h>

static void	ft_set_ray_cr(t_tr *t)
{
	double		dx_over;

	dx_over = (t->map_cols + 2) * \
		(2 * (t->ray_quarter == 0 || t->ray_quarter == 3) - 1);
	t->ray_c_dx = \
		floor(t->p->x + (t->ray_quarter == 0 || t->ray_quarter == 3)) - t->p->x;
	t->ray_r_dy = floor(t->p->y + (t->ray_quarter < 2)) - t->p->y;
	if (fabs(t->ray_angle - M_PI_2) > 0.001 && \
		fabs(t->ray_angle - M_PI_2 * 3) > 0.001)
	{
		if (!t->ray_tan_err && t->ray_tan)
			t->ray_r_dx = t->ray_r_dy / t->ray_tan;
		else
			t->ray_r_dx = dx_over;
		if (fabs(t->ray_tan - t->ray_r_dy / t->ray_r_dx) > 0.001)
			t->ray_r_dx = dx_over;
		t->ray_r_dx = fabs(t->ray_r_dx) \
			* (2 * (t->ray_quarter == 0 || t->ray_quarter == 3) - 1);
	}
	else
		t->ray_r_dx = 0;
}

void	ft_calc_maze(t_tr *t)
{
	int		c;
	int		r;

	c = t->p->c;
	r = t->p->r;
	t->vert_idx = 0;
	while (t->vert_idx < t->mlx_wdth)
	{
		t->ray_angle = t->p->d + t->f_vert_angle[t->vert_idx];
		t->ray_quarter = ((int)(4.0 + t->ray_angle / M_PI_2)) % 4;
		t->ray_tan_err = 0;
		t->ray_tan = tan(t->ray_angle);
		if (errno == ERANGE)
			t->ray_tan_err = 1;
		t->ray_x = t->p->x;
		ft_set_ray_cr(t);
		ft_get_cross(r, c, t);
	}
	ft_calc_texture(t);
}
