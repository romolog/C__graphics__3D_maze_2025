/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_04_set_tracer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:03:05 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 21:26:56 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "libft.h"
#include <assert.h>
#include <fcntl.h>
#include <stddef.h>

char	*ft_get_prog_name(char *prog_name)
{
	char	*ptr;

	ptr = ft_strrchr(prog_name, '/');
	if (!ptr)
		return (prog_name);
	else
		return (ptr + 1);
}

static void	ft_set_err_list(t_tr *t)
{
	t->err_algorithm = "algorithm failed\n";
	t->err_map_invalid = "invalid map\n";
	t->err_mlx = "mlx failed\n";
	t->err_overflow = "datatype overflow\n";
	t->err = NULL;
}

static void	ft_set_vars_mlx(t_tr *t)
{
	t->mlx = NULL;
	t->mlx_win = NULL;
	t->mlx_wdth = 2560;
	t->mlx_hght = 1440;
	t->mlx_img = NULL;
	t->mlx_addr = NULL;
	t->mlx_bpp = 0;
	t->mlx_line_len = 0;
	t->mlx_endian = 0;
}

static void	ft_set_vars_f(t_tr *t)
{
	t->f_vert = NULL;
	t->f_vert_angle = NULL;
	t->f_map = NULL;
	t->f_map_raw = NULL;
	t->f_tex[0] = NULL;
	t->f_map_textures[0] = NULL;
	t->f_map_textures[1] = NULL;
	t->f_map_textures[2] = NULL;
	t->f_map_textures[3] = NULL;
	t->f_map_fd = -1;
}

void	ft_set_tracer(char *map_file, t_pl *pl, t_tr *t)
{
	t->exit = 0;
	t->exit_status = 0;
	t->p = pl;
	ft_set_err_list(t);
	ft_set_vars_f(t);
	ft_set_vars_mlx(t);
	ft_set_vars_map(map_file, t);
	ft_set_vars_player(t);
	ft_set_vars_vertices(t);
}
