/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_91_utils_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:42:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/22 16:32:47 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_free_2d_char(char ***arr)
{
	size_t	i;

	if (!arr || !*arr || !**arr)
		return ;
	i = -1;
	while ((*arr)[++i])
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	ft_free_2d_double(double ***arr)
{
	size_t	i;

	if (!arr || !*arr || !**arr)
		return ;
	i = -1;
	while ((*arr)[++i])
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	ft_free_2d_int(int ***arr)
{
	size_t	i;

	if (!arr || !*arr || !**arr)
		return ;
	i = -1;
	while ((*arr)[++i])
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

int	ft_free_close_fd(int *fd)
{
	if (*fd < 0)
		return (0);
	if (close(*fd) == -1)
		return (errno);
	*fd = -1;
	return (0);
}

void	ft_free_str(char **str)
{
	if (str && *str)
		free(*str);
	if (str)
		*str = NULL;
}
