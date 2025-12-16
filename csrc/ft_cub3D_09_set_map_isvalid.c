/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_08_set_map_isvalid.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:10 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/19 18:44:12 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include <stdio.h>

static int	ft_is_zero(int i, int k, t_tr *t)
{
	if (t->f_map[i][k] == '0')
		return (1);
	return (0);
}

static int	ft_is_space_or_edge(int i, int k, t_tr *t)
{
	if (i < 0 || t->f_map[i][k] == '\0' || t->f_map[i][k] == ' ')
		return (1);
	return (0);
}

static void	ft_is_valid_cell(int prev, int i, int k, t_tr *t)
{
	if (prev)
	{
		t->map_invalid += ft_is_space_or_edge(i - 1, k + 1, t);
		t->map_invalid += ft_is_space_or_edge(i + 1, k + 1, t);
	}
	else
	{
		t->map_invalid += ft_is_space_or_edge(i - 1, k - 1, t);
		t->map_invalid += ft_is_space_or_edge(i - 1, k, t);
		t->map_invalid += ft_is_space_or_edge(i - 1, k + 1, t);
		t->map_invalid += ft_is_space_or_edge(i + 1, k - 1, t);
		t->map_invalid += ft_is_space_or_edge(i + 1, k, t);
		t->map_invalid += ft_is_space_or_edge(i + 1, k + 1, t);
	}
}

int	ft_is_valid_map(t_tr *t)
{
	int		i;
	int		k;
	int		current;
	int		prev;

	i = -1;
	while (++i < t->map_rows)
	{
		prev = 0;
		k = -1;
		while (++k < t->map_cols)
		{
			current = ft_is_zero(i, k, t);
			if (current)
				ft_is_valid_cell(prev, i, k, t);
			if (t->map_invalid)
				return (0);
			prev = current;
		}
	}
	if (!ft_is_valid_textures(t))
		return (0);
	return (1);
}
