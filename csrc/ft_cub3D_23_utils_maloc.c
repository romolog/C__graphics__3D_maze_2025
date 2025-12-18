/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_23_utils_maloc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:19:59 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:17:01 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cub3D.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strlcpy_malloc(char *ptr, size_t ptr_len, t_tr *t)
{
	char	*f_str;

	if (!ptr)
		return (NULL);
	f_str = malloc(ptr_len + 1);
	ft_err(!f_str, t, __FILE__, __LINE__);
	if (!f_str)
		return (NULL);
	ft_strlcpy(f_str, ptr, ptr_len + 1);
	return (f_str);
}

static void	ft_call_copy(char *f_str, char **dst, char *add, int add_len)
{
	int		i;

	ft_strlcpy(f_str, *dst, ft_strlen(*dst) + 1);
	if (ft_strlen(add) >= (size_t)add_len)
		ft_strlcpy(f_str + ft_strlen(*dst), add, add_len + 1);
	else
	{
		ft_strlcpy(f_str + ft_strlen(*dst), add, ft_strlen(add) + 1);
		i = ft_strlen(*dst) + ft_strlen(add) - 1;
		while (++i <= add_len)
			f_str[i] = '\0';
	}
	free(*dst);
	*dst = f_str;
}

void	ft_add_str_malloc(char **dst, char *add, size_t add_len, t_tr *t)
{
	char	*f_str;

	if (!add || !dst)
		return ;
	if (!*dst)
	{
		*dst = ft_strlcpy_malloc(add, add_len, t);
		ft_err(!*dst, t, __FILE__, __LINE__);
		return ;
	}
	else if (!add_len || (ft_strlen(*dst) < ft_strlen(*dst) + add_len))
	{
		f_str = malloc(ft_strlen(*dst) + add_len + 1);
		ft_err(!f_str, t, __FILE__, __LINE__);
		if (!f_str)
			return ;
		ft_call_copy(f_str, dst, add, add_len);
		return ;
	}
	t->err = t->err_overflow;
	ft_err(1, t, __FILE__, __LINE__);
}
