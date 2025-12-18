/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_20_draw_maze.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:22:26 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:44:14 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <assert.h>
#include <stddef.h>

static int	ft_render_img(t_tr *t)
{
	if (t->p->move_x || t->p->move_y || t->p->rotate)
		ft_move_rotate(t);
	mlx_put_image_to_window(t->mlx, t->mlx_win, t->mlx_img, 0, 0);
	return (0);
}

void	ft_draw_maze(t_tr *t)
{
	mlx_loop_hook(t->mlx, &ft_render_img, t);
	mlx_hook(t->mlx_win, MLX_RED_CROSS, 0, &ft_event_red_button, t);
	mlx_hook(t->mlx_win, MLX_KEY_PRESS, \
		MLX_KEY_PRESS_MASK, &ft_event_key_press, t);
	mlx_hook(t->mlx_win, MLX_KEY_RELEASE, \
		MLX_KEY_RELEASE_MASK, &ft_event_key_release, t);
	mlx_loop(t->mlx);
}
