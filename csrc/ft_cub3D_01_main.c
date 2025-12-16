/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_01_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:21:32 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 22:48:08 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include <assert.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_tr		t;
	t_pl		p;

	t.prog = ft_get_prog_name(argv[0]);
	ft_check_args(argc, argv, &t);
	assert(argc == 2);
	ft_set_tracer(argv[1], &p, &t);
	ft_set_map(&t);
	ft_set_player(&t);
	ft_init_mlx(&t);
	ft_set_textures(&t);
	ft_calc_maze(&t);
	ft_draw_maze(&t);
	ft_cleanup(&t);
	return (0);
}
