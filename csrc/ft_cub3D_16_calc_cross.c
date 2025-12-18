/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_16_calc_cross.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:04:54 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:43:58 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_record_vertice(t_tr *t)
{
	t->f_vert[t->vert_idx][0] = t->vert_height;
	t->f_vert[t->vert_idx][1] = t->vert_tex_idx;
	t->f_vert[t->vert_idx][2] = t->vert_tex_point;
	t->vert_idx++;
}

static int	ft_get_cross_x(int *r, int *c, t_tr *t)
{
	while (t->ray_r_dx && (fabs(t->ray_r_dx) - fabs(t->ray_c_dx) > 0.0001))
	{
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		t->ray_x = round(t->ray_x + t->ray_c_dx);
		t->ray_r_dx -= t->ray_c_dx;
		t->ray_c_dx = 1 - 2 * (t->ray_quarter == 1 || t->ray_quarter == 2);
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		(*c) = (int)t->ray_x - (t->ray_c_dx < 0);
		if (t->f_map[*r][*c] == '1')
		{
			t->vert_tex_idx = 2 + (t->ray_quarter == 1 || t->ray_quarter == 2);
			ft_get_height("x_cross", *r, *c, t);
			ft_get_tex_point(t);
			ft_record_vertice(t);
			return (1);
		}
	}
	return (0);
}

static int	ft_get_cross_y(int *r, int *c, t_tr *t)
{
	while (fabs(t->ray_c_dx) - fabs(t->ray_r_dx) > 0.0001)
	{
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		if (fabs(t->ray_angle - M_PI_2) > 0.001 && \
			fabs(t->ray_angle - M_PI_2 * 3) > 0.001)
		{
			t->ray_x += t->ray_r_dx;
			t->ray_c_dx -= t->ray_r_dx;
			t->ray_r_dx = fabs(1 / t->ray_tan);
			t->ray_r_dx *= \
				(1 - 2 * (t->ray_quarter == 1 || t->ray_quarter == 2));
		}
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		(*r) += 1 - 2 * (t->ray_quarter < 2);
		if (t->f_map[*r][*c] == '1')
		{
			t->vert_tex_idx = (t->ray_quarter < 2);
			ft_get_height("y_cross", *r, *c, t);
			ft_get_tex_point(t);
			ft_record_vertice(t);
			return (1);
		}
	}
	return (0);
}

void	ft_get_cross(int r, int c, t_tr *t)
{
	while (42)
	{
		if (ft_get_cross_x(&r, &c, t))
			return ;
		if (ft_get_cross_xy(&r, &c, t))
			return ;
		if (ft_get_cross_y(&r, &c, t))
			return ;
	}
}
