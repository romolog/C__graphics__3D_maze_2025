/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_22_move_rotate.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:04:25 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:41:28 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <assert.h>

static void	ft_add_round(double *a_new, double a, double incr)
{
	*a_new = a + incr;
	if (fabs((*a_new) - floor(*a_new)) < 0.001)
		*a_new = floor(*a_new) - 0.001;
	else if (fabs((*a_new) - ceil(*a_new)) < 0.001)
		*a_new = ceil(*a_new) + 0.001;
}

static void	ft_move(t_tr *t)
{
	double	x_new;
	double	y_new;
	int		c_new;
	int		r_new;

	c_new = t->p->c;
	r_new = t->p->r;
	assert(t->f_map[r_new][c_new] == '0');
	ft_add_round(&x_new, t->p->x, t->p->move_x);
	c_new = (int)x_new;
	ft_add_round(&y_new, t->p->y, t->p->move_y);
	r_new = t->map_rows - 1 - (int)y_new;
	if (t->f_map[r_new][c_new] == '1')
		return ;
	if (t->f_map[r_new][t->p->c] == '1' && \
		t->f_map[t->p->r][c_new] == '1')
		return ;
	t->p->r = r_new;
	t->p->c = c_new;
	t->p->x = x_new;
	t->p->y = y_new;
}

static void	ft_rotate(t_tr *t)
{
	double	d;
	int		k;

	t->p->d += 2 * M_PI + t->p->rotate;
	k = (int)floor(t->p->d / M_PI_4);
	d = t->p->d - k * M_PI_4;
	k %= 8;
	t->p->d = k * M_PI_4 + d;
	k = (int)round(t->p->d / M_PI_4);
	if (fabs(t->p->d - k * M_PI_4) < (t->p->rad / 2))
		t->p->d = k * M_PI_4;
	t->p->d_sin = sin(t->p->d);
}

void	ft_move_rotate(t_tr *t)
{
	if (t->p->move_x || t->p->move_y)
		ft_move(t);
	if (t->p->rotate)
		ft_rotate(t);
	ft_calc_maze(t);
}
