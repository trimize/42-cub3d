/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/14 21:49:21 by trimize          ###   ########.fr       */
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
int	handle_input(int key, t_cube *cub)
{
	printf("\n\n YOU PRESSED %d \n\n", key);
	if (key == XK_Escape)
	{
		printf("You pressed ESC and closed the game\n");
		close_x(cub);
		exit(1);
	}
	else if (key == 119)
	{
		cub->player.x += cub->rr.pdx * 5;
		cub->player.y += cub->rr.pdy * 5;
	}
	else if (key == 115)
	{
		cub->player.x -= cub->rr.pdx * 5;
		cub->player.y -= cub->rr.pdy * 5;
	}
	else if (key == 97)
		cub->player.x -= PLAYER_SPEED;
	else if (key == 100)
		cub->player.x += PLAYER_SPEED;

	mlx_clear_window(cub->con, cub->win);
	draw_map(cub);
	if (cub->start == 1)
		player_rotation_init(cub);
	player_rotation_keys(key, cub);
	draw_player(cub);
	mlx_do_sync(cub->con);
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
	// init_rays(cub);
	load_textures(cub);
	mlx_key_hook(cub->win, handle_input, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	// mlx_loop_hook(cub->con, loop_hook, cub);
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
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200,
				(cub->player.y * TILE_SIZE) + 200 - (i * 3), DARK_GREEN);
			cub->rr.ray_x[i] =  (cub->player.x * TILE_SIZE) + 200;
			cub->rr.ray_y[i] =  (cub->player.y * TILE_SIZE) + 200 - (i * 3);
			cub->rr.angle_rad = M_PI / 2;
			cub->rr.pdx = cos(cub->rr.angle_rad);
			cub->rr.pdy = sin(cub->rr.angle_rad);
		}
	}
	else if (cub->player.dir == 1)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200 + (i * 3),
				(cub->player.y * TILE_SIZE) + 200, DARK_GREEN);
			cub->rr.ray_x[i] =  cub->player.x + (i * 3);
			cub->rr.ray_y[i] =  cub->player.y;
			cub->rr.angle_rad = M_PI * 2;
			cub->rr.pdx = cos(cub->rr.angle_rad);
			cub->rr.pdy = sin(cub->rr.angle_rad);
		}
	}
	else if (cub->player.dir == 2)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200,
				(cub->player.y * TILE_SIZE) + 200 + (i * 3), DARK_GREEN);
			cub->rr.ray_x[i] =  cub->player.x;
			cub->rr.ray_y[i] =  cub->player.y + (i * 3);
			cub->rr.angle_rad = (3 * M_PI) / 2;
			cub->rr.pdx = cos(cub->rr.angle_rad);
			cub->rr.pdy = sin(cub->rr.angle_rad);
		}
	}
	else if (cub->player.dir == 3)
	{
		while (++i < 7)
		{
			draw_dot(cub, (cub->player.x * TILE_SIZE) + 200 - (i * 3),
				(cub->player.y * TILE_SIZE) + 200, DARK_GREEN);
			cub->rr.ray_x[i] =  cub->player.x - (i * 3);
			cub->rr.ray_y[i] =  cub->player.y;
			cub->rr.angle_rad = M_PI;
			cub->rr.pdx = cos(cub->rr.angle_rad);
			cub->rr.pdy = sin(cub->rr.angle_rad);
		}
	}
}

void	player_rotation_keys(int key, t_cube *cub)
{
	if (key == 65361)
		rotate_player(cub, -(0.2));
	else if (key == 65363)
	{
		//Right
	}
}

void	rotate_player(t_cube *cub, double dir)
{
	int		i;
	int		y;

	i = 0;
	y = 1;
	cub->rr.angle_rad += dir;
	while (i < 7)
	{
		if (cub->rr.angle_rad < 0)
			cub->rr.angle_rad += 2 * M_PI;
		else if (cub->rr.angle_rad > 2 * M_PI)
			cub->rr.angle_rad -= 2 * M_PI;
		cub->rr.pdx = cos(cub->rr.angle_rad) * 7 * y * i;
		cub->rr.pdy = sin(cub->rr.angle_rad) * 7 * y * i;
		draw_dot(cub, cub->rr.ray_x[i] + cub->rr.pdx,
			cub->rr.ray_y[i] + cub->rr.pdy, DARK_GREEN);
		y += 0.2;
		printf("\n\n%f\n\n", cub->rr.ray_y[i]);
		i++;
	}
}
