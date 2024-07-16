/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:35:12 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:38:28 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	flc_helper(char **map, int *i, int *j)
{
	while (map[*i])
	{
		*j = ft_strlen(map[*i]) - 1;
		if ((map[*i][0] != '1' && map[*i][0] != ' ')
			|| (map[*i][*j] != '1' && map[*i][*j] != ' '))
			return (1);
		(*i)++;
	}
	(*i)--;
	*j = 0;
	return (0);
}

// If there's a problem it returns 1.
int	first_and_last_checker(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (1);
		j++;
	}
	if (flc_helper(map, &i, &j))
		return (1);
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

void	color_filler_helper(t_cube *cub, char **tmp, char **tab)
{
	if (tab[0][0] == 'C')
	{
		cub->c_r = ft_atoi(tmp[0]);
		cub->c_g = ft_atoi(tmp[1]);
		cub->c_b = ft_atoi(tmp[2]);
	}
	else
	{
		cub->f_r = ft_atoi(tmp[0]);
		cub->f_g = ft_atoi(tmp[1]);
		cub->f_b = ft_atoi(tmp[2]);
	}
	freetab(tmp);
}

void	color_filler_helper2(t_cube *cub, char **tab, char **file)
{
	if (tab[0][0] == 'C' && (cub->c_r < 0 || cub->c_r > 255 || cub->c_g < 0
		|| cub->c_g > 255 || cub->c_b < 0 || cub->c_b > 255))
	{
		printf("Error\nInvalid RGB values.\n");
		freetab(tab);
		freetab(file);
		if (cub->level > 1)
			close_x(cub);
		free(cub->txt);
		free(cub->path);
		exit(1);
	}
	else if (tab[0][0] == 'F' && (cub->f_r < 0 || cub->f_r > 255 || cub->f_g < 0
		|| cub->f_g > 255 || cub->f_b < 0 || cub->f_b > 255))
	{
		printf("Error\nInvalid RGB values.\n");
		freetab(tab);
		freetab(file);
		if (cub->level > 1)
			close_x(cub);
		free(cub->txt);
		free(cub->path);
		exit(1);
	}
}

void	color_filler(t_cube *cub, char **tab, char **file)
{
	char	**tmp;

	tmp = ft_split(tab[1], ',');
	if (!tmp || tablen(tmp) != 3)
	{
		printf("Error\nInvalid variables on the map.\n");
		if (tmp)
			freetab(tmp);
		freetab(tab);
		freetab(file);
		if (cub->level > 1)
			close_x(cub);
		free(cub->txt);
		free(cub->path);
		exit(1);
	}
	color_filler_helper(cub, tmp, tab);
	color_filler_helper2(cub, tab, file);
}
