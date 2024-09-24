/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:38:03 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:39:19 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	save_file_helper2(t_cube *cub, t_sf *sf, char **file)
{
	printf("Error\nInvalid variables on the map.\n");
	free_stuff(cub);
	freetab(sf->tmp);
	freetab(file);
	if (cub->level > 1)
		close_x(cub);
	free(cub->path);
	free(cub->txt);
	exit(1);
}

void	save_file_helper3(t_cube *cub, t_sf *sf, char **file)
{
	(printf("Error\nInvalid texture paths.\n"),
		freetab(file), freetab(sf->tmp));
	free_stuff(cub);
	if (cub->level > 1)
		close_x(cub);
	(free(cub->path), free(cub->txt));
	exit(1);
}

void	save_file_helper(t_cube *cub, t_sf *sf, char **file)
{
	while (sf->j < sf->i)
	{
		sf->tmp = ft_split(file[sf->j], ' ');
		if (tablen(sf->tmp) != 2)
			save_file_helper3(cub, sf, file);
		if (sf->tmp[0][0] == 'F' || sf->tmp[0][0] == 'C')
			color_filler(cub, sf->tmp, file);
		else if (!ft_strncmp(sf->tmp[0], "NO", 2)
			|| !ft_strncmp(sf->tmp[0], "SO", 2)
			|| !ft_strncmp(sf->tmp[0], "WE", 2)
			|| !ft_strncmp(sf->tmp[0], "EA", 2))
		{
			cub->txt[sf->x].type = ft_strdup(sf->tmp[0]);
			cub->txt[sf->x++].path = ft_strdup(sf->tmp[1]);
		}
		else
			save_file_helper2(cub, sf, file);
		freetab(sf->tmp);
		sf->j++;
	}
}

void	save_file(t_cube *cub, char **file)
{
	t_sf	sf;

	sf.i = 0;
	sf.x = 0;
	while (file[sf.i])
	{
		sf.j = 0;
		while (file[sf.i][sf.j] && file[sf.i][sf.j] == ' ')
			sf.j++;
		if (file[sf.i][sf.j] == '1')
			break ;
		sf.i++;
	}
	if (!file[sf.i])
		(printf("Error\nInvalid map.\n"), freetab(file), exit(1));
	sf.j = 0;
	save_file_helper(cub, &sf, file);
	cub->c_rgb = rgb_to_hex(cub->c_r, cub->c_g, cub->c_b);
	cub->f_rgb = rgb_to_hex(cub->f_r, cub->f_g, cub->f_b);
	sf.j = 0;
	cub->map.map = (char **) malloc((tablen(file + sf.i) + 1) * sizeof(char *));
	while (file[sf.i])
		cub->map.map[sf.j++] = ft_strdup(file[sf.i++]);
	cub->map.map[sf.j] = NULL;
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
