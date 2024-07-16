/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:17:55 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/15 22:43:47 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	fov_helper(t_cube *cub)
{
	char	*fov_str;

	draw_xpm_alpha(5, WIDTH / 2.3, HEIGHT / 4, cub);
	draw_xpm_alpha(14, WIDTH / 2.2, HEIGHT / 4, cub);
	draw_xpm_alpha(21, WIDTH / 2.1, HEIGHT / 4, cub);
	fov_str = to_str(cub->fov);
	if (cub->fov == 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 4, cub);
	else if (ft_strlen(fov_str) == 1)
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
	else if (ft_strlen(fov_str) == 2)
	{
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[1] - 48, WIDTH / 1.75, HEIGHT / 4, cub);
	}
	else if (ft_strlen(fov_str) == 3)
	{
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[1] - 48, WIDTH / 1.75, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[2] - 48, WIDTH / 1.7, HEIGHT / 4, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 3.8, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 3.8, cub);
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	free(fov_str);
}

void	fov_option(t_cube *cub)
{
	fov_helper(cub);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62
		&& cub->mouse_y > HEIGHT / 3.8 && cub->mouse_y < HEIGHT / 3.4
		&& cub->key.mouse_l)
	{
		cub->fov += 10;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85
		&& cub->mouse_y > HEIGHT / 3.8 && cub->mouse_y < HEIGHT / 3.4
		&& cub->key.mouse_l)
	{
		cub->fov -= 10;
		cub->key.mouse_l = 0;
	}
}

void	minimap_option(t_cube *cub)
{
	draw_xpm_alpha(18, WIDTH / 2.35, HEIGHT / 1.6, cub);
	draw_xpm_alpha(7, WIDTH / 2.25, HEIGHT / 1.6, cub);
	draw_xpm_alpha(14, WIDTH / 2.16, HEIGHT / 1.6, cub);
	draw_xpm_alpha(22, WIDTH / 2.08, HEIGHT / 1.6, cub);
	draw_xpm_alpha(12, WIDTH / 1.94, HEIGHT / 1.6, cub);
	draw_xpm_alpha(0, WIDTH / 1.87, HEIGHT / 1.6, cub);
	draw_xpm_alpha(15, WIDTH / 1.81, HEIGHT / 1.6, cub);
	if (cub->minimap_bool == -1)
		draw_xpm_animation(23, WIDTH / 1.65, HEIGHT / 1.578, cub->txt);
	else
		draw_xpm_animation(24, WIDTH / 1.65, HEIGHT / 1.578, cub->txt);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < ((WIDTH / 1.65)
			+ cub->txt[23].width) && cub->mouse_y > HEIGHT / 1.6
		&& cub->mouse_y < ((HEIGHT / 1.6) + cub->txt[23].height)
		&& cub->key.mouse_l)
	{
		cub->minimap_bool = -cub->minimap_bool;
		cub->key.mouse_l = 0;
	}
}
