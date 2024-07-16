/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:33:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 17:32:18 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	load_texture(t_cube *cub, t_txt *txt)
{
	txt->img = mlx_xpm_file_to_image(cub->con, txt->path,
			&txt->width, &txt->height);
	if (!txt->img)
		return (1);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
			&txt->line_length, &txt->endian);
	if (!txt->addr)
	{
		mlx_destroy_image(cub->con, txt->img);
		return (1);
	}
	return (0);
}

void	load_textures(t_cube *cub, t_txt *txt, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (load_texture(cub, &txt[i]))
		{
			while (--i > 0)
				mlx_destroy_image(cub->con, txt[i].img);
			free_stuff(cub);
			freetab(cub->map.map);
			free(cub->path);
			if (cub->weapon_counter)
				free(cub->weapons);
			if (cub->enemy_counter)
				(free(cub->all_enemies), free(cub->dropped_items));
			if (cub->items_counter)
				free(cub->items);
			if (cub->door_counter)
				free(cub->doors);
			(free(cub->rays), mlx_destroy_window(cub->con, cub->win));
			(mlx_destroy_display(cub->con), free(cub->con), exit(1));
		}
		i++;
	}
}

void	increment_alphabet(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] < 65 || str[i] > 90))
		i++;
	str[i] = 65 + index;
}

char	*str_add_end(char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = 0;
	free(str);
	return (tmp);
}

char	*rm_last_c(char *str)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(ft_strlen(str) * sizeof(char));
	i = 0;
	while (i < (int)(ft_strlen(str) - 1))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	free(str);
	return (tmp);
}
