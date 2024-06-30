/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: to <to@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:33:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/30 12:17:52 by to               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	load_texture(t_cube *cub, t_txt *txt)
{
	txt->img = mlx_xpm_file_to_image(cub->con, txt->path, &txt->width, &txt->height);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
			&txt->line_length, &txt->endian);
}

void	load_textures(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 15)
		load_texture(cub, &cub->txt[i++]);
}

void increment_alphabet(char *str, int index)
{
	int i;

	i = 0;
	while (str[i] && (str[i] < 65 || str[i] > 90))
		i++;
	str[i] = 65 + index;
}

void increment_numbers(char *str, int index)
{
	int i;

	i = 0;
	while (str[i] && (str[i] < 48 || str[i] > 57))
		i++;
	str[i] = 48 + index;
}

void increment_numbers_2(char *str, int index)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '1')
		i++;
	str[i + 1] = 48 + index;
}
