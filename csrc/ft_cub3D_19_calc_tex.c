/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_19_calc_tex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:07:59 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:16:58 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

static void	ft_draw_texture(int *ptr, int r, int c, t_tr *t)
{
	int		*tex_ptr;
	double	point;
	int		rows;
	int		idx;

	idx = t->f_vert[c][1];
	tex_ptr = (int *)t->tex_addr[idx];
	rows = (int)round((t->tex_h[idx] - 1) * \
		((double)(r - (t->mlx_hght - t->f_vert[c][0]) / 2) / \
		t->f_vert[c][0]));
	tex_ptr += t->tex_w[idx] * rows;
	point = ((double)(t->f_vert[c][2])) / 10000;
	if (point < 0.01 || point > 0.99)
		point = round(point);
	tex_ptr += (int)round((t->tex_w[idx] - 1) * point);
	*ptr = *tex_ptr;
}

static void	ft_eliminate_edges(int c, t_tr *t)
{
	int		l;
	int		r;
	int		ok;

	l = c;
	r = c;
	while (l >= 0 && t->f_vert[l][1] == -1)
		l--;
	while (r < t->mlx_wdth && t->f_vert[r][1] == -1)
		r++;
	ok = l;
	if (l < 0 || t->f_vert[l][1] == -1)
		ok = r;
	else if (r < t->mlx_wdth && \
		ft_abs(t->f_vert[l][0] - t->f_vert[c][0]) \
			> ft_abs(t->f_vert[r][0] - t->f_vert[c][0]))
		ok = r;
	t->f_vert[c][1] = t->f_vert[ok][1];
	t->f_vert[c][2] = t->f_vert[ok][2];
}

void	ft_calc_texture(t_tr *t)
{
	int		c;
	int		r;
	int		*ptr;

	assert(t->mlx_wdth == t->vert_idx);
	c = -1;
	while (++c < t->mlx_wdth)
	{
		if (t->f_vert[c][1] == -1)
			ft_eliminate_edges(c, t);
		r = -1;
		while (++r < t->mlx_hght)
		{
			ptr = t->mlx_addr + (t->mlx_wdth * r) + c;
			if (r < (t->mlx_hght - t->f_vert[c][0]) / 2)
				*ptr = t->map_c[3];
			else if (r > (t->mlx_hght + t->f_vert[c][0]) / 2)
				*ptr = t->map_f[3];
			else
				ft_draw_texture(ptr, r, c, t);
		}
	}
}
