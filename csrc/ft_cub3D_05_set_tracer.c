/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_05_set_tracer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:03:05 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 21:26:34 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "libft.h"
#include <assert.h>
#include <fcntl.h>
#include <stddef.h>

void	ft_set_vars_map(char *map_file, t_tr *t)
{
	t->map_cols = 0;
	t->map_init = 0;
	t->map_init_nswecf = 0;
	t->map_invalid = 0;
	t->map_raw_rows = 100;
	t->map_rows = 0;
	t->map_player = 0;
	t->f_map_fd = open(map_file, O_RDONLY);
	t->err = "can't open map\n";
	ft_err((t->f_map_fd == -1), t, __FILE__, __LINE__);
	assert(t->f_map_fd > 2);
}

void	ft_set_vars_player(t_tr *t)
{
	t->p->d = 0.0;
	t->p->move_x = 0.0;
	t->p->move_y = 0.0;
	t->p->mxa = 0.0;
	t->p->mya = 0.0;
	t->p->mxd = 0.0;
	t->p->myd = 0.0;
	t->p->mxs = 0.0;
	t->p->mys = 0.0;
	t->p->mxw = 0.0;
	t->p->myw = 0.0;
	t->p->step = 0.03;
	t->p->min_to_wall = 0.01;
	t->p->rad = M_PI / 128;
	t->p->rotate = 0.0;
	t->p->c = -1;
	t->p->r = -1;
	t->p->x = -1;
	t->p->y = -1;
}

void	ft_set_vars_vertices(t_tr *t)
{
	int		i;

	t->vert_idx = 0;
	t->f_vert = malloc(sizeof(int *) * (t->mlx_wdth + 1));
	ft_err(!t->f_vert, t, __FILE__, __LINE__);
	t->f_vert[0] = NULL;
	t->f_vert[t->mlx_wdth] = NULL;
	i = -1;
	while (++i < t->mlx_wdth)
	{
		t->f_vert[i] = ft_calloc(3, sizeof(int));
		ft_err(!t->f_vert[i], t, __FILE__, __LINE__);
		t->f_vert[i + 1] = NULL;
	}
	t->f_vert_angle = malloc(sizeof(double) * t->mlx_wdth);
	ft_err(!t->f_vert_angle, t, __FILE__, __LINE__);
	i = 0;
	while (++i < t->mlx_wdth - 1)
		t->f_vert_angle[i] = atan(1 - ((double)(2 * i)) / (t->mlx_wdth - 1));
	t->f_vert_angle[0] = M_PI_4;
	t->f_vert_angle[t->mlx_wdth / 2] = 0;
	t->f_vert_angle[t->mlx_wdth - 1] = -M_PI_4;
}
