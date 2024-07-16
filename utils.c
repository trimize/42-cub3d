/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:23:05 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/15 22:57:24 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	tablen(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	get_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid file.");
		free(call_cub()->path);
		exit(1);
	}
	return (fd);
}

int	ft_equalstr(char const *str, char const *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (!str[i] && !str2[i])
		return (1);
	return (0);
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	search_txt(t_cube *cub, char c)
{
	int	i;

	i = 0;
	if (c == 'D')
		return (10);
	while (i < 4)
	{
		if (cub->txt[i].type && cub->txt[i].type[0] == c)
			return (i);
		i++;
	}
	return (-1);
}
