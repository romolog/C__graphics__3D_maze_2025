/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_24_calc_cross_xy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:04:54 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 16:32:19 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include <assert.h>
#include <errno.h>

#include <stdio.h>

int	ft_is_45degree(double angle)
{
	double		prec;
	int			k;

	prec = 0.001;
	k = (int)floor(angle / M_PI_4);
	if (fabs(angle - M_PI_4 * k) < prec)
		return (1);
	return (0);
}

static void	ft_rec_vertice(int *r, int *c, t_tr *t)
{
	t->vert_tex_idx = -1;
	t->vert_tex_point = -1;
	ft_get_height("xy_cross", *r, *c, t);
	ft_record_vertice(t);
}

int	ft_get_cross_xy(int *r, int *c, t_tr *t)
{
	while (fabs(fabs(t->ray_r_dx) - fabs(t->ray_c_dx)) <= 0.0001)
	{
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		t->ray_x = round(t->ray_x + t->ray_c_dx);
		t->ray_c_dx = 1 - 2 * (t->ray_quarter == 1 || t->ray_quarter == 2);
		t->ray_r_dx = t->ray_c_dx;
		if (!ft_is_45degree(t->ray_angle))
		{
			t->ray_r_dx = fabs(1 / t->ray_tan);
			t->ray_r_dx *= 1 - 2 * (t->ray_quarter == 1 || t->ray_quarter == 2);
		}
		assert((t->ray_r_dx * t->ray_c_dx) >= 0);
		(*c) = (int)t->ray_x - (t->ray_c_dx < 0);
		(*r) += 1 - 2 * (t->ray_quarter < 2);
		if (t->f_map[*r][*c] != '0' || \
			t->f_map[(*r) - (1 - 2 * (t->ray_quarter < 2))][*c] != '0' || \
			t->f_map[*r][(*c) - \
				(1 - 2 * (t->ray_quarter == 1 || t->ray_quarter == 2))] != '0')
		{
			ft_rec_vertice(r, c, t);
			return (1);
		}
	}
	return (0);
}
