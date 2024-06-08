/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:41:47 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 21:07:13 by mbrandao         ###   ########.fr       */
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
	chars = "10NSEW ";
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
		i++;
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

void	save_file(t_cube *cub, char **file)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
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
		cub->txt[j].type = ft_strdup(tmp[0]);
		cub->txt[j].path = ft_strdup(tmp[1]);
		freetab(tmp);
		j++;
	}
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

void	color_filler(t_cube *cub, int *i)
{
	char	**tmp;

	tmp = ft_split(cub->txt[*i].path, ',');
	if (!tmp || tablen(tmp) != 3)
		printf("Error\nInvalid variables on the map.\n"), exit(1); // TODO Display better error message and fix leaks.
	cub->txt[*i].r = ft_atoi(tmp[0]);
	cub->txt[*i].g = ft_atoi(tmp[1]);
	cub->txt[*i].b = ft_atoi(tmp[2]);
	freetab(tmp);
	if (cub->txt[*i].r < 0 || cub->txt[*i].r > 255 || cub->txt[*i].g < 0
		|| cub->txt[*i].g > 255 || cub->txt[*i].b < 0 || cub->txt[*i].b > 255)
		printf("Error\nInvalid RGB values.\n"), exit(1); // TODO Display better error message and fix leaks.
}

void	variables_checker(t_cube *cub)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (cub->txt[i].type[0] == 'F' || cub->txt[i].type[0] == 'C')
			color_filler(cub, &i);
		else if (!ft_equalstr(cub->txt[i].type, "NO")
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
