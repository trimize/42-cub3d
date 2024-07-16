/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:41:47 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:35:51 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// If there's a problem it returns 1.
int	char_checker(char *line)
{
	int		i;
	int		j;
	char	*chars;

	i = 0;
	chars = "10NSEW D|OCGHAQVRXncpvswk";
	while (line[i])
	{
		j = 0;
		while (chars[j])
		{
			if (line[i] == chars[j])
				break ;
			j++;
		}
		if (!chars[j])
			return (1);
		i++;
	}
	return (0);
}

void	check_characters(t_cube *cub, int y, int x)
{
	if (cub->map.map[y][x] == '|' || cub->map.map[y][x] == 'O'
		|| cub->map.map[y][x] == 'C' || cub->map.map[y][x] == 'G')
		cub->weapon_counter++;
	else if (cub->map.map[y][x] == 'A' || cub->map.map[y][x] == 'H'
		|| cub->map.map[y][x] == 'Q' || cub->map.map[y][x] == 'V'
		|| cub->map.map[y][x] == 'R' || cub->map.map[y][x] == 'X')
		cub->items_counter++;
	else if (cub->map.map[y][x] == 'D')
		cub->door_counter++;
	else if (cub->map.map[y][x] == 'r' || cub->map.map[y][x] == 'n'
		|| cub->map.map[y][x] == 'c' || cub->map.map[y][x] == 'p'
		|| cub->map.map[y][x] == 'v' || cub->map.map[y][x] == 's'
		|| cub->map.map[y][x] == 'w' || cub->map.map[y][x] == 'k')
		cub->enemy_counter++;
}

void	player_checker(t_cube *cub)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (cub->map.map[i])
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == 'N' || cub->map.map[i][j] == 'W'
				|| cub->map.map[i][j] == 'E' || cub->map.map[i][j] == 'S')
				counter++;
			check_characters(cub, i, j);
			j++;
		}
		i++;
	}
	if (!counter)
		(printf("Error\nPlayer not found in the map.\n"), exit_free(cub));
	else if (counter > 1)
		(printf("Error\nMore than one player in the map.\n"), exit_free(cub));
}

int	space_checker_horizontal(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (j > 0 && map[i][j - 1] != '1')
					return (1);
				while (map[i][j] == ' ')
					j++;
				if (map[i][j] && map[i][j] != '1')
					return (1);
			}
			if (map[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

int	space_checker_vertical(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i][j])
	{
		while (map[i])
		{
			if (map[i][j] == ' ')
			{
				if (i > 0 && map[i - 1][j] != '1')
					return (1);
				while (map[i] && map[i][j] == ' ')
					i++;
				if (map[i] && map[i][j] && map[i][j] != '1')
					return (1);
			}
			if (map[i])
				i++;
		}
		j++;
		i = 0;
	}
	return (0);
}
