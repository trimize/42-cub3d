/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/19 19:54:17 by trimize          ###   ########.fr       */
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
			else if (cub->map.map[y][x] == '0')
				color = 0x008000;  // Green
			else if (cub->map.map[y][x] == ' ')
				color = 0x000000;  // Green
			else if (cub->map.map[y][x] == 'D') //Doors
				color = 0x964B00; //Brown
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
	return (1);
}

void	mouse_rotate(t_cube *cub)
{
	int	m_x;

	m_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x >= WIDTH - (WIDTH / 50) || cub->mouse_x <= WIDTH / 50)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (m_x != cub->mouse_x)
	{
		if (cub->mouse_x > m_x)
			rotate_player(cub, -(ROTATION_SENSE));
		else if (cub->mouse_x < m_x)
			rotate_player(cub, ROTATION_SENSE);
	}
	printf("Mouse position :\nx : %d\ny : %d\n\n", cub->mouse_x, cub->mouse_y);
}

//void	draw_options(t_cube *cub)
//{
	
//}

int	loop_hook(t_cube *cub)
{
	void *img;
	int bits_per_pixel;
	int endian;
	int	i;

	i = 0;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);
	//printf ("Player y is %d and x is %d\n", (int)cub->player.y, (int)cub->player.x);
	if (cub->key.w)
	{
		if ((cub->map.map[(int) (cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '1'))
		{
			if ((cub->map.map[(int) (cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int) (cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '2') && remove_corners(cub, (int) (cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad))), (int) (cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))))
			{
				cub->player.y += PLAYER_SPEED * (sin(-cub->rr.angle_rad));
				cub->player.x += PLAYER_SPEED * (cos(-cub->rr.angle_rad));
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
				cub->player.y += PLAYER_SPEED * (sin(-cub->rr.angle_rad));	
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int) (cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad)), (int) cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x += PLAYER_SPEED * (cos(-cub->rr.angle_rad));
		}
	}
	if (cub->key.s)
	{
		if (cub->map.map[(int) (cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '1' && remove_corners(cub, (int) (cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad))), (int) (cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))))
		{
			if (cub->map.map[(int) (cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int) (cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '2')
			{	
				cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad);
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad);
			}
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '1' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad))))
		{
				if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) (cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int) cub->player.x] != '2')
					cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad);
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int) (cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad)), (int) cub->player.y))
		{
			if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad);
		}	
	}
	if (cub->key.a)
	{
		if (cub->map.map[(int) (cub->player.y - (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int) (cub->player.x - (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y - (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int) (cub->player.y - (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x - (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
			{
				cub->player.y -= PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2);
				cub->player.x -= PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y - PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))))
		{
			if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y - PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
				cub->player.y -= PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2);
		}
		else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && !is_corner(cub, (int) (cub->player.x - PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
		{
			if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x - PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x -= PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2);
		}
	}
	if (cub->key.d)
	{
		if (cub->map.map[(int) (cub->player.y + (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int) (cub->player.x + (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))), (int) (cub->player.y + (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int) (cub->player.y + (PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2)))][(int) (cub->player.x + (PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)))] != '2')
			{	
				cub->player.y += PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2);
				cub->player.x += PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '1' && is_corner(cub, (int) cub->player.x, (int) (cub->player.y + PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))))
		{
			if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) (cub->player.y + PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2))][(int) cub->player.x] != '2')
				cub->player.y += PLAYER_SPEED * sin(- cub->rr.angle_rad + M_PI / 2);	
		}
		else if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))] != '1' && is_corner(cub, (int) (cub->player.x + PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2)), (int) cub->player.y))
		{
			if (- cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int) cub->player.y][(int) (cub->player.x + PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x += PLAYER_SPEED * cos(- cub->rr.angle_rad + M_PI / 2);
		}
	}
	
	draw_map_to_image(cub, cub->addr, cub->line_length);
	if (cub->start == 1)
		player_rotation_init(cub);
	mouse_rotate(cub);
	if (cub->key.left)
		rotate_player(cub, (ROTATION_SENSE));
	if (cub->key.right)
		rotate_player(cub, -(ROTATION_SENSE));
	draw_player_to_image(cub, cub->addr, cub->line_length);
	cast_ray(cub);
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
	mlx_mouse_hide(cub->con, cub->win);
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
	int		i;
	// double	distance;
	// double	cx;
	// double	cy;
	// double	n_angle;
	// double	x[7];
	// double	y[7];

	i = 0;
	// cx = (cub->player.x * TILE_SIZE);
	// cy = (cub->player.y * TILE_SIZE);
	cub->rr.angle_rad += dir;
	//printf("\n\nDegrees : %f\n\n", cub->rr.angle_rad * (180 / M_PI));
	if (cub->rr.angle_rad < 0)
		cub->rr.angle_rad += 2 * M_PI;
	else if (cub->rr.angle_rad > 2 * M_PI)
		cub->rr.angle_rad -= 2 * M_PI;
	// while (i < 7)
	// {
	// 	distance = sqrt(pow(cub->rr.ray_x[i] - cx, 2) + pow(cub->rr.ray_y[i] - cy, 2));
	// 	n_angle = atan2(cub->rr.ray_y[i] - cy, cub->rr.ray_x[i] - cx) + dir;
	// 	cub->rr.ray_x[i] = cx + cos(n_angle) * distance;
	// 	cub->rr.ray_y[i] = cy + sin(n_angle) * distance;
	// 	x[i] = cub->rr.ray_x[i];
	// 	y[i] = cub->rr.ray_y[i];
	// 	if (cub->rr.ray_x[i] < 0)
	// 	{
	// 		cub->rr.ray_x[i] = 0;
	// 		cub->rr.ray_y[i] = cub->rr.ray_y[i - 1];
	// 	}
	// 	else
	// 	{
	// 		cub->rr.ray_x[i] = x[i];
	// 		cub->rr.ray_y[i] = y[i];
	// 	}	
	// 	if (cub->rr.ray_y[i] < 0)
	// 	{
	// 		x[i] = cub->rr.ray_x[i];
	// 		y[i] = cub->rr.ray_y[i];
	// 		cub->rr.ray_y[i] = 0;
	// 		cub->rr.ray_x[i] = cub->rr.ray_x[i - 1];
	// 	}
	// 	else
	// 	{
	// 		cub->rr.ray_x[i] = x[i];
	// 		cub->rr.ray_y[i] = y[i];
	// 	}
	// 	draw_p_to_image(cub->addr, cub->line_length, (cub->rr.ray_x[i]),
	// 		(cub->rr.ray_y[i]), DARK_GREEN);
	// 	i++;
	// }
}