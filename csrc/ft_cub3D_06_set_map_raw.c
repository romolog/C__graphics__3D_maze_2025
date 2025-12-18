/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_06_set_map_raw.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:07:37 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:42:53 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cub3D.h"
#include <assert.h>

static void	ft_get_str_entry(char *key, char *entry, int base, t_tr *t)
{
	int		i;
	char	**dst;

	if (t->map_invalid || entry[0] != key[0] || entry[1] != key[1])
		return ;
	t->map_invalid = 1;
	if ((t->map_init_nswecf / base) % 10)
		return ;
	i = 2;
	while (entry[i] == ' ' || entry[i] == '\t')
		i++;
	if (!entry[i])
		return ;
	dst = t->f_map_textures;
	if (!ft_strncmp(key, "SO", 2))
		dst = t->f_map_textures + 1;
	else if (!ft_strncmp(key, "WE", 2))
		dst = t->f_map_textures + 2;
	else if (!ft_strncmp(key, "EA", 2))
		dst = t->f_map_textures + 3;
	assert(!*dst);
	ft_add_str_malloc(dst, entry + i, ft_strlen(entry + i) - \
		(*(entry + i + ft_strlen(entry + i) - 1) == '\n'), t);
	t->map_init_nswecf += base;
	t->map_invalid = 0;
}

static void	ft_get_rgb(char *entry, int *idx, int *dst, t_tr *t)
{
	int		i;

	if (t->map_invalid)
		return ;
	i = *idx;
	if (!ft_isdigit(entry[i]) || (ft_isdigit(entry[i + 1]) \
		&& ft_isdigit(entry[i + 2]) && ft_isdigit(entry[i + 3])))
	{
		t->map_invalid = 1;
		return ;
	}
	*dst = ft_atoi(entry + i);
	t->map_invalid = (*dst < 0 || *dst > 255);
	if (t->map_invalid)
		return ;
	while (ft_isdigit(entry[i]))
		i++;
	i += (entry[i] == ',');
	while (entry[i] == ' ' || entry[i] == '\t')
		i++;
	*idx = i;
}

static void	ft_get_int_entry(char key, char *entry, int base, t_tr *t)
{
	int		i;
	int		*dst;

	if (t->map_invalid || entry[0] != key)
		return ;
	t->map_invalid = 1;
	if ((t->map_init_nswecf / base) % 10)
		return ;
	i = 1;
	while (entry[i] == ' ' || entry[i] == '\t')
		i++;
	if (!ft_isdigit(entry[i]))
		return ;
	t->map_invalid = 0;
	dst = t->map_c;
	if (key == 'F')
		dst = t->map_f;
	ft_get_rgb(entry, &i, dst, t);
	ft_get_rgb(entry, &i, dst + 1, t);
	ft_get_rgb(entry, &i, dst + 2, t);
	t->map_f[3] = t->map_f[0] * 0x10000 + t->map_f[1] * 0x100 + t->map_f[2];
	t->map_c[3] = t->map_c[0] * 0x10000 + t->map_c[1] * 0x100 + t->map_c[2];
	t->map_init_nswecf += base;
}

static void	ft_get_nswecf_entry(char *entry, t_tr *t)
{
	int		i;

	if (t->map_init_nswecf == 111111)
		return ;
	i = 0;
	while (entry[i] == ' ' || entry[i] == '\t')
		i++;
	if (!entry[i])
		return ;
	ft_get_str_entry("NO", entry + i, 100000, t);
	ft_get_str_entry("SO", entry + i, 10000, t);
	ft_get_str_entry("WE", entry + i, 1000, t);
	ft_get_str_entry("EA", entry + i, 100, t);
	ft_get_int_entry('C', entry + i, 10, t);
	ft_get_int_entry('F', entry + i, 1, t);
}

void	ft_set_map(t_tr *t)
{
	char	*entry;

	entry = ft_get_next_line(t->f_map_fd);
	while (entry && !t->map_invalid)
	{
		if (t->map_init_nswecf != 111111)
			ft_get_nswecf_entry(entry, t);
		else
			ft_get_map_entry(entry, t);
		ft_free_str(&entry);
		if (!t->map_invalid)
			entry = ft_get_next_line(t->f_map_fd);
	}
	t->map_invalid += (t->p->c < 0);
	t->err = t->err_map_invalid;
	ft_err(t->map_invalid || (!entry && !t->map_init) \
		|| (entry && t->map_init), t, __FILE__, __LINE__);
	assert(t->map_init_nswecf == 111111);
	assert(!entry && t->map_init);
	ft_transform_rawmap_to_arr2d(t);
	t->err = t->err_map_invalid;
	ft_err(!ft_is_valid_map(t), t, __FILE__, __LINE__);
}
