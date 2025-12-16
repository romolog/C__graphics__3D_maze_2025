/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_09_set_map_isvalid_textures.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:52:13 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/17 23:00:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>

int	ft_is_valid_textures(t_tr *t)
{
	int		check;
	int		i;
	size_t	len;

	return (1);
	i = -1;
	while (++i < 4)
	{
		len = ft_strlen(t->f_map_textures[i]);
		if (len < 5 || ft_strncmp(t->f_map_textures[i] + len - 4, ".xpm", 5))
			return (0);
		check = open(t->f_map_textures[i], O_RDONLY);
		if (check == -1)
			return (0);
		ft_err(ft_free_close_fd(&check), t, __FILE__, __LINE__);
	}
	return (1);
}
