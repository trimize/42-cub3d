/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:22:11 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 18:30:38 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	start_keys2(t_cube *cub)
{
	if (!cub->retry)
	{
		cub->title_bool = 1;
		cub->bg_bool = 0;
	}
	cub->fade_factor = 1.0;
	cub->tuto = 0;
	cub->player.hit = 0;
	cub->player.last_atk = 0;
	cub->explosion->x = 0;
	cub->explosion->y = 0;
	cub->explosion->launched = 0;
	cub->enemies_nb = 2;
	cub->victory = 0;
	cub->minimap_bool = -1;
	cub->player_run_value = 0;
	cub->next_lvl_start = 0;
	cub->next_lvl_end = 0;
	cub->idle_delay = 0;
}

void	start_keys(t_cube *cub)
{
	cub->key.w = 0;
	cub->key.a = 0;
	cub->key.s = 0;
	cub->key.d = 0;
	cub->key.left = 0;
	cub->key.right = 0;
	cub->option_bool = -1;
	cub->sensi = 5;
	cub->p_rotation = 0.0299;
	cub->fov = 60;
	cub->speed = 3;
	cub->player.hp = 100;
	cub->player.weapon = 1;
	init_w_slots(cub);
	cub->player.arrows = 5;
	cub->player.speed = 0.007;
	cub->player.atk = 20;
	cub->player.atk_item_amount = 0;
	cub->player.speed_item_amount = 0;
	start_keys2(cub);
}
