/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_08_set_map_raw.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:16:21 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:42:58 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cub3D.h"
#include <assert.h>

static void	ft_passby_zero_player(char **k, char *entry, t_tr *t)
{
	while (**k == '0' \
		|| **k == 'N' || **k == 'S' || **k == 'W' || **k == 'E')
	{
		if (**k == 'N' || **k == 'S' || **k == 'W' || **k == 'E')
		{
			t->map_invalid = t->p->c >= 0;
			if (t->map_invalid)
				return ;
			t->map_player = **k;
			t->p->c = (*k) - entry;
			t->p->r = t->map_rows;
		}
		(*k)++;
	}
	t->map_invalid = (**k != '1');
}

void	ft_passby_zero_one_player(char **k, char *entry, t_tr *t)
{
	if (t->map_invalid)
		return ;
	while (**k == '0' || **k == '1' \
		|| **k == 'N' || **k == 'S' || **k == 'W' || **k == 'E')
	{
		ft_passby_zero_player(k, entry, t);
		if (t->map_invalid)
			return ;
		while (**k == '1')
			(*k)++;
	}
	t->map_invalid = (**k && **k != '\n' && **k != ' ');
}
