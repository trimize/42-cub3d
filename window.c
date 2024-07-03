/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/03 19:14:56 by trimize          ###   ########.fr       */
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
	else if (key == 119 && cub->option_bool == -1)
		cub->key.w = 1;
	else if (key == 115 && cub->option_bool == -1)
		cub->key.s = 1;
	else if (key == 97 && cub->option_bool == -1)
		cub->key.a = 1;
	else if (key == 100 && cub->option_bool == -1)
		cub->key.d = 1;
	else if (key == 65361)
		cub->key.left = 1;
	else if (key == 65363)
		cub->key.right = 1;
	else if (key == 65513 && !cub->tuto)
		cub->option_bool = -cub->option_bool;
	else if (key == 65289)
	{
		if (!cub->bg_bool && !cub->title_bool && cub->tuto)
			cub->tuto = 0;
		cub->player.hp -= 25;
	}
	else if (key == 49 && cub->player.hp > 0)
		cub->player.weapon = 1;
	else if (key == 50 && cub->player.hp > 0)
		cub->player.weapon = 2;
	else if (key == 51 && cub->player.hp > 0)
		cub->player.weapon = 3;
	else if (key == 52 && cub->player.hp > 0)
		cub->player.weapon = 4;
	else if (key == 101)
		cub->map.map[7][8] = 'd';
	else if (key == 65293)
		cub->enter_pressed = 1;
	return (0);
}

int	handle_key_release(int key, t_cube *cub)
{
	if (key == 119)
		cub->key.w = 0;
	else if (key == 115)
		cub->key.s = 0;
	else if (key == 97)
		cub->key.a = 0;
	else if (key == 100)
		cub->key.d = 0;
	else if (key == 65361)
		cub->key.left = 0;
	else if (key == 65363)
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

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
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
    x = cub->player.x * TILE_SIZE;
    y = cub->player.y * TILE_SIZE;

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
				color = 0xFFFFFF;  // White
			else if (cub->map.map[y][x] == ' ')
				color = 0x000000;
			else
				color = 0x4DB8FF;  // Green

			draw_square_to_image(addr, line_length, x * TILE_SIZE, y * TILE_SIZE, color);
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
	if (cub->mouse_x >= WIDTH - (WIDTH / 10) || cub->mouse_x <= WIDTH / 10)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (cub->mouse_y >= HEIGHT - (HEIGHT / 10) || cub->mouse_x <= HEIGHT / 10)
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

int	loop_hook(t_cube *cub)
{
	void *img;
	int bits_per_pixel;
	int endian;
	char	*arrow_amount;
	char	*atk_amount;
	char	*speed_amount;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);
	//printf ("Player y is %d and x is %d\n", (int)cub->player.y, (int)cub->player.x);
	if (cub->title_bool == 0 && cub->bg_bool == 0)
	{
		if (cub->player.hp > 0)
		{
			if (cub->key.w)
			{
				if ((cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))] != '1')
						&& (cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))] != 'D'))
				{
					if ((cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad)))] != '2') && remove_corners(cub, (int) (cub->player.x + (cub->player.speed * cos(-cub->rr.angle_rad))), (int) (cub->player.y + (cub->player.speed * sin(-cub->rr.angle_rad)))))
					{
						cub->player.y += cub->player.speed * (sin(-cub->rr.angle_rad));
						cub->player.x += cub->player.speed * (cos(-cub->rr.angle_rad));
					}
				}
				else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != 'D' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))))
				{
					if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
						cub->player.y += cub->player.speed * (sin(-cub->rr.angle_rad));	
				}
				else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))] != '1' && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))] != 'D' && is_corner(cub, (int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad)), (int) cub->player.y))
				{
					if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(-cub->rr.angle_rad))] != '2')
						cub->player.x += cub->player.speed * (cos(-cub->rr.angle_rad));
				}
			}
			if (cub->key.s)
			{
				if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))] != '1' && cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))] != 'D' && remove_corners(cub, (int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad))), (int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))))
				{
					if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad)))] != '2')
					{	
						cub->player.y -= cub->player.speed * sin(-cub->rr.angle_rad);
						cub->player.x -= cub->player.speed * cos(-cub->rr.angle_rad);
					}
				}
				else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != 'D' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y - cub->player.speed * sin(-cub->rr.angle_rad))))
				{
						if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
							cub->player.y -= cub->player.speed * sin(-cub->rr.angle_rad);
				}
				else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))] != '1' && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))] != 'D' && is_corner(cub, (int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad)), (int) cub->player.y))
				{
					if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad))] != '2')
						cub->player.x -= cub->player.speed * cos(-cub->rr.angle_rad);
				}	
			}
			if (cub->key.a)
			{
				if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != 'D' && remove_corners(cub, (int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))))
				{
					if (cub->map.map[(int) (cub->player.y - (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
					{
						cub->player.y -= cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
						cub->player.x -= cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
					}
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != 'D' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
						cub->player.y -= cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != 'D' && !is_corner(cub, (int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '2')
						cub->player.x -= cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
				}
			}
			if (cub->key.d)
			{
				if (cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != 'D' && remove_corners(cub, (int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))))
				{
					if (cub->map.map[(int) (cub->player.y + (cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
					{	
						cub->player.y += cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);
						cub->player.x += cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2);
					}
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != 'D' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))))
				{
					if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
						cub->player.y += cub->player.speed * sin(- cub->rr.angle_rad + M_PI / 2);	
				}
				else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && cub->map.map[(int) cub->player.y][(int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2))] != 'D' && is_corner(cub, (int) (cub->player.x + cub->player.speed * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
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
		cast_ray(cub);
		sword_handler(cub);
		hp_handler(cub);
		crossbow_handler(cub);
		shield_handler(cub);
		weapon_slot_handler(cub);
		dragon_handler(cub);
		explosion_handler(cub);
		draw_xpm_texture(15, WIDTH / 1.08, HEIGHT / 6, cub);
		draw_xpm_texture(16, WIDTH / 1.08, HEIGHT / 10, cub);
		draw_xpm_texture(17, WIDTH / 1.069, HEIGHT / 22, cub);
	}
	if (cub->title_bool == 1)
		title_handler(cub);
	if (cub->bg_bool)
	{
		bg_handler(cub);
		cub->player.hp = 100;
		draw_xpm_animation(0, WIDTH /10, HEIGHT / 25, cub, cub->main_menu_assets);
		start_handler(cub);
		if (cub->enter_pressed)
			cub->bg_bool = 0;
	}
	if (!cub->bg_bool && !cub->title_bool)
	{
		//draw_player_to_image(cub, cub->addr, cub->line_length);
		//draw_map_to_image(cub, cub->addr, cub->line_length);
	}
	mlx_put_image_to_window(cub->con, cub->win, img, 0, 0);
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
	}
	if (cub->player.hp <= 0 && !cub->bg_bool)
	{
		cub->fade_factor -= 0.01; // Adjust the decrement value for smoother or faster fade
		if (cub->fade_factor < 0.42)
			cub->fade_factor = 0.42;
		fade_to_black(cub, cub->fade_factor, bits_per_pixel);
		died_handler(cub);
	}
	if (cub->tuto && !cub->title_bool && !cub->bg_bool)
		tutorial(cub, bits_per_pixel);
	mlx_destroy_image(cub->con, img);
	return (0);
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
	cub->current_frame_num_sword = 0;
	cub->current_frame_num_cbow = 0;
	cub->current_frame_num_dra = 0;
	cub->current_frame_num_explo = 0;
	cub->current_frame_num_title = 0;
	cub->current_frame_num_bg = 0;
	cub->current_frame_num_start = 0;
	cub->current_frame_num_died = 0;
	cub->sword_delay = 10;
	cub->dra_delay = 15;
	cub->cbow_delay = 18;
	cub->player.hp = 100;
	cub->hp_delay = 6;
	cub->explo_delay = 7;
	cub->title_delay = 70;
	cub->died_delay = 20;
	cub->bg_delay = 20;
	cub->start_delay = 10;
	cub->current_frame_num_hp = 1;
	cub->player.weapon = 1;
	init_w_slots(cub);
	cub->player.arrows = 5;
	cub->player.speed = 0.006;
	cub->player.atk = 10;
	cub->player.atk_item_amount = 0;
	cub->player.speed_item_amount = 0;
	cub->title_bool = 1;
	cub->bg_bool = 0;
	cub->enter_pressed = 0;
	cub->fade_factor = 1.0;
	cub->tuto = 1;
}

void window_init(t_cube *cub)
{
	char *alpha;
	char *num;
	int i;
	int x;
	int y;

	alpha = ft_strdup("./textures/alphabet/A.xpm");
	num = ft_strdup("./textures/numbers/0.xpm");
	cub->con = mlx_init();
	if (cub->con == NULL)
		(printf("Error\nCouldn't start minilibx.\n"), exit_free(cub));
	cub->win = mlx_new_window(cub->con, WIDTH, HEIGHT, "CATACOMBS");
	if (cub->win == NULL)
	{
		mlx_destroy_display(cub->con);
		free(cub->con);
		printf("Error\nCouldn't open the window.\n");
		exit_free(cub);
	}
	i = 0;
	cub->abc = (t_txt *)malloc(26 * sizeof(t_txt));
	while (i < 26)
	{
		cub->alphabet[i] = mlx_xpm_file_to_image(cub->con, alpha, &x, &y);
		cub->abc[i].addr = mlx_get_data_addr(cub->alphabet[i], &cub->abc[i].bits_per_pixel,
			&cub->abc[i].line_length, &cub->abc[i].endian);
		cub->abc[i].width = 22;
		cub->abc[i].height = 34;
		i++;
		increment_alphabet(alpha, i);
	}
	i = 0;
	cub->nums = (t_txt *)malloc(10 * sizeof(t_txt));
	while (i < 10)
	{
		cub->numbers[i] = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->nums[i].addr = mlx_get_data_addr(cub->numbers[i], &cub->nums[i].bits_per_pixel,
			&cub->nums[i].line_length, &cub->nums[i].endian);
		cub->nums[i].width = 22;
		cub->nums[i].height = 34;
		i++;
		increment_numbers(num, i);
	}
	i = 0;
	free(num);
	cub->sword_ani = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/sword_animation/sword1.xpm");
	while (i < 5)
	{
		increment_numbers(num, i + 1);
		cub->s_ani[i] = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->sword_ani[i].addr = mlx_get_data_addr(cub->s_ani[i], &cub->sword_ani[i].bits_per_pixel,
			&cub->sword_ani[i].line_length, &cub->sword_ani[i].endian);
		cub->sword_ani[i].width = 637;
		cub->sword_ani[i].height = 595;
		cub->sword_ani[i].tmp_delay = 0;
		i++;
	}
	i = 0;
	free(num);
	num = ft_strdup("./textures/hp/hp1.xpm");
	cub->hp_frame = (t_txt *)malloc(8 * sizeof(t_txt));
	while (i < 8)
	{
		increment_numbers(num, i + 1);
		cub->p_hp[i] = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->hp_frame[i].addr = mlx_get_data_addr(cub->p_hp[i], &cub->hp_frame[i].bits_per_pixel,
			&cub->hp_frame[i].line_length, &cub->hp_frame[i].endian);
		cub->hp_frame[i].width = 160;
		cub->hp_frame[i].height = 48;
		cub->hp_frame[i].tmp_delay = 0;
		i++;
	}
	free(num);
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
	free(num);
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
	free(num);
	i = 0;
	cub->explosion = (t_txt *)malloc(13 * sizeof(t_txt));
	num = ft_strdup("./textures/explosion_animation/explosion1.xpm");
	while (i < 13)
	{
		if (i == 9)
		{
			free(num);
			num = ft_strdup("./textures/explosion_animation/explosion10.xpm");
		}
		else if (i >= 10)
			increment_numbers_2(num, i - 10 + 1);
		else
			increment_numbers(num, i + 1);
		cub->explosion[i].img = mlx_xpm_file_to_image(cub->con, num, &cub->explosion[i].width, &cub->explosion[i].height);
		cub->explosion[i].addr = mlx_get_data_addr(cub->explosion[i].img, &cub->explosion[i].bits_per_pixel,
			&cub->explosion[i].line_length, &cub->explosion[i].endian);
		cub->explosion[i].tmp_delay = 0;
		i++;
	}
	free(num);
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
	free(num);
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
	free(num);
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
	free(num);
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
	free(num);
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
	cub->main_menu_assets = (t_txt *)malloc(1 * sizeof(t_txt));
	cub->main_menu_assets[0].type = NULL;
	cub->main_menu_assets[0].path = ft_strdup("./textures/main_menu/title_main_menu.xpm");
	load_textures(cub, cub->main_menu_assets, 1);
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
	cub->txt[10].path = ft_strdup("textures/Door.xpm");
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
	mlx_mouse_hide(cub->con, cub->win);
	load_textures(cub, cub->txt, 18);
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