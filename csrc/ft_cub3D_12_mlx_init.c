/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_14_mlx_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:52 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/19 18:44:48 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

void	ft_init_mlx(t_tr *t)
{
	t->mlx = mlx_init();
	t->err = t->err_mlx;
	ft_err(!t->mlx, t, __FILE__, __LINE__);
	t->mlx_win = mlx_new_window(t->mlx, t->mlx_wdth, t->mlx_hght, \
		"Roman_Irina_Cub3D");
	t->err = t->err_mlx;
	ft_err(!t->mlx_win, t, __FILE__, __LINE__);
	t->mlx_img = mlx_new_image(t->mlx, t->mlx_wdth, t->mlx_hght);
	t->err = t->err_mlx;
	ft_err(!t->mlx_img, t, __FILE__, __LINE__);
	t->mlx_addr = (int *)mlx_get_data_addr(t->mlx_img, \
		&t->mlx_bpp, &t->mlx_line_len, &t->mlx_endian);
	t->err = t->err_mlx;
	ft_err(!t->mlx_addr, t, __FILE__, __LINE__);
}
