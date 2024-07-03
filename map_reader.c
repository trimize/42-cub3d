/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:41:47 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/01 14:57:51 by trimize          ###   ########.fr       */
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
	chars = "10NSEW DA";
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
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		if ((map[i][0] != '1' && map[i][0] != ' ') || (map[i][j] != '1' && map[i][j] != ' '))
			return (1);
		i++;
	}
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

void	color_filler(t_cube *cub, char **tab)
{
	char	**tmp;

	tmp = ft_split(tab[1], ',');
	if (!tmp || tablen(tmp) != 3)
		printf("Error\nInvalid variables on the map.\n"), exit(1); // TODO Display better error message and fix leaks.
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
	if (tab[0][0] == 'C' && (cub->c_r < 0 || cub->c_r > 255 || cub->c_g < 0
		|| cub->c_g > 255 || cub->c_b < 0 || cub->c_b > 255))
		printf("Error\nInvalid RGB values.\n"), exit(1); // TODO Display better error message and fix leaks.
	else if (tab[0][0] == 'F' && (cub->f_r < 0 || cub->f_r > 255 || cub->f_g < 0
		|| cub->f_g > 255 || cub->f_b < 0 || cub->f_b > 255))
		printf("Error\nInvalid RGB values.\n"), exit(1); // TODO Display better error message and fix leaks.
}

void	save_file(t_cube *cub, char **file)
{
	int		i;
	int		j;
	int		x;
	char	**tmp;

	i = 0;
	x = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] && file[i][j] == ' ')
			j++;
		if (file[i][j] == '1')
			break ;
		i++;
	}
	if (!file[i])
		(printf("Error\nInvalid map.\n"), freetab(file), exit(1)); // TODO Display better error message.
	j = 0;
	while (j < i)
	{
		tmp = ft_split(file[j], ' ');
		if (tablen(tmp) != 2)
		{
			(printf("Error\nInvalid texture paths.\n"), freetab(file), freetab(tmp));
			while (j >= 0)
				(free(cub->txt[j].type), free(cub->txt[j--].path));
			exit(1); // TODO Display better error message.
		}
		if (tmp[0][0] == 'F' || tmp[0][0] == 'C')
			color_filler(cub, tmp);
		else
		{
			cub->txt[x].type = ft_strdup(tmp[0]);
			cub->txt[x++].path = ft_strdup(tmp[1]);
		}
		freetab(tmp);
		j++;
	}

	cub->c_rgb = rgb_to_hex(cub->c_r, cub->c_g, cub->c_b);
	cub->f_rgb = rgb_to_hex(cub->f_r, cub->f_g, cub->f_b);
	j = 0;
	cub->map.map = (char **) malloc((tablen(file + i) + 1) * sizeof(char *));
	while (file[i])
		cub->map.map[j++] = ft_strdup(file[i++]);
	cub->map.map[j] = NULL;
	freetab(file);
}

char	**read_file(char *path)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	**result;

	fd = get_fd(path);
	line = ft_strdup("");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line = ft_strjoin_gnl(line, tmp);
		free(tmp);
	}
	result = ft_split(line, '\n');
	free(line);
	close(fd);
	return (result);
}


void	variables_checker(t_cube *cub)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!ft_equalstr(cub->txt[i].type, "NO")
			&& !ft_equalstr(cub->txt[i].type, "SO")
			&& !ft_equalstr(cub->txt[i].type, "WE")
			&& !ft_equalstr(cub->txt[i].type, "EA"))
			printf("Error\nInvalid variables on the map.\n"), exit(1); // TODO Display better error message and fix leaks.
		i++;
	}
}

void	set_size(t_map *map)
{
	int	i;
	int	big;

	i = 0;
	big = ft_strlen(map->map[0]);
	while (map->map[i])
		i++;
	map->rows = i;
	i = 1;
	while (map->map[i])
	{
		if ((int) ft_strlen(map->map[i]) > big)
			big = ft_strlen(map->map[i]);
		i++;
	}
	map->cols = big;
}

void	map_filler(t_map *map)
{
	int	i;
	int	cols;

	i = 0;
	set_size(map);
	while (map->map[i])
	{
		cols = ft_strlen(map->map[i]);
		if (cols < map->cols)
		{
			while (cols < map->cols)
			{
				map->map[i] = ft_strjoin_gnl(map->map[i], " ");
				cols++;
			}
		}
		i++;
	}
}
int	check_cub(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (len < 4)
		return (1);
	if (file[len] != 'b')
		return (1);
	if (file[len - 1] != 'u')
		return (1);
	if (file[len - 2] != 'c')
		return (1);
	if (file[len - 3] != '.')
		return (1);
	return (0);
}
