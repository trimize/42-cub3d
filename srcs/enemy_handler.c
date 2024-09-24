/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:32:51 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	enemy_handler_helper4(t_cube *cub, t_enemy *enemy, t_txt **txt)
{
	if (cub->player.hit == 1 && enemy->dist < enemy->attack_range
		&& cub->rays[WIDTH / 2].dist > enemy->dist)
	{
		cub->player.hit = 0;
		enemy->hp -= cub->player.atk;
		enemy->hurt = 1;
	}
	if (cub->option_bool == -1 && !enemy->hurt)
		enemy->txt = enemy_animation_atk(cub,
				txt[2], enemy, enemy->dist);
	if (enemy->last_attack == 1 && enemy->dist
		< enemy->attack_range && cub->option_bool == -1
		&& cub->weapons_in_slot[cub->player.weapon - 1] != 3)
	{
		cub->player.hp -= 25;
		enemy->last_attack = -1;
	}
}

void	enemy_handler_helper3(t_cube *cub, t_enemy *enemy)
{
	if (cub->player.y > enemy->y && cub->map.map[(int)(enemy->y
			+ ENEMY_SPEED)][(int) enemy->x] != '1' && can_walk(cub,
				(int)(enemy->y + ENEMY_SPEED), (int) enemy->x))
		enemy->y += ENEMY_SPEED;
	else if (cub->player.y < enemy->y && cub->map.map[(int)(enemy->y
			- ENEMY_SPEED)][(int) enemy->x] != '1' && can_walk(cub,
				(int)(enemy->y - ENEMY_SPEED), (int) enemy->x))
		enemy->y -= ENEMY_SPEED;
}

void	enemy_handler_helper2(t_cube *cub, t_enemy *enemy, t_txt **txt)
{
	enemy->txt = enemy_animation_handler(txt[1], enemy->run_max_frame);
	if (cub->player.hit == 1 && enemy->draw_start >= WIDTH / 8
		&& enemy->draw_end <= WIDTH / 1.1 && (cub->weapons_in_slot
			[cub->player.weapon - 1] == 2 || cub->weapons_in_slot
			[cub->player.weapon - 1] == 4) && cub->rays[WIDTH / 2].dist
		> enemy->dist)
	{
		cub->player.hit = 0;
		enemy->hp -= cub->player.atk;
		enemy->hurt = 1;
	}
	if (cub->player.x > enemy->x && cub->map.map[(int) enemy->y]
		[(int)(enemy->x + ENEMY_SPEED)] != '1' && can_walk(cub,
			(int) enemy->y, (int)(enemy->x + ENEMY_SPEED)))
		enemy->x += ENEMY_SPEED;
	else if (cub->player.x < enemy->x && cub->map.map[(int) enemy->y]
		[(int)(enemy->x - ENEMY_SPEED)] != '1' && can_walk(cub,
			(int) enemy->y, (int)(enemy->x - ENEMY_SPEED)))
		enemy->x -= ENEMY_SPEED;
	enemy_handler_helper3(cub, enemy);
}

void	enemy_handler_helper(t_cube *cub, t_enemy *enemy, t_txt **txt)
{
	if (enemy->dist > 500 && cub->option_bool == -1)
	{
		enemy->txt = enemy_animation_handler(txt[0], enemy->idle_max_frame);
		if (cub->player.hit == 1 && enemy->draw_start >= WIDTH / 4
			&& enemy->draw_end <= WIDTH / 1.4 && (cub->weapons_in_slot
				[cub->player.weapon - 1] == 2 || cub->weapons_in_slot
				[cub->player.weapon - 1] == 4) && cub->rays[WIDTH / 2].dist
			> enemy->dist)
		{
			cub->player.hit = 0;
			enemy->hp -= cub->player.atk;
			enemy->hurt = 1;
		}
	}
	else if (enemy->dist > enemy->attack_range
		&& enemy->attacking_bool == 0 && cub->option_bool == -1)
		enemy_handler_helper2(cub, enemy, txt);
	else
		enemy_handler_helper4(cub, enemy, txt);
}

void	enemy_handler(t_cube *cub, t_enemy *enemy, t_txt **txt)
{
	enemy->dist = dist((enemy->x * TILE_SIZE), (enemy->y * TILE_SIZE),
			cub->player.x * TILE_SIZE, cub->player.y * TILE_SIZE);
	if (enemy->hp > 0)
	{
		enemy_handler_helper(cub, enemy, txt);
		if (cub->option_bool == -1 && enemy->hurt)
			enemy->txt = enemy_animation_hurt(cub, txt[3],
					enemy, enemy->hurt_max_frame);
	}
	else if (enemy->dead == 0)
		enemy->txt = enemy_animation_death(cub, txt[4],
				enemy, enemy->death_max_frame);
}
