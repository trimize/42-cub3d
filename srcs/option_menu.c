/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:13:00 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	speed_helper(t_cube *cub)
{
	char	*p_speed_str;

	draw_xpm_alpha(18, WIDTH / 2.35, HEIGHT / 2.6, cub);
	draw_xpm_alpha(15, WIDTH / 2.25, HEIGHT / 2.6, cub);
	draw_xpm_alpha(4, WIDTH / 2.16, HEIGHT / 2.6, cub);
	draw_xpm_alpha(4, WIDTH / 2.08, HEIGHT / 2.6, cub);
	draw_xpm_alpha(3, WIDTH / 2.01, HEIGHT / 2.6, cub);
	p_speed_str = to_str(cub->speed);
	if (cub->fov == 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 2.6, cub);
	else if (ft_strlen(p_speed_str) == 1)
		draw_xpm_number(p_speed_str[0] - 48, WIDTH / 1.8, HEIGHT / 2.6, cub);
	else if (ft_strlen(p_speed_str) == 2)
	{
		draw_xpm_number(p_speed_str[0] - 48, WIDTH / 1.8, HEIGHT / 2.6, cub);
		draw_xpm_number(p_speed_str[1] - 48, WIDTH / 1.75, HEIGHT / 2.6, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 2.5, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 2.5, cub);
	free(p_speed_str);
}

void	speed_option(t_cube *cub)
{
	speed_helper(cub);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62
		&& cub->mouse_y > HEIGHT / 2.5 && cub->mouse_y < HEIGHT / 2.4
		&& cub->key.mouse_l && cub->speed < 10)
	{
		cub->player.speed += 0.009;
		cub->speed++;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85
		&& cub->mouse_y > HEIGHT / 2.5 && cub->mouse_y < HEIGHT / 2.4
		&& cub->key.mouse_l && cub->speed <= 10 && cub->speed > 1)
	{
		cub->player.speed -= 0.009;
		if (cub->player.speed <= 0)
			cub->player.speed = 0.006;
		cub->speed--;
		cub->key.mouse_l = 0;
	}
}

void	sensi_helper(t_cube *cub)
{
	char	*sensi_str;

	draw_xpm_alpha(18, WIDTH / 2.35, HEIGHT / 2, cub);
	draw_xpm_alpha(4, WIDTH / 2.25, HEIGHT / 2, cub);
	draw_xpm_alpha(13, WIDTH / 2.16, HEIGHT / 2, cub);
	draw_xpm_alpha(18, WIDTH / 2.08, HEIGHT / 2, cub);
	draw_xpm_alpha(8, WIDTH / 2.01, HEIGHT / 2, cub);
	sensi_str = to_str(cub->sensi);
	if (cub->sensi <= 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 2, cub);
	else if (ft_strlen(sensi_str) == 1)
		draw_xpm_number(sensi_str[0] - 48, WIDTH / 1.8, HEIGHT / 2, cub);
	else if (ft_strlen(sensi_str) == 2)
	{
		draw_xpm_number(sensi_str[0] - 48, WIDTH / 1.8, HEIGHT / 2, cub);
		draw_xpm_number(sensi_str[1] - 48, WIDTH / 1.75, HEIGHT / 2, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 1.94, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 1.94, cub);
	free(sensi_str);
}

void	sensi_option(t_cube *cub)
{
	sensi_helper(cub);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62
		&& cub->mouse_y > HEIGHT / 1.94 && cub->mouse_y < HEIGHT / 1.85
		&& cub->key.mouse_l && cub->sensi < 10)
	{
		cub->p_rotation += 0.0299 / 4;
		cub->sensi++;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85
		&& cub->mouse_y > HEIGHT / 1.94 && cub->mouse_y < HEIGHT / 1.85
		&& cub->key.mouse_l && cub->sensi <= 10 && cub->sensi > 1)
	{
		cub->p_rotation -= 0.0299 / 4;
		cub->sensi--;
		cub->key.mouse_l = 0;
	}
}

void	draw_options(t_cube *cub)
{
	mlx_mouse_show(cub->con, cub->win);
	draw_xpm_texture(4, WIDTH / 2.5, HEIGHT / 10, cub);
	draw_xpm_alpha(14, WIDTH / 1.99, HEIGHT / 8, cub);
	draw_xpm_alpha(15, WIDTH / 1.92, HEIGHT / 8, cub);
	draw_xpm_alpha(19, WIDTH / 1.86, HEIGHT / 8, cub);
	draw_xpm_alpha(8, WIDTH / 1.8, HEIGHT / 8, cub);
	draw_xpm_alpha(14, WIDTH / 1.75, HEIGHT / 8, cub);
	draw_xpm_alpha(13, WIDTH / 1.7, HEIGHT / 8, cub);
	draw_xpm_alpha(18, WIDTH / 1.65, HEIGHT / 8, cub);
	speed_option(cub);
	sensi_option(cub);
	minimap_option(cub);
	fov_option(cub);
}
