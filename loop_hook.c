/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:03 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:49:22 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	loop_hook_last(t_cube *cub)
{
	(mlx_put_image_to_window(cub->con, cub->win, cub->img, 0, 0),
		display_messages(cub));
}

int	loop_hook(t_cube *cub)
{
	void	*img;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->img = img;
	cub->addr = mlx_get_data_addr
		(img, &cub->bits_per_pixel, &cub->line_length, &cub->endian);
	if (cub->title_bool == 0 && cub->bg_bool == 0)
		loop_hook_helper(cub);
	if (cub->title_bool == 1 && !cub->victory)
		title_handler(cub);
	if (cub->bg_bool && !cub->victory)
		bg_true(cub);
	loop_hook_last(cub);
	if (!cub->title_bool && !cub->bg_bool
		&& !cub->victory && cub->minimap_bool == 1)
		(draw_map_to_image(cub), draw_player_to_image(cub));
	if (cub->title_bool == 0 && cub->bg_bool == 0 && !cub->victory)
		hud_options_handler(cub);
	if (cub->player.hp <= 0 && !cub->bg_bool && !cub->victory)
		dying_handler(cub);
	else if (cub->player.hp > 0 && !cub->bg_bool && cub->victory)
		next_map(cub);
	if (cub->tuto && !cub->title_bool && !cub->bg_bool && !cub->victory)
		tutorial(cub, cub->bits_per_pixel);
	return (mlx_destroy_image(cub->con, img), 0);
}
