/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_03_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:49:27 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 22:29:31 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "mlx.h"
#include <stdlib.h>

static void	ft_close_mlx(t_tr *t)
{
	int		i;

	i = -1;
	while (++i < 4 && t->f_tex[i])
		mlx_destroy_image(t->mlx, t->f_tex[i]);
	if (t->mlx_img)
		mlx_destroy_image(t->mlx, t->mlx_img);
	t->mlx_img = NULL;
	if (t->mlx_win)
		mlx_destroy_window(t->mlx, t->mlx_win);
	t->mlx_win = NULL;
	if (t->mlx)
		mlx_destroy_display(t->mlx);
	t->mlx = NULL;
}

static void	ft_free_map_textures(t_tr *t)
{
	int		i;

	i = -1;
	while (++i < 4 && t->f_map_textures[i])
	{
		free(t->f_map_textures[i]);
		t->f_map_textures[i] = NULL;
	}
}

void	ft_cleanup(t_tr *t)
{
	ft_free_2d_char(&t->f_map);
	ft_free_2d_char(&t->f_map_raw);
	ft_free_2d_int(&t->f_vert);
	ft_free_close_fd(&t->f_map_fd);
	ft_free_map_textures(t);
	ft_close_mlx(t);
	if (t->f_vert_angle)
		free(t->f_vert_angle);
	if (t->exit)
		exit(t->exit_status);
}
