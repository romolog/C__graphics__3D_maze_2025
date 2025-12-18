/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_25_utils_mix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:44:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:17:02 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_space_tab_newline(char *entry)
{
	while (*entry == ' ' || *entry == '\t' || *entry == '\n')
		entry++;
	if (*entry)
		return (0);
	return (1);
}

int	ft_abs(int a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}
