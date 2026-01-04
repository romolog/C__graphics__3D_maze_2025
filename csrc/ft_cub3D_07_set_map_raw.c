/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_07_set_map_raw.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:16:21 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:42:47 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cub3D.h"
#include <assert.h>

static void	ft_malloc_raw_map(t_tr *t)
{
	char	**temp;
	int		i;

	if (!t->f_map_raw)
	{
		t->f_map_raw = ft_calloc((t->map_raw_rows + 1), sizeof(char *));
		ft_err(!t->f_map_raw, t, __FILE__, __LINE__);
		t->f_map_raw[0] = NULL;
	}
	if (t->map_rows == t->map_raw_rows)
	{
		temp = malloc(sizeof(char *) * (t->map_raw_rows * 10 + 1));
		ft_err(!temp, t, __FILE__, __LINE__);
		i = -1;
		while (t->f_map_raw[++i])
			temp[i] = t->f_map_raw[i];
		temp[i] = NULL;
		free(t->f_map_raw);
		t->f_map_raw = temp;
		t->map_raw_rows *= 10;
	}
}

static void	ft_passby_space_one(char **k, t_tr *t)
{
	if (t->map_invalid)
		return ;
	while (**k == ' ' || **k == '1')
	{
		while (**k == ' ')
			(*k)++;
		t->map_invalid = (**k && **k != '\n' && **k != '1');
		if (t->map_invalid)
			return ;
		while (**k == '1')
			(*k)++;
	}
	t->map_invalid = (**k && **k != '\n' && **k != '0' \
		&& **k != 'N' && **k != 'S' && **k != 'W' && **k != 'E');
}

static void	ft_get_char_entry(char *entry, t_tr *t)
{
	char		*tracer;
	int			len;

	assert(t->map_rows < t->map_raw_rows);
	assert(!t->f_map_raw[t->map_rows]);
	tracer = entry;
	while (!t->map_invalid && *tracer && *tracer != '\n')
	{
		ft_passby_space_one(&tracer, t);
		ft_passby_zero_one_player(&tracer, entry, t);
	}
	if (t->map_invalid)
		return ;
	len = tracer - entry;
	assert(*(entry + (len - 1)) != '\n');
	ft_add_str_malloc(t->f_map_raw + t->map_rows, entry, len, t);
	t->map_rows++;
	t->f_map_raw[t->map_rows] = NULL;
	if (t->map_cols < len)
		t->map_cols = len;
}

void	ft_get_map_entry(char *entry, t_tr *t)
{
	if (t->map_init_nswecf != 111111)
		return ;
	if (t->map_invalid || (!t->map_init && ft_is_space_tab_newline(entry)))
		return ;
	t->map_invalid = t->map_init && ft_is_space_tab_newline(entry);
	if (t->map_invalid)
		return ;
	t->map_init = 1;
	ft_malloc_raw_map(t);
	ft_get_char_entry(entry, t);
}
