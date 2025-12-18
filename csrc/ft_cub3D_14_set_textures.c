/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_14_set_textures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:04:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:16:55 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_set_textures(t_tr *t)
{
	int		i;
	int		bpp;
	int		size_line;
	int		endian;

	i = -1;
	while (++i < 4)
	{
		t->f_tex[i] = mlx_xpm_file_to_image(t->mlx, \
			t->f_map_textures[i], t->tex_w + i, t->tex_h + i);
		t->err = t->err_mlx;
		ft_err(!t->f_tex[i], t, __FILE__, __LINE__);
		t->tex_addr[i] = (int *)mlx_get_data_addr(t->f_tex[i], \
			&bpp, &size_line, &endian);
		t->err = t->err_mlx;
		ft_err(!t->tex_addr[i], t, __FILE__, __LINE__);
	}
}
