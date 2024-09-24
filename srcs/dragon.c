/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:38:18 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dragon_handler(t_cube *cub)
{
	if (cub->weapons_in_slot[cub->player.weapon - 1] == 4)
	{
		update_animation_dragon(cub);
		draw_xpm_animation(cub->dragon->current_frame,
			WIDTH / 1.6, HEIGHT / 2.2, cub->dragon);
		cub->player.hit = 0;
		if (cub->dragon->current_frame == 4)
			cub->dragon->current_frame = 0;
	}
}

t_enemy	*explosion_sprite2(t_cube *cub)
{
	int		i;
	t_enemy	*enemy;

	i = 0;
	enemy = NULL;
	if (cub->enemy_counter)
	{
		enemy = &cub->all_enemies[i++];
		while (i < cub->enemy_counter)
		{
			if (cub->all_enemies[i].dist < enemy->dist
				&& cub->all_enemies[i].draw_start > 0
				&& cub->all_enemies[i].draw_end < WIDTH)
				enemy = &cub->all_enemies[i];
			i++;
		}
	}
	return (enemy);
}

void	explosion_sprite3(t_cube *cub, t_enemy *enemy)
{
	if ((!enemy || enemy->draw_start < WIDTH || enemy->draw_end > WIDTH)
		&& cub->explosion->launched)
	{
		cub->explosion->x = cub->rays[WIDTH / 2].rx / TILE_SIZE;
		cub->explosion->y = cub->rays[WIDTH / 2].ry / TILE_SIZE;
	}
	else if (enemy && cub->rays[(WIDTH / 2) - 1].dist < enemy->dist
		&& enemy->draw_start > 0 && enemy->draw_end
		< WIDTH && cub->explosion->launched)
	{
		cub->explosion->x = cub->rays[(WIDTH / 2) - 1].rx / TILE_SIZE;
		cub->explosion->y = cub->rays[(WIDTH / 2) - 1].ry / TILE_SIZE;
	}
	else if (enemy && cub->rays[(WIDTH / 2) - 1].dist > enemy->dist
		&& enemy->draw_start > WIDTH / 3 && enemy->draw_end
		< WIDTH / 1.8 && cub->explosion->launched)
	{
		cub->explosion->x = enemy->x;
		cub->explosion->y = enemy->y;
	}
	draw_sprite(cub, &cub->explosion[cub->explosion->current_frame],
		0.4, 40);
}

void	explosion_sprite(t_cube *cub)
{
	t_enemy	*enemy;

	enemy = explosion_sprite2(cub);
	if (cub->option_bool == -1 && cub->key.mouse_l == 1
		&& cub->weapons_in_slot[cub->player.weapon - 1] == 4)
	{
		update_animation_explosion(cub);
		if (cub->explosion->current_frame == 0)
		{
			cub->player.hit = 1;
			cub->explosion->launched = 1;
		}
		else
		{
			cub->explosion->launched = 0;
			cub->player.hit = 0;
		}
		explosion_sprite3(cub, enemy);
		if (cub->explosion->current_frame == 13)
		{
			cub->explosion->current_frame = 0;
			cub->key.mouse_l = 0;
		}
	}
}

void	explosion_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1
		&& cub->weapons_in_slot[cub->player.weapon - 1] == 4)
	{
		update_animation_explosion(cub);
		draw_xpm_animation(cub->explosion->current_frame,
			WIDTH / 2.7, HEIGHT / 3.5, cub->explosion);
		if (cub->explosion->current_frame == 12)
		{
			cub->explosion->current_frame = 0;
			cub->key.mouse_l = 0;
		}
		else if (cub->explosion->current_frame == 1)
			cub->player.hit = 1;
		else
			cub->player.hit = 0;
	}
}
