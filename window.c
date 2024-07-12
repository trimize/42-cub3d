/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/12 22:19:21 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	close_x(t_cube *cub)
{
	printf("You closed the game.");
	int	i = 0;
	while (i < 4)
		mlx_destroy_image(cub->con, cub->txt[i++].img);
	mlx_destroy_window(cub->con, cub->win);
	mlx_destroy_display(cub->con);
	free(cub->con);
	// free_map(data->map);
	exit_free(cub);
	return (0);
}

int mouse_events(int key)
{
	if (key == 1)
	{
		(call_cub())->key.mouse_l = 1;
	}
	return (1);
}

int	handle_key_press(int key, t_cube *cub)
{
	//printf("key pressed %d\n", key);
	if (key == XK_Escape)
	{
		printf("You pressed ESC and closed the game\n");
		close_x(cub);
		exit(1);
	}
	else if (key == XK_w && cub->option_bool == -1)
		cub->key.w = 1;
	else if (key == XK_s && cub->option_bool == -1)
		cub->key.s = 1;
	else if (key == XK_a && cub->option_bool == -1)
		cub->key.a = 1;
	else if (key == XK_d && cub->option_bool == -1)
		cub->key.d = 1;
	else if (key == XK_Left)
		cub->key.left = 1;
	else if (key == XK_Right)
		cub->key.right = 1;
	else if (key == XK_Alt_L && !cub->tuto)
		cub->option_bool = -cub->option_bool;
	else if (key == XK_Tab)
	{
		if (!cub->bg_bool && !cub->title_bool && cub->tuto)
			cub->tuto = 0;
	}
	else if (key == XK_1 && cub->player.hp > 0)
		cub->player.weapon = 1;
	else if (key == XK_2 && cub->player.hp > 0)
		cub->player.weapon = 2;
	else if (key == XK_3 && cub->player.hp > 0)
		cub->player.weapon = 3;
	else if (key == XK_4 && cub->player.hp > 0)
		cub->player.weapon = 4;
	else if (key == XK_e)
		cub->key.e = 1;
	else if (key == XK_Return)
		cub->bg_bool = 0;
	return (0);
}

int	handle_key_release(int key, t_cube *cub)
{
	if (key == XK_w)
		cub->key.w = 0;
	else if (key == XK_s)
		cub->key.s = 0;
	else if (key == XK_a)
		cub->key.a = 0;
	else if (key == XK_d)
		cub->key.d = 0;
	else if (key == XK_Left)
		cub->key.left = 0;
	else if (key == XK_Right)
		cub->key.right = 0;
	return (0);
}

// void	game_loop(t_cube *cub)
// {
// 	while (1)
// 	{
// 		draw_player(cub);
// 		mlx_do_sync(cub->con);
// 	}
// }

//int	loop_hook(t_cube *cub)
//{
//	mlx_clear_window(cub->con, cub->win);
//	draw_map(cub);
//	draw_player(cub);
//	mlx_do_sync(cub->con);
//	return (0);
//}


void	draw_square_to_image(char *addr, int line_length, int x, int y, int color)
{
	int	i;
	int	j;

	for (i = 0; i < MINIMAP_SIZE; i++)
	{
		for (j = 0; j < MINIMAP_SIZE; j++)
		{
			((int *)(addr))[(y + i) * line_length / 4 + x + j] = color;
		}
	}
}

void	draw_p_to_image(char *addr, int line_length, int x, int y, int color)
{
	int	i;
	int	j;

	if (x < 0 || y < 0 || x + PLAYER_SIZE >= line_length / 4 || y + PLAYER_SIZE >= line_length / 4)
        return;

	for (i = 0; i < PLAYER_SIZE; i++)
	{
		for (j = 0; j < PLAYER_SIZE; j++)
		{
			((int *)(addr))[(y + i) * line_length / 4 + x + j] = color;
		}
	}
}

void	draw_player_to_image(t_cube *cub, char *addr, int line_length)
{
    int	x;
    int	y;
    int	color;

    // Set the player color
    color = 0xFF0000;  // Red

    // Calculate the player's position in pixels
    x = cub->player.x * MINIMAP_SIZE;
    y = cub->player.y * MINIMAP_SIZE;

    // Draw the player as a square
    draw_p_to_image(addr, line_length, x, y, color);
}

void	draw_map_to_image(t_cube *cub, char *addr, int line_length)
{
	int	x;
	int	y;
	int	color;

	for (y = 0; y < cub->map.rows; y++)
	{
		for (x = 0; x < cub->map.cols; x++)
		{
			if (cub->map.map[y][x] == '1')  // Wall
				color = 0x00004A;  // Green
			else if (cub->map.map[y][x] == ' ')
				continue ;
			else
				color = 0xffece0;  // White

			draw_square_to_image(addr, line_length, x * MINIMAP_SIZE, y * MINIMAP_SIZE, color);
		}
	}
}

int	remove_corners(t_cube *cub, int x, int y)
{
	if (cub->map.map[y + 1][x] == '2')
		(cub->map.map[y + 1][x] = '0', printf("yes"));
	if (cub->map.map[y - 1][x] == '2')
		(cub->map.map[y - 1][x] = '0', printf("yes2"));
	if (cub->map.map[y][x + 1] == '2')
		(cub->map.map[y][x + 1] = '0', printf("yes3"));
	if (cub->map.map[y][x - 1] == '2')
		(cub->map.map[y][x - 1] = '0', printf("yes4"));
	return (1);
}

int	is_corner(t_cube *cub, int x, int y)
{
	if ((cub->map.map[y - 1][x + 1] == '0' || cub->map.map[y - 1][x + 1] == ' ') && cub->map.map[y][x + 1] == '1' && cub->map.map[y - 1][x] == '1')
		(cub->map.map[y - 1][x + 1] = '2');
	else if ((cub->map.map[y - 1][x - 1] == '0' || cub->map.map[y - 1][x - 1] == ' ') && cub->map.map[y][x - 1] == '1' && cub->map.map[y - 1][x] == '1')
		(cub->map.map[y - 1][x - 1] = '2');
	else if ((cub->map.map[y + 1][x - 1] == '0' || cub->map.map[y + 1][x - 1] == ' ') && cub->map.map[y][x - 1] == '1' && cub->map.map[y + 1][x] == '1')
		(cub->map.map[y + 1][x - 1] = '2');
	else if ((cub->map.map[y + 1][x + 1] == '0' || cub->map.map[y + 1][x + 1] == ' ') && cub->map.map[y + 1][x] == '1' && cub->map.map[y][x + 1] == '1')
		(cub->map.map[y + 1][x + 1] = '2', printf("yes"));
	//if (cub->map.map[y + 1][x] == '2')
	//	(cub->map.map[y + 1][x] = '0', printf("yes"));
	//if (cub->map.map[y - 1][x] == '2')
	//	(cub->map.map[y - 1][x] = '0', printf("yes2"));
	//if (cub->map.map[y][x + 1] == '2')
	//	(cub->map.map[y][x + 1] = '0', printf("yes3"));
	//if (cub->map.map[y][x - 1] == '2')
	//	(cub->map.map[y][x - 1] = '0', printf("yes4"));
	return (1);
}

void mouse_rotate(t_cube *cub)
{
	int m_x;

	m_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x >= WIDTH - (WIDTH / 10) || cub->mouse_x <= WIDTH / 5)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (cub->mouse_y >= HEIGHT - (HEIGHT / 10) || cub->mouse_x <= HEIGHT / 5)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (m_x != cub->mouse_x)
	{
		if (cub->mouse_x > m_x)
			rotate_player(cub, -(cub->p_rotation));
		else if (cub->mouse_x < m_x)
			rotate_player(cub, cub->p_rotation);
	}
	// printf("Mouse position :\nx : %d\ny : %d\n\n", cub->mouse_x, cub->mouse_y);
}

void	tutorial(t_cube *cub, int bits_per_pixel)
{
	fade_to_black(cub, 0.4, bits_per_pixel);
	draw_xpm_animation(11, WIDTH / 10, HEIGHT / 10, cub, cub->keyboard);
	draw_xpm_animation(9, WIDTH / 10, HEIGHT / 8, cub, cub->keyboard);
	draw_xpm_animation(4, WIDTH / 11.5, HEIGHT / 8, cub, cub->keyboard);
	draw_xpm_animation(8, WIDTH / 8.8, HEIGHT / 8, cub, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 7.5, HEIGHT / 7.4, 0xFFFFFF, " -   Player Movement");
	draw_xpm_animation(0, WIDTH / 2.5, HEIGHT / 8, cub, cub->keyboard);
	draw_xpm_animation(1, WIDTH / 2.32, HEIGHT / 8, cub, cub->keyboard);
	draw_xpm_animation(2, WIDTH / 2.17, HEIGHT / 8, cub, cub->keyboard);
	draw_xpm_animation(3, WIDTH / 2.04, HEIGHT / 8, cub, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 1.94, HEIGHT / 7, 0xFFFFFF, " -   Change weapons");
	draw_xpm_animation(6, WIDTH / 11, HEIGHT / 3, cub, cub->keyboard);
	draw_xpm_animation(7, WIDTH / 9.2, HEIGHT / 3, cub, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 7.5, HEIGHT / 2.85, 0xFFFFFF, " -   Look right, look left");
	draw_xpm_animation(5, WIDTH / 2.2, HEIGHT / 3, cub, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 2.02, HEIGHT / 2.85, 0xFFFFFF, " -   Options menu");
	draw_xpm_animation(10, WIDTH / 2.5, HEIGHT / 1.2, cub, cub->keyboard);
	mlx_string_put(cub->con, cub->win, WIDTH / 2.2, HEIGHT / 1.175, 0xFFFFFF, " -   Close the tutorial !");
}

void	enemy_handler(t_cube *cub, t_enemy *enemy, t_txt **txt)
{
	if (enemy->hp > 0)
	{
		enemy->dist = dist((enemy->x * TILE_SIZE), (enemy->y * TILE_SIZE), cub->player.x * TILE_SIZE, cub->player.y * TILE_SIZE);
		if (enemy->dist > 500 && cub->option_bool == -1)
		{
			enemy->txt = enemy_animation_handler(txt[0], enemy->idle_max_frame);
			//printf("draw start : %d\ndraw end : %d", enemy->draw_start, enemy->draw_end);
			if (cub->player.hit == 1 && enemy->draw_start >= WIDTH / 4 && enemy->draw_end <= WIDTH / 1.4 && (cub->weapons_in_slot[cub->player.weapon - 1] == 2 || cub->weapons_in_slot[cub->player.weapon - 1] == 4) && cub->rays[WIDTH / 2].dist > enemy->dist)
			{
				cub->player.hit = 0;
				//printf("player hit !\n");
				enemy->hp -= 25;
				enemy->hurt = 1;
			}
		}
		else if (enemy->dist > enemy->attack_range && enemy->attacking_bool == 0 && cub->option_bool == -1)
		{
			//printf("draw start : %d\n", enemy->draw_start);
			enemy->txt = enemy_animation_handler(txt[1], enemy->run_max_frame);
			if (cub->player.hit == 1 && enemy->draw_start >= WIDTH / 8 && enemy->draw_end <= WIDTH / 1.1 && (cub->weapons_in_slot[cub->player.weapon - 1] == 2 || cub->weapons_in_slot[cub->player.weapon - 1] == 4) && cub->rays[WIDTH / 2].dist > enemy->dist)
			{
				cub->player.hit = 0;
				enemy->hp -= 25;
				enemy->hurt = 1;
			}
			if (cub->player.x > enemy->x && cub->map.map[(int) enemy->y][(int) (enemy->x + ENEMY_SPEED)] != '1' && can_walk(cub, (int) enemy->y, (int) (enemy->x + ENEMY_SPEED)))
				enemy->x += ENEMY_SPEED;
			else if (cub->player.x < enemy->x && cub->map.map[(int) enemy->y][(int) (enemy->x - ENEMY_SPEED)] != '1' && can_walk(cub, (int) enemy->y, (int) (enemy->x - ENEMY_SPEED)))
				enemy->x -= ENEMY_SPEED;
			if (cub->player.y > enemy->y && cub->map.map[(int) (enemy->y + ENEMY_SPEED)][(int) enemy->x] != '1' && can_walk(cub, (int) (enemy->y + ENEMY_SPEED), (int) enemy->x))
				enemy->y += ENEMY_SPEED;
			else if (cub->player.y < enemy->y && cub->map.map[(int) (enemy->y - ENEMY_SPEED)][(int) enemy->x] != '1' && can_walk(cub, (int) (enemy->y - ENEMY_SPEED), (int) enemy->x))
				enemy->y -= ENEMY_SPEED;
		}
		else
		{
			if (cub->player.hit == 1 && enemy->dist < enemy->attack_range && cub->rays[WIDTH / 2].dist > enemy->dist)
			{
				cub->player.hit = 0;
				//printf("player hit !\n");
				enemy->hp -= cub->player.atk;
				enemy->hurt = 1;
			}
			if (cub->option_bool == -1 && !enemy->hurt)
				enemy->txt = enemy_animation_atk(cub, txt[2], enemy, enemy->dist);
			if (enemy->last_attack == 1 && enemy->dist < enemy->attack_range && cub->option_bool == -1)
			{
				cub->player.hp -= 25;
				enemy->last_attack = -1;
				//enemy->last_attack = get_current_time();
			}
		}
		if (cub->option_bool == -1 && enemy->hurt)
			enemy->txt = enemy_animation_hurt(cub, txt[3], enemy, enemy->hurt_max_frame);
	}
	else if (enemy->dead == 0)
		enemy->txt = enemy_animation_death(cub, txt[4], enemy, enemy->death_max_frame);
}

int	loop_hook(t_cube *cub)
{
	void *img;
    int bits_per_pixel;
    int endian;
	char	*arrow_amount;
	char	*atk_amount;
	char	*speed_amount;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->img = img;
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);
	//printf ("Player y is %d and x is %d\n", (int)cub->player.y, (int)cub->player.x);
	if (cub->title_bool == 0 && cub->bg_bool == 0)
	{
		if (cub->player.hp > 0)
		{
			if (cub->key.w)
			{
				if ((cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))] != '1')
						&& can_walk(cub, (int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad))), (int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))))
				{
					if ((cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))] != '2') && remove_corners(cub, (int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad))), (int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))))
					{
						cub->player.y += cub->player.speed * (sin(-cub->rr.angle_rad));
						cub->player.x += cub->player.speed * (cos(-cub->rr.angle_rad));
					}
				}
				else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && can_walk(cub, (int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad)), (int) cub->player.x) && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))))
				{
					if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
						cub->player.y += cub->player.speed * (sin(-cub->rr.angle_rad));	
				}
				else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))] != '1' && can_walk(cub, (int) cub->player.y, (int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))) && is_corner(cub, (int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad)), (int) cub->player.y))
				{
					if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))] != '2')
						cub->player.x += cub->player.speed * (cos(-cub->rr.angle_rad));
				}
			}
			if (cub->key.s)
			{
				if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))] != '1' && can_walk(cub, (int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad))), (int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))) && remove_corners(cub, (int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad))), (int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))))
				{
					if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))] != '2')
					{	
						cub->player.y -= cub->player.speed * sin(-cub->rr.angle_rad);
						cub->player.x -= cub->player.speed * cos(-cub->rr.angle_rad);
					}
				}
				else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && can_walk(cub, (int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad)), (int) cub->player.x)&& is_corner(cub, (int) cub->player.x, (int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad))))
				{
						if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
							cub->player.y -= cub->player.speed * sin(-cub->rr.angle_rad);
				}
				else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))] != '1' && can_walk(cub, (int) cub->player.y, (int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))) && is_corner(cub, (int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad)), (int) cub->player.y))
				{
					if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))] != '2')
						cub->player.x -= cub->player.speed * cos(-cub->rr.angle_rad);
				}	
			}
			if (cub->key.a)
			{
				if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && can_walk(cub, (int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))) && remove_corners(cub, (int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))))
				{
					if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
					{
						cub->player.y -= cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
						cub->player.x -= cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
					}
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && can_walk(cub, (int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.x) && is_corner(cub, (int) cub->player.x, (int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
						cub->player.y -= cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && can_walk(cub, (int) cub->player.y, (int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))) && !is_corner(cub, (int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '2')
						cub->player.x -= cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
				}
			}
			if (cub->key.d)
			{
				if (cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && can_walk(cub, (int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))) && remove_corners(cub, (int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))))
				{
					if (cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
					{	
						cub->player.y += cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
						cub->player.x += cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
					}
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && can_walk(cub, (int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.x) && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
						cub->player.y += cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);	
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && can_walk(cub, (int) cub->player.y, (int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))) && is_corner(cub, (int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '2')
						cub->player.x += cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
				}
			}
			
			// draw_map_to_image(cub, cub->addr, cub->line_length);
			if (cub->start == 1)
				player_rotation_init(cub);
			if (cub->option_bool == -1)
				mouse_rotate(cub);
			if (cub->key.left && cub->option_bool == -1)
				rotate_player(cub, (cub->p_rotation));
			if (cub->key.right && cub->option_bool == -1)
				rotate_player(cub, -(cub->p_rotation));
		}
		update_dist(cub);
		check_pick_up(cub);
		// printf("weaponsss %d\n", cub->weapon_counter);
		render_game(cub);
		check_door(cub);
		// mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a sword.");
		sword_handler(cub);
		hp_handler(cub);
		crossbow_handler(cub);
		shield_handler(cub);
		weapon_slot_handler(cub);
		dragon_handler(cub);
		explosion_sprite(cub);
		draw_xpm_texture(15, WIDTH / 1.08, HEIGHT / 6, cub);
		draw_xpm_texture(16, WIDTH / 1.08, HEIGHT / 10, cub);
		draw_xpm_texture(17, WIDTH / 1.069, HEIGHT / 22, cub);
		if (cub->start == 1)
			player_rotation_init(cub);
		if (cub->option_bool == -1)
			mouse_rotate(cub);
		if (cub->key.left && cub->option_bool == -1)
			rotate_player(cub, (cub->p_rotation));
		if (cub->key.right && cub->option_bool == -1)
			rotate_player(cub, -(cub->p_rotation));
			
		// cub->casket_dist = dist((cub->casket_x * TILE_SIZE), (cub->casket_y * TILE_SIZE), cub->player.x * TILE_SIZE, cub->player.y * TILE_SIZE);
		int idx = 0;
		while (idx < cub->enemy_counter)
		{
			if (cub->all_enemies[idx].type == 'n')
				enemy_handler(cub, &cub->all_enemies[idx], cub->nightborne);
			else if (cub->all_enemies[idx].type == 'c')
				enemy_handler(cub, &cub->all_enemies[idx], cub->cute_wolf);
			else if (cub->all_enemies[idx].type == 'p')
				enemy_handler(cub, &cub->all_enemies[idx], cub->plague_doctor);
			else if (cub->all_enemies[idx].type == 'v')
				enemy_handler(cub, &cub->all_enemies[idx], cub->s_warrior);
			else if (cub->all_enemies[idx].type == 's')
				enemy_handler(cub, &cub->all_enemies[idx], cub->skeleton);
			else if (cub->all_enemies[idx].type == 'w')
				enemy_handler(cub, &cub->all_enemies[idx], cub->warrior);
			else if (cub->all_enemies[idx].type == 'k')
				enemy_handler(cub, &cub->all_enemies[idx], cub->skullwolf);
			idx++;
		}
		// enemy_handler(cub, 0, cub->nightborne);
		// enemy_handler(cub, 0, cub->nightborne);
		// enemy_handler(cub, 1, cub->skeleton);
		// enemy_handler(cub, 2, cub->warrior);
		// enemy_handler(cub, 3, cub->skullwolf);
		// enemy_handler(cub, 4, cub->s_warrior);
		// enemy_handler(cub, 5, cub->plague_doctor);
		// enemy_handler(cub, 6, cub->cute_wolf);
	}
	if (cub->title_bool == 1)
		title_handler(cub);
	if (cub->bg_bool)
	{
		bg_handler(cub);
		draw_xpm_animation(0, WIDTH /10, HEIGHT / 25, cub, cub->main_menu_assets);
		start_handler(cub);
		start_keys(cub);
		items_parsing(cub);
		// init_enemies(cub);
		cub->player.x = 2;
		cub->player.y = 13;
	}
	mlx_put_image_to_window(cub->con, cub->win, cub->img, 0, 0);
	display_messages(cub);
	if (!cub->title_bool && !cub->bg_bool)
	{
		draw_map_to_image(cub, cub->addr, cub->line_length);
		draw_player_to_image(cub, cub->addr, cub->line_length);
	}
	if (cub->title_bool == 0 && cub->bg_bool == 0)
	{
		if (cub->option_bool == 1 && cub->player.hp > 0 && !cub->tuto)
			draw_options(cub);
		else
			mlx_mouse_hide(cub->con, cub->win);
		arrow_amount = ft_strdup(" x ");
		arrow_amount = ft_strjoin_gnl(arrow_amount, ft_itoa(cub->player.arrows));
		mlx_string_put(cub->con, cub->win, WIDTH / 1.049, HEIGHT / 16, 0xFFFFFF, arrow_amount);
		atk_amount = ft_strdup(" x ");
		atk_amount = ft_strjoin_gnl(atk_amount, ft_itoa(cub->player.atk_item_amount));
		mlx_string_put(cub->con, cub->win, WIDTH / 1.049, HEIGHT / 7.5, 0xFFFFFF, atk_amount);
		speed_amount = ft_strdup(" x ");
		speed_amount = ft_strjoin_gnl(speed_amount, ft_itoa(cub->player.speed_item_amount));
		mlx_string_put(cub->con, cub->win, WIDTH / 1.049, HEIGHT / 5, 0xFFFFFF, speed_amount);
		draw_xpm_animation(19, WIDTH / 2, HEIGHT / 2, cub, cub->txt);
	}
	if (cub->player.hp <= 0 && !cub->bg_bool)
	{
		cub->fade_factor -= 0.01; // Adjust the decrement value for smoother or faster fade
		if (cub->fade_factor < 0.42)
			cub->fade_factor = 0.42;
		fade_to_black(cub, cub->fade_factor, bits_per_pixel);
		died_handler(cub);
		cub->retry = 1;
	}
	if (cub->tuto && !cub->title_bool && !cub->bg_bool)
		tutorial(cub, bits_per_pixel);
	mlx_destroy_image(cub->con, img);
	return (0);
}

// void	init_enemies(t_cube *cub)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 7)
// 	{
// 		cub->enemies[i].attacking_bool = 0;
// 		cub->enemies[i].last_attack = -1;
// 		cub->enemies[i].dead = 0;
// 		if (i == 0 || i == 2 || i == 5)
// 			cub->enemies[i].hp = 500;
// 		else
// 			cub->enemies[i].hp = 100;
// 		i++;
// 	}
// 	cub->enemies[0].x = 2;
// 	cub->enemies[0].y = 2;
// 	cub->enemies[0].scale = 0.4;
// 	cub->enemies[0].z_index = 20;
// 	cub->enemies[0].atk_max_frame = 11;
// 	cub->enemies[0].death_max_frame = 21;
// 	cub->enemies[0].hurt_max_frame = 4;
// 	cub->enemies[0].idle_max_frame = 8;
// 	cub->enemies[0].run_max_frame = 5;
// 	cub->enemies[0].attack_range = 150;
// 	cub->enemies[1].x = 8;
// 	cub->enemies[1].y = 6;
// 	cub->enemies[1].scale = 0.8;
// 	cub->enemies[1].z_index = 100;
// 	cub->enemies[1].atk_max_frame = 17;
// 	cub->enemies[1].death_max_frame = 12;
// 	cub->enemies[1].hurt_max_frame = 7;
// 	cub->enemies[1].idle_max_frame = 10;
// 	cub->enemies[1].run_max_frame = 12;
// 	cub->enemies[1].attack_range = 80;
// 	cub->enemies[2].x = 13;
// 	cub->enemies[2].y = 12;
// 	cub->enemies[2].scale = 0.4;
// 	cub->enemies[2].z_index = 70;
// 	cub->enemies[2].atk_max_frame = 6;
// 	cub->enemies[2].death_max_frame = 6;
// 	cub->enemies[2].hurt_max_frame = 2;
// 	cub->enemies[2].idle_max_frame = 9;
// 	cub->enemies[2].run_max_frame = 7;
// 	cub->enemies[2].attack_range = 80;
// 	cub->enemies[3].x = 5;
// 	cub->enemies[3].y = 12;
// 	cub->enemies[3].scale = 0.6;
// 	cub->enemies[3].z_index = 80;
// 	cub->enemies[3].atk_max_frame = 4;
// 	cub->enemies[3].death_max_frame = 6;
// 	cub->enemies[3].hurt_max_frame = 3;
// 	cub->enemies[3].idle_max_frame = 5;
// 	cub->enemies[3].run_max_frame = 4;
// 	cub->enemies[3].attack_range = 80;
// 	cub->enemies[4].x = 8;
// 	cub->enemies[4].y = 11;
// 	cub->enemies[4].scale = 0.6;
// 	cub->enemies[4].z_index = 80;
// 	cub->enemies[4].atk_max_frame = 3;
// 	cub->enemies[4].death_max_frame = 8;
// 	cub->enemies[4].hurt_max_frame = 2;
// 	cub->enemies[4].idle_max_frame = 5;
// 	cub->enemies[4].run_max_frame = 7;
// 	cub->enemies[4].attack_range = 100;
// 	cub->enemies[5].x = 7;
// 	cub->enemies[5].y = 11;
// 	cub->enemies[5].scale = 0.6;
// 	cub->enemies[5].z_index = 80;
// 	cub->enemies[5].atk_max_frame = 4;
// 	cub->enemies[5].death_max_frame = 5;
// 	cub->enemies[5].hurt_max_frame = 2;
// 	cub->enemies[5].idle_max_frame = 3;
// 	cub->enemies[5].run_max_frame = 3;
// 	cub->enemies[5].attack_range = 70;
// 	cub->enemies[6].x = 2;
// 	cub->enemies[6].y = 11;
// 	cub->enemies[6].scale = 0.6;
// 	cub->enemies[6].z_index = 80;
// 	cub->enemies[6].atk_max_frame = 4;
// 	cub->enemies[6].death_max_frame = 4;
// 	cub->enemies[6].hurt_max_frame = 2;
// 	cub->enemies[6].idle_max_frame = 3;
// 	cub->enemies[6].run_max_frame = 3;
// 	cub->enemies[6].attack_range = 70;
// }

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
	cub->player.speed = 0.006;
	cub->player.atk = 25;
	cub->player.atk_item_amount = 0;
	cub->player.speed_item_amount = 0;
	if (!cub->retry)
	{
		cub->title_bool = 0;
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
	// init_enemies(cub);
}

void	init_cute_wolf(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->cute_wolf = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->cute_wolf[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/idle/idle1.xpm");
	while (y < 4)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->cute_wolf[i][y].width, &cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
			&cub->cute_wolf[i][y].line_length, &cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->cute_wolf[i]->delay = 20;
	cub->cute_wolf[i]->current_frame = 0;
	i++;
	y = 0;
	cub->cute_wolf[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/run/run1.xpm");
	while (y < 4)
	{

		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->cute_wolf[i][y].width, &cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
			&cub->cute_wolf[i][y].line_length, &cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[i]->delay = 10;
	cub->cute_wolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->cute_wolf[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->cute_wolf[i][y].width, &cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
			&cub->cute_wolf[i][y].line_length, &cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[i]->delay = 20;
	cub->cute_wolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->cute_wolf[i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->cute_wolf[i][y].width, &cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
			&cub->cute_wolf[i][y].line_length, &cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[i]->delay = 12;
	cub->cute_wolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->cute_wolf[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/death/death1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->cute_wolf[i][y].width, &cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
			&cub->cute_wolf[i][y].line_length, &cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[i]->delay = 8;
	cub->cute_wolf[i]->current_frame = 0;
	free(num);
}

void	init_plague_doctor(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->plague_doctor = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->plague_doctor[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/idle/idle1.xpm");
	while (y < 4)
	{
		increment_numbers(num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->plague_doctor[i][y].width, &cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
			&cub->plague_doctor[i][y].line_length, &cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->plague_doctor[i]->delay = 20;
	cub->plague_doctor[i]->current_frame = 0;
	i++;
	y = 0;
	cub->plague_doctor[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/run/run1.xpm");
	while (y < 4)
	{

		increment_numbers(num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->plague_doctor[i][y].width, &cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
			&cub->plague_doctor[i][y].line_length, &cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[i]->delay = 10;
	cub->plague_doctor[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->plague_doctor[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->plague_doctor[i][y].width, &cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
			&cub->plague_doctor[i][y].line_length, &cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[i]->delay = 20;
	cub->plague_doctor[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->plague_doctor[i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->plague_doctor[i][y].width, &cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
			&cub->plague_doctor[i][y].line_length, &cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[i]->delay = 12;
	cub->plague_doctor[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->plague_doctor[i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/death/death1.xpm");
	while (y < 6)
	{
		increment_numbers(num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->plague_doctor[i][y].width, &cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
			&cub->plague_doctor[i][y].line_length, &cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[i]->delay = 8;
	cub->plague_doctor[i]->current_frame = 0;
	free(num);
}

void	init_s_warrior(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->s_warrior = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->s_warrior[i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/idle/idle1.xpm");
	while (y < 6)
	{
		increment_numbers(num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->s_warrior[i][y].width, &cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
			&cub->s_warrior[i][y].line_length, &cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->s_warrior[i]->delay = 20;
	cub->s_warrior[i]->current_frame = 0;
	i++;
	y = 0;
	cub->s_warrior[i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/run/run1.xpm");
	while (y < 8)
	{

		increment_numbers(num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->s_warrior[i][y].width, &cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
			&cub->s_warrior[i][y].line_length, &cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[i]->delay = 10;
	cub->s_warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->s_warrior[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/attack/attack1.xpm");
	while (y < 4)
	{
		increment_numbers(num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->s_warrior[i][y].width, &cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
			&cub->s_warrior[i][y].line_length, &cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[i]->delay = 20;
	cub->s_warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->s_warrior[i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->s_warrior[i][y].width, &cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
			&cub->s_warrior[i][y].line_length, &cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[i]->delay = 12;
	cub->s_warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->s_warrior[i] = (t_txt *)malloc(9 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/death/death1.xpm");
	while (y < 9)
	{
		increment_numbers(num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->s_warrior[i][y].width, &cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
			&cub->s_warrior[i][y].line_length, &cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[i]->delay = 8;
	cub->s_warrior[i]->current_frame = 0;
	free(num);
}

void	init_skullwolf(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->skullwolf = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->skullwolf[i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/idle/idle1.xpm");
	while (y < 6)
	{
		increment_numbers(num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skullwolf[i][y].width, &cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
			&cub->skullwolf[i][y].line_length, &cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->skullwolf[i]->delay = 8;
	cub->skullwolf[i]->current_frame = 0;
	i++;
	y = 0;
	cub->skullwolf[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/run/run1.xpm");
	while (y < 5)
	{

		increment_numbers(num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skullwolf[i][y].width, &cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
			&cub->skullwolf[i][y].line_length, &cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[i]->delay = 10;
	cub->skullwolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skullwolf[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skullwolf[i][y].width, &cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
			&cub->skullwolf[i][y].line_length, &cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[i]->delay = 10;
	cub->skullwolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skullwolf[i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/hurt/hurt1.xpm");
	while (y < 4)
	{
		increment_numbers(num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skullwolf[i][y].width, &cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
			&cub->skullwolf[i][y].line_length, &cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[i]->delay = 12;
	cub->skullwolf[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skullwolf[i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/death/death1.xpm");
	while (y < 7)
	{
		increment_numbers(num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skullwolf[i][y].width, &cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
			&cub->skullwolf[i][y].line_length, &cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[i]->delay = 8;
	cub->skullwolf[i]->current_frame = 0;
	free(num);
}

void	init_warrior(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->warrior = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->warrior[i] = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/idle/idle1.xpm");
	while (y < 10)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/warrior/idle/idle10.xpm"));
		else
			increment_numbers(num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->warrior[i][y].width, &cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior[i][y].img, &cub->warrior[i][y].bits_per_pixel,
			&cub->warrior[i][y].line_length, &cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->warrior[i]->delay = 8;
	cub->warrior[i]->current_frame = 0;
	i++;
	y = 0;
	cub->warrior[i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/run/run1.xpm");
	while (y < 8)
	{

		increment_numbers(num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->warrior[i][y].width, &cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior[i][y].img, &cub->warrior[i][y].bits_per_pixel,
			&cub->warrior[i][y].line_length, &cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[i]->delay = 10;
	cub->warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->warrior[i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/attack/attack1.xpm");
	while (y < 7)
	{
		increment_numbers(num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->warrior[i][y].width, &cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior[i][y].img, &cub->warrior[i][y].bits_per_pixel,
			&cub->warrior[i][y].line_length, &cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[i]->delay = 14;
	cub->warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->warrior[i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->warrior[i][y].width, &cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior[i][y].img, &cub->warrior[i][y].bits_per_pixel,
			&cub->warrior[i][y].line_length, &cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[i]->delay = 12;
	cub->warrior[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->warrior[i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/death/death1.xpm");
	while (y < 7)
	{
		increment_numbers(num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->warrior[i][y].width, &cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior[i][y].img, &cub->warrior[i][y].bits_per_pixel,
			&cub->warrior[i][y].line_length, &cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[i]->delay = 8;
	cub->warrior[i]->current_frame = 0;
	free(num);
}

void	init_skeleton(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->skeleton = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->skeleton[i] = (t_txt *)malloc(11 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/idle/idle1.xpm");
	while (y < 11)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/skeleton/idle/idle10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skeleton[i][y].width, &cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
			&cub->skeleton[i][y].line_length, &cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->skeleton[i]->delay = 8;
	cub->skeleton[i]->current_frame = 0;
	i++;
	y = 0;
	cub->skeleton[i] = (t_txt *)malloc(13 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/run/run1.xpm");
	while (y < 13)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/skeleton/run/run10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skeleton[i][y].width, &cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
			&cub->skeleton[i][y].line_length, &cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[i]->delay = 2;
	cub->skeleton[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skeleton[i] = (t_txt *)malloc(18 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/attack/attack1.xpm");
	while (y < 18)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/skeleton/attack/attack10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skeleton[i][y].width, &cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
			&cub->skeleton[i][y].line_length, &cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[i]->delay = 8;
	cub->skeleton[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skeleton[i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/hurt/hurt1.xpm");
	while (y < 8)
	{
		increment_numbers(num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skeleton[i][y].width, &cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
			&cub->skeleton[i][y].line_length, &cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[i]->delay = 8;
	cub->skeleton[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->skeleton[i] = (t_txt *)malloc(13 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/death/death1.xpm");
	while (y < 13)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/skeleton/death/death10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->skeleton[i][y].width, &cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
			&cub->skeleton[i][y].line_length, &cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[i]->delay = 8;
	cub->skeleton[i]->current_frame = 0;
	free(num);
}

void	init_alphabet(t_cube *cub)
{
	int		i;
	int		x;
	int		y;
	char	*num;

	i = 0;
	cub->abc = (t_txt *)malloc(26 * sizeof(t_txt));
	num = ft_strdup("./textures/alphabet/A.xpm");
	while (i < 26)
	{
		cub->abc[i].img = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->abc[i].addr = mlx_get_data_addr(cub->abc[i].img, &cub->abc[i].bits_per_pixel,
			&cub->abc[i].line_length, &cub->abc[i].endian);
		cub->abc[i].width = 22;
		cub->abc[i].height = 34;
		i++;
		increment_alphabet(num, i);
	}
	free(num);
}

void	init_textures(t_cube *cub)
{
	cub->txt[4].type = NULL;
	cub->txt[4].path = ft_strdup("./textures/options_menu_resized.xpm");
	cub->txt[5].type = NULL;
	cub->txt[5].path = ft_strdup("./textures/arrow_right.xpm");
	cub->txt[6].type = NULL;
	cub->txt[6].path = ft_strdup("./textures/arrow_left.xpm");
	cub->txt[7].type = NULL;
	cub->txt[7].path = ft_strdup("./textures/weapon_slot.xpm");
	cub->txt[8].type = NULL;
	cub->txt[8].path = ft_strdup("./textures/weapon_slot_white.xpm");
	cub->txt[9].type = NULL;
	cub->txt[9].path = ft_strdup("./textures/sword_weapon_slot.xpm");
	cub->txt[10].type = ft_strdup("D");
	cub->txt[10].path = ft_strdup("./textures/sword_weapon_slot.xpm");
	cub->txt[11].type = NULL;
	cub->txt[11].path = ft_strdup("textures/crossbow_weapon_slot.xpm");
	cub->txt[12].type = NULL;
	cub->txt[12].path = ft_strdup("textures/shield.xpm");
	cub->txt[13].type = NULL;
	cub->txt[13].path = ft_strdup("textures/shield_weapon_slot.xpm");
	cub->txt[14].type = NULL;
	cub->txt[14].path = ft_strdup("textures/fire_weapon_slot.xpm");
	cub->txt[15].type = NULL;
	cub->txt[15].path = ft_strdup("textures/speed_item_hud.xpm");
	cub->txt[16].type = NULL;
	cub->txt[16].path = ft_strdup("textures/attack_item_hud.xpm");
	cub->txt[17].type = NULL;
	cub->txt[17].path = ft_strdup("textures/arrow_item_hud.xpm");
	cub->txt[18].type = NULL;
	cub->txt[18].path = ft_strdup("textures/Casket.xpm");
	cub->txt[19].type = NULL;
	cub->txt[19].path = ft_strdup("textures/crosshair.xpm");
	cub->txt[20].type = NULL;
	cub->txt[20].path = ft_strdup("textures/rat.xpm");
	cub->txt[21].type = NULL;
	cub->txt[21].path = ft_strdup("textures/rat_left.xpm");
	cub->txt[22].type = NULL;
	cub->txt[22].path = ft_strdup("textures/health_potion.xpm");
}

void	init_nightborne(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->nightborne = (t_txt **)malloc(5 * sizeof(t_txt *));
	i = 0;
	y = 0;
	cub->nightborne[i] = (t_txt *)malloc(9 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/idle/idle1.xpm");
	while (y < 9)
	{

		increment_numbers(num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->nightborne[i][y].width, &cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length, &cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	i++;
	y = 0;
	cub->nightborne[i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/run/run1.xpm");
	while (y < 6)
	{

		increment_numbers(num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->nightborne[i][y].width, &cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length, &cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->nightborne[i] = (t_txt *)malloc(12 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/attack/attack1.xpm");
	while (y < 12)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/Nightborne/attack/attack10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->nightborne[i][y].width, &cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length, &cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->nightborne[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/hurt/hurt1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->nightborne[i][y].width, &cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length, &cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	free(num);
	i++;
	y = 0;
	cub->nightborne[i] = (t_txt *)malloc(22 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/death/death1.xpm");
	while (y < 22)
	{
		if (y == 9)
			(free(num), num = ft_strdup("./textures/Enemies/Nightborne/death/death10.xpm"));
		else if (y == 19)
			(free(num), num = ft_strdup("./textures/Enemies/Nightborne/death/death20.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else if (y >= 20 && y < 29)
			increment_numbers_2(num, y - 20 + 1);
		else
			increment_numbers(num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image(cub->con, num, &cub->nightborne[i][y].width, &cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length, &cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	free(num);
}

void	init_keyboard(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->keyboard = (t_txt *)malloc(12 * sizeof(t_txt));
	num = ft_strdup("./textures/keyboard_assets/1.xpm");
	while (i < 12)
	{
		if (i == 9)
			(free(num), num = ft_strdup("./textures/keyboard_assets/10.xpm"));
		else if (i >= 10 && i < 19)
			increment_numbers_2(num, i - 10 + 1);
		else
			increment_numbers(num, i + 1);
		cub->keyboard[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->keyboard[i].width, &cub->keyboard[i].height);
		cub->keyboard[i].addr = mlx_get_data_addr(cub->keyboard[i].img, &cub->keyboard[i].bits_per_pixel,
			&cub->keyboard[i].line_length, &cub->keyboard[i].endian);
		cub->keyboard[i].tmp_delay = 0;
		i++;
	}
	free(num);
}

void	init_game_over(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->game_over = (t_txt *)malloc(11 * sizeof(t_txt));
	num = ft_strdup("./textures/game_over/died1.xpm");
	while (i < 11)
	{
		if (i == 9)
			(free(num), num = ft_strdup("./textures/game_over/died10.xpm"));
		else if (i >= 10 && i < 19)
			increment_numbers_2(num, i - 10 + 1);
		else
			increment_numbers(num, i + 1);
		cub->game_over[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->game_over[i].width, &cub->game_over[i].height);
		cub->game_over[i].addr = mlx_get_data_addr(cub->game_over[i].img, &cub->game_over[i].bits_per_pixel,
			&cub->game_over[i].line_length, &cub->game_over[i].endian);
		cub->game_over[i].tmp_delay = 0;
		i++;
	}
	cub->game_over->delay = 20;
	cub->game_over->current_frame = 0;
	free(num);
}

void	init_main_menu_start(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->main_menu_start = (t_txt *)malloc(19 * sizeof(t_txt));
	num = ft_strdup("./textures/main_menu/start/start1.xpm");
	while (i < 19)
	{
		if (i == 9)
			(free(num), num = ft_strdup("./textures/main_menu/start/start10.xpm"));
		else if (i >= 10 && i < 19)
			increment_numbers_2(num, i - 10 + 1);
		else
			increment_numbers(num, i + 1);
		cub->main_menu_start[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->main_menu_start[i].width, &cub->main_menu_start[i].height);
		cub->main_menu_start[i].addr = mlx_get_data_addr(cub->main_menu_start[i].img, &cub->main_menu_start[i].bits_per_pixel,
			&cub->main_menu_start[i].line_length, &cub->main_menu_start[i].endian);
		cub->main_menu_start[i].tmp_delay = 0;
		i++;
	}
	cub->main_menu_start->delay = 10;
	cub->main_menu_start->current_frame = 0;
	free(num);
}

void	init_main_menu_bg(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->main_menu_bg = (t_txt *)malloc(24 * sizeof(t_txt));
	num = ft_strdup("./textures/main_menu/bg1.xpm");
	while (i < 24)
	{
		if (i == 9)
			(free(num), num = ft_strdup("./textures/main_menu/bg10.xpm"));
		else if (i == 19)
			(free(num), num = ft_strdup("./textures/main_menu/bg20.xpm"));
		else if (i >= 10 && i < 19)
			increment_numbers_2(num, i - 10 + 1);
		else if (i >= 20 && i < 29)
			increment_numbers_2(num, i - 20 + 1);
		else
			increment_numbers(num, i + 1);
		cub->main_menu_bg[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->main_menu_bg[i].width, &cub->main_menu_bg[i].height);
		cub->main_menu_bg[i].addr = mlx_get_data_addr(cub->main_menu_bg[i].img, &cub->main_menu_bg[i].bits_per_pixel,
			&cub->main_menu_bg[i].line_length, &cub->main_menu_bg[i].endian);
		cub->main_menu_bg[i].tmp_delay = 0;
		i++;
	}
	cub->main_menu_bg->delay = 20;
	cub->main_menu_bg->current_frame = 0;
	free(num);
}

void	init_title(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->title_screen = (t_txt *)malloc(29 * sizeof(t_txt));
	num = ft_strdup("./textures/title_screen/title1.xpm");
	while (i < 29)
	{
		if (i == 9)
			(free(num), num = ft_strdup("./textures/title_screen/title10.xpm"));
		else if (i == 19)
			(free(num), num = ft_strdup("./textures/title_screen/title20.xpm"));
		else if (i >= 10 && i < 19)
			increment_numbers_2(num, i - 10 + 1);
		else if (i >= 20)
			increment_numbers_2(num, i - 20 + 1);
		else
			increment_numbers(num, i + 1);
		cub->title_screen[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->title_screen[i].width, &cub->title_screen[i].height);
		cub->title_screen[i].addr = mlx_get_data_addr(cub->title_screen[i].img, &cub->title_screen[i].bits_per_pixel,
			&cub->title_screen[i].line_length, &cub->title_screen[i].endian);
		cub->title_screen[i].tmp_delay = 0;
		i++;
	}
	cub->title_screen->delay = 70;
	cub->title_screen->current_frame = 0;
	free(num);
}

void	init_explosion(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->explosion = (t_txt *)malloc(14 * sizeof(t_txt));
	num = ft_strdup("./textures/explosion_animation/explosion1.xpm");
	while (i < 14)
	{
		if (i == 9)
		{
			free(num);
			num = ft_strdup("./textures/explosion_animation/explosion10.xpm");
		}
		else if (i >= 10)
			increment_numbers_2(num, i / 10 + 1);
		else
			increment_numbers(num, i + 1);
		cub->explosion[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->explosion[i].width, &cub->explosion[i].height);
		cub->explosion[i].addr = mlx_get_data_addr(cub->explosion[i].img, &cub->explosion[i].bits_per_pixel,
			&cub->explosion[i].line_length, &cub->explosion[i].endian);
		cub->explosion[i].tmp_delay = 0;
		i++;
	}
	cub->explosion->delay = 7;
	cub->explosion->current_frame = 0;
	free(num);
}

void	init_dragon(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->dragon = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/dragon_animation/dragon1.xpm");
	while (i < 5)
	{
		increment_numbers(num, i + 1);
		cub->dragon[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->dragon[i].width, &cub->dragon[i].height);
		cub->dragon[i].addr = mlx_get_data_addr(cub->dragon[i].img, &cub->dragon[i].bits_per_pixel,
			&cub->dragon[i].line_length, &cub->dragon[i].endian);
		cub->dragon[i].tmp_delay = 0;
		i++;
	}
	cub->dragon->delay = 15;
	cub->dragon->current_frame = 0;
	free(num);
}

void	init_crossbow(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->crossbow = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/crossbow_animation/crossbow1.xpm");
	while (i < 6)
	{
		increment_numbers(num, i + 1);
		cub->crossbow[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->crossbow[i].width, &cub->crossbow[i].height);
		cub->crossbow[i].addr = mlx_get_data_addr(cub->crossbow[i].img, &cub->crossbow[i].bits_per_pixel,
			&cub->crossbow[i].line_length, &cub->crossbow[i].endian);
		cub->crossbow[i].tmp_delay = 0;
		i++;
	}
	cub->crossbow->delay = 18;
	cub->crossbow->current_frame = 0;
	free(num);
}

void	init_hp(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_strdup("./textures/hp/hp1.xpm");
	cub->hp_frame = (t_txt *)malloc(8 * sizeof(t_txt));
	while (i < 8)
	{
		increment_numbers(num, i + 1);
		cub->hp_frame[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->hp_frame[i].width, &cub->hp_frame[i].height);
		cub->hp_frame[i].addr = mlx_get_data_addr(cub->hp_frame[i].img, &cub->hp_frame[i].bits_per_pixel,
			&cub->hp_frame[i].line_length, &cub->hp_frame[i].endian);
		cub->hp_frame[i].tmp_delay = 0;
		i++;
	}
	cub->hp_frame->delay = 6;
	cub->hp_frame->current_frame = 1;
	free(num);
}

void	init_sword(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->sword_ani = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/sword_animation/sword1.xpm");
	while (i < 5)
	{
		increment_numbers(num, i + 1);
		cub->sword_ani[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->sword_ani[i].width, &cub->sword_ani[i].height);
		cub->sword_ani[i].addr = mlx_get_data_addr(cub->sword_ani[i].img, &cub->sword_ani[i].bits_per_pixel,
			&cub->sword_ani[i].line_length, &cub->sword_ani[i].endian);
		cub->sword_ani[i].tmp_delay = 0;
		i++;
	}
	cub->sword_ani->current_frame = 0;
	cub->sword_ani->delay = 10;
	free(num);
}

void	init_numbers(t_cube *cub)
{
	int		i;
	int		x;
	int		y;
	char	*num;

	i = 0;
	cub->nums = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/numbers/0.xpm");
	while (i < 10)
	{
		cub->nums[i].img = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->nums[i].addr = mlx_get_data_addr(cub->nums[i].img, &cub->nums[i].bits_per_pixel,
			&cub->nums[i].line_length, &cub->nums[i].endian);
		cub->nums[i].width = 22;
		cub->nums[i].height = 34;
		i++;
		increment_numbers(num, i);
	}
	free(num);
}

void	init_door(t_cube *cub)
{
	int		i;
	char 	*num;

	cub->door = (t_txt *)malloc(7 * sizeof(t_txt));
	i = 0;
	num = ft_strdup("./textures/door/Door1.xpm");
	while (i < 7)
	{
		increment_numbers(num, i + 1);
		cub->door[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->door[i].width, &cub->door[i].height);
		cub->door[i].addr = mlx_get_data_addr(cub->door[i].img, &cub->door[i].bits_per_pixel,
			&cub->door[i].line_length, &cub->door[i].endian);
		cub->door[i].tmp_delay = 0;
		cub->door[i].delay = 7;
		i++;
	}
	free(num);
}

void window_init(t_cube *cub)
{

	cub->con = mlx_init();
	if (cub->con == NULL)
		(printf("Error\nCouldn't start minilibx.\n"), exit_free(cub));
	cub->win = mlx_new_window(cub->con, WIDTH, HEIGHT, "cub3d");
	if (cub->win == NULL)
	{
		mlx_destroy_display(cub->con);
		free(cub->con);
		printf("Error\nCouldn't open the window.\n");
		exit_free(cub);
	}
	init_alphabet(cub);
	init_numbers(cub);
	init_sword(cub);
	init_hp(cub);
	init_crossbow(cub);
	init_dragon(cub);
	init_explosion(cub);
	init_title(cub);
	init_main_menu_bg(cub);
	init_main_menu_start(cub);
	init_game_over(cub);
	init_keyboard(cub);
	init_nightborne(cub);
	init_skeleton(cub);
	init_warrior(cub);
	init_skullwolf(cub);
	init_s_warrior(cub);
	init_plague_doctor(cub);
	init_cute_wolf(cub);
	init_door(cub);
	save_doors(cub);
	cub->main_menu_assets = (t_txt *)malloc(1 * sizeof(t_txt));
	cub->main_menu_assets[0].type = NULL;
	cub->main_menu_assets[0].path = ft_strdup("./textures/main_menu/title_main_menu.xpm");
	load_textures(cub, cub->main_menu_assets, 1);
	init_textures(cub);
	items_parsing(cub);
	mlx_mouse_hide(cub->con, cub->win);
	load_textures(cub, cub->txt, 23);
	start_keys(cub);
	mlx_key_hook(cub->win, handle_key_release, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, handle_key_press, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, handle_key_release, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
			 close_x, cub);
	mlx_hook(cub->win, ButtonPress, ButtonPressMask, mouse_events, 0);
	mlx_loop_hook(cub->con, loop_hook, cub);
	mlx_loop(cub->con);
}

void	player_rotation_init(t_cube *cub)
{
	cub->start = 0;
	if (cub->player.dir == 0)
		cub->rr.angle_rad = M_PI / 2;
	else if (cub->player.dir == 1)
		cub->rr.angle_rad = 0;
	else if (cub->player.dir == 2)
		cub->rr.angle_rad = (3 * M_PI) / 2;
	else if (cub->player.dir == 3)
		cub->rr.angle_rad = M_PI;
}

void	rotate_player(t_cube *cub, double dir)
{

	cub->rr.angle_rad += dir;
	if (cub->rr.angle_rad < 0)
		cub->rr.angle_rad += 2 * M_PI;
	else if (cub->rr.angle_rad > 2 * M_PI)
		cub->rr.angle_rad -= 2 * M_PI;
}