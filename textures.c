/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:33:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/09 18:07:51 by mbrandao         ###   ########.fr       */
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
	while (i < 4)
		load_texture(cub, &cub->txt[i++]);
}
