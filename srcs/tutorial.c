/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:45:41 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	tutorial(t_cube *cub, int bits_per_pixel)
{
	fade_to_black(cub, 0.4, bits_per_pixel);
	draw_xpm_animation(11, WIDTH / 10, HEIGHT / 10, cub->keyboard);
	draw_xpm_animation(9, WIDTH / 10, HEIGHT / 8, cub->keyboard);
	draw_xpm_animation(4, WIDTH / 11.5, HEIGHT / 8, cub->keyboard);
	draw_xpm_animation(8, WIDTH / 8.8, HEIGHT / 8, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 7.5, HEIGHT / 7.4,
		0xFFFFFF, " -   Player Movement");
	draw_xpm_animation(0, WIDTH / 2.5, HEIGHT / 8, cub->keyboard);
	draw_xpm_animation(1, WIDTH / 2.32, HEIGHT / 8, cub->keyboard);
	draw_xpm_animation(2, WIDTH / 2.17, HEIGHT / 8, cub->keyboard);
	draw_xpm_animation(3, WIDTH / 2.04, HEIGHT / 8, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 1.94, HEIGHT / 7,
		0xFFFFFF, " -   Change weapons");
	draw_xpm_animation(6, WIDTH / 11, HEIGHT / 3, cub->keyboard);
	draw_xpm_animation(7, WIDTH / 9.2, HEIGHT / 3, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 7.5, HEIGHT / 2.85,
		0xFFFFFF, " -   Look right, look left");
	draw_xpm_animation(5, WIDTH / 2.2, HEIGHT / 3, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 2.02, HEIGHT / 2.85,
		0xFFFFFF, " -   Options menu");
	draw_xpm_animation(10, WIDTH / 2.5, HEIGHT / 1.2, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 2.2, HEIGHT / 1.175,
		0xFFFFFF, " -   Close the tutorial!");
}
