/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/15 15:50:30 by mbrandao         ###   ########.fr       */
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

void	draw_dot(t_cube *cub, double x, double y, int color)
{
	int	i;
	int	j;
	int	size;

	size = PLAYER_SIZE;
	i = x - size / 2;
	while (i <= x + size / 2)
	{
		j = y - size / 2;
		while (j <= y + size / 2)
			mlx_pixel_put(cub->con, cub->win, i, j++, color);
		i++;
	}
}

void	draw_dot_map(t_cube *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = TILE_SIZE;
	i = x - size / 2;
	while (i <= x + size / 2)
	{
		j = y - size / 2;
		while (j <= y + size / 2)
			mlx_pixel_put(cub->con, cub->win, i, j++, color);
		i++;
	}
}

void	draw_player(t_cube *cub)
{
	int	color;

	color = 0xFFFFFF; // White color, you can choose any color you prefer

	// printf("\n PLAYER X IS %d AND PLAYER Y IS %d\n", x, y);
	draw_dot(cub, (cub->player.x * TILE_SIZE) + 200, (cub->player.y * TILE_SIZE) + 200, color);
}

void	draw_map(t_cube *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.map[i])
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == '1')
				draw_dot_map(cub, (j * TILE_SIZE) + 200, (i * TILE_SIZE) + 200, 0x0000FF);
			j++;
		}
		i++;
	}
}

// Key codes
// W -> 119
// A -> 97
// S -> 115
// D -> 100
// Left arrow -> 65361
// Right arrow -> 65363
// Esc -> 65307 or XK_Escape
int	handle_key_press(int key, t_cube *cub)
{
	if (key == XK_Escape)
	{
		printf("You pressed ESC and closed the game\n");
		close_x(cub);
		exit(1);
	}
	else if (key == 119)
		cub->key.w = 1;
	else if (key == 115)
		cub->key.s = 1;
	else if (key == 97)
		cub->key.a = 1;
	else if (key == 100)
		cub->key.d = 1;
	else if (key == 65361)
		cub->key.left = 1;
	else if (key == 65363)
		cub->key.right = 1;
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
			else
				color = 0x000000;  // Black

			draw_square_to_image(addr, line_length, x * TILE_SIZE, y * TILE_SIZE, color);
		}
	}
}

void	print_rot_ray(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		draw_p_to_image(cub->addr, cub->line_length, (cub->rr.ray_x[i]),
			(cub->rr.ray_y[i]), DARK_GREEN);
		i++;
	}
}

int	loop_hook(t_cube *cub)
{
	void *img;
    int bits_per_pixel;
    int endian;
    int	i;

	i = 0;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);

	if (cub->key.w)
	{
		
		if (cub->map.map[(int) (cub->player.y - PLAYER_SPEED)][(int) cub->player.x] != '1')
		{
			i = 0;
			while (i < 7)
				cub->rr.ray_y[i++] -= PLAYER_SPEED * TILE_SIZE;
			cub->player.y -= PLAYER_SPEED;
		}
	}
	if (cub->key.s)
	{
		if (cub->map.map[(int) (cub->player.y + PLAYER_SPEED)][(int) cub->player.x] != '1')
		{
			cub->player.y += PLAYER_SPEED;
			i = 0;
			while (i < 7)
				cub->rr.ray_y[i++] += PLAYER_SPEED * TILE_SIZE;
		}
	}
	if (cub->key.a)
	{
		if (cub->map.map[(int) cub->player.y][(int) (cub->player.x - PLAYER_SPEED)] != '1')
		{
			cub->player.x -= PLAYER_SPEED;
			i = 0;
			while (i < 7)
				cub->rr.ray_x[i++] -= PLAYER_SPEED * TILE_SIZE;
		}
	}
	if (cub->key.d)
	{
		if (cub->map.map[(int) cub->player.y][(int) (cub->player.x + PLAYER_SPEED)] != '1')
		{
			cub->player.x += PLAYER_SPEED;
			i = 0;
			while (i < 7)
				cub->rr.ray_x[i++] += PLAYER_SPEED * TILE_SIZE;
		}
	}
	draw_map_to_image(cub, cub->addr, cub->line_length);
	if (cub->start == 1)
		player_rotation_init(cub);
	if (cub->key.left)
		rotate_player(cub, -(ROTATION_SENSE));
	if (cub->key.right)
		rotate_player(cub, (ROTATION_SENSE));
	print_rot_ray(cub);
	draw_player_to_image(cub, cub->addr, cub->line_length);

	mlx_put_image_to_window(cub->con, cub->win, img, 0, 0);
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
}

void	window_init(t_cube *cub)
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
	load_textures(cub);
	start_keys(cub);
	mlx_key_hook(cub->win, handle_key_release, cub);
    mlx_hook(cub->win, KeyPress, KeyPressMask, handle_key_press, cub);
    mlx_hook(cub->win, KeyRelease, KeyReleaseMask, handle_key_release, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	mlx_loop_hook(cub->con, loop_hook, cub);
	mlx_loop(cub->con);
}

void	player_rotation_init(t_cube *cub)
{
	int	i;

	i = -1;
	cub->start = 0;
	if (cub->player.dir == 0)
	{
		while (++i < 7)
		{
			draw_p_to_image(cub->addr, cub->line_length, (cub->player.x * TILE_SIZE), (cub->player.y * TILE_SIZE) - (i * 3), DARK_GREEN);
			cub->rr.ray_x[i] =  (cub->player.x * TILE_SIZE);
			cub->rr.ray_y[i] =  (cub->player.y * TILE_SIZE) - (i * 3);
			cub->rr.angle_rad = M_PI / 2;
		}
	}
	else if (cub->player.dir == 1)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + (i * 3),
				(cub->player.y * TILE_SIZE), DARK_GREEN);
			cub->rr.ray_x[i] = (cub->player.x * TILE_SIZE) + (i * 3);
			cub->rr.ray_y[i] =  (cub->player.y * TILE_SIZE);
			cub->rr.angle_rad = M_PI * 2;

		}
	}
	else if (cub->player.dir == 2)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200,
				(cub->player.y * TILE_SIZE) + 200 + (i * 3), DARK_GREEN);
			cub->rr.ray_x[i] =  (cub->player.x * TILE_SIZE) + 200;
			cub->rr.ray_y[i] =  (cub->player.y * TILE_SIZE) + 200 + (i * 3);
			cub->rr.angle_rad = (3 * M_PI) / 2;
		}
	}
	else if (cub->player.dir == 3)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200 - (i * 3),
				(cub->player.y * TILE_SIZE) + 200, DARK_GREEN);
			cub->rr.ray_x[i] =  (cub->player.x * TILE_SIZE) + 200 - (i * 3);
			cub->rr.ray_y[i] =  (cub->player.y * TILE_SIZE);
			cub->rr.angle_rad = M_PI;
		}
	}
}

void	player_rotation_keys(int key, t_cube *cub)
{
	if (key == 65361)
		rotate_player(cub, -(0.2));
	else if (key == 65363)
	{
		rotate_player(cub, (0.2));
	}
}

void	rotate_player(t_cube *cub, double dir)
{
	int		i;
	double	distance;
	double	cx;
	double	cy;
	double	n_angle;

	i = 0;
	cx = (cub->player.x * TILE_SIZE);
	cy = (cub->player.y * TILE_SIZE);
	cub->rr.angle_rad += dir;
	if (cub->rr.angle_rad < 0)
		cub->rr.angle_rad += 2 * M_PI;
	else if (cub->rr.angle_rad > 2 * M_PI)
		cub->rr.angle_rad -= 2 * M_PI;
	while (i < 7)
	{
		distance = sqrt(pow(cub->rr.ray_x[i] - cx, 2) + pow(cub->rr.ray_y[i] - cy, 2));
		n_angle = atan2(cub->rr.ray_y[i] - cy, cub->rr.ray_x[i] - cx) + dir;
		cub->rr.ray_x[i] = cx + cos(n_angle) * distance;
		cub->rr.ray_y[i] = cy + sin(n_angle) * distance;
		draw_p_to_image(cub->addr, cub->line_length, (cub->rr.ray_x[i]),
			(cub->rr.ray_y[i]), DARK_GREEN);
		i++;
	}
}

