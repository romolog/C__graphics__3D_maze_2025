/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_09_set_map_transform_2darr.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:11:10 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:16:49 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cub3D.h"
#include <stdio.h>
#include <stddef.h>

static void	ft_malloc_memset_space_map(t_tr *t)
{
	int		i;

	t->f_map = malloc(sizeof(char *) * (t->map_rows + 1));
	ft_err(!t->f_map, t, __FILE__, __LINE__);
	t->f_map[t->map_rows] = NULL;
	i = -1;
	while (++i < t->map_rows)
	{
		t->f_map[i] = malloc((t->map_cols + 1));
		ft_err(!t->f_map[i], t, __FILE__, __LINE__);
		ft_memset(t->f_map[i], ' ', t->map_cols);
		t->f_map[i][t->map_cols] = '\0';
	}
}

static void	ft_copy_rawmap_to_map(t_tr *t)
{
	int		i;
	int		k;

	i = -1;
	while (++i < t->map_rows)
	{
		k = -1;
		while (t->f_map_raw[i][++k])
		{
			if (t->f_map_raw[i][k] == 'N' || \
				t->f_map_raw[i][k] == 'S' || \
				t->f_map_raw[i][k] == 'W' || \
				t->f_map_raw[i][k] == 'E')
				t->f_map[i][k] = '0';
			else
				t->f_map[i][k] = t->f_map_raw[i][k];
		}
	}
}

void	ft_transform_rawmap_to_arr2d(t_tr *t)
{
	int		i;

	ft_malloc_memset_space_map(t);
	ft_copy_rawmap_to_map(t);
	if (DEBUG_MODE)
	{
		i = -1;
		while (++i < (t->map_cols + 7))
			write(1, "-", 1);
		write(1, "\n", 1);
		i = -1;
		while (++i < t->map_rows)
			printf("%2d : |%s|\n", i, t->f_map[i]);
		i = -1;
		while (++i < (t->map_cols + 7))
			write(1, "-", 1);
		printf("\nline length = %d\n", t->map_cols);
		i = -1;
		while (++i < (t->map_cols + 7))
			write(1, "-", 1);
		write(1, "\n", 1);
	}
}
