/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/26 17:35:43 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int close_x(t_cube *cub)
{
	printf("You closed the game.");
	int i = 0;
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

char *to_str(int n)
{
	int i;
	int len;
	char *str;
	char *tmp;

	if (n == 0)
	{
		str = (char *)malloc(2 * sizeof(char));
		str[0] = '0';
		return (str[1] = 0, str);
	}
	i = n;
	len = 0;
	while (i > 0 && ++len > -1)
		i /= 10;
	str = (char *)malloc((len + 1) * sizeof(char));
	tmp = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len)
		(tmp[i++] = n % (10) + 48, n /= 10);
	i = -1;
	while (++i <= len)
		str[i] = tmp[(len - 1) - i];
	return (free(tmp), str[i] = 0, str);
}

int mouse_events(int key)
{
	printf("the key pressed is %d\n", key);
	if (key == 1)
	{
		(call_cub())->key.mouse_l = 1;
		ft_putstr_fd("clicked\n", 1);
	}
	return (1);
}

void fov_option(t_cube *cub)
{
	char *fov_str;

	// cub->fov
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[5], WIDTH / 2.5, HEIGHT / 8);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[14], WIDTH / 2.38, HEIGHT / 8);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[21], WIDTH / 2.27, HEIGHT / 8);
	fov_str = to_str(cub->fov);
	if (cub->fov == 0)
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[0], WIDTH / (1.8), HEIGHT / 8);
	else if (ft_strlen(fov_str) == 1)
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[0] - 48], WIDTH / (1.8), HEIGHT / 8);
	else if (ft_strlen(fov_str) == 2)
	{
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[0] - 48], WIDTH / (1.8), HEIGHT / 8);
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[1] - 48], WIDTH / (1.75), HEIGHT / 8);
	}
	else if (ft_strlen(fov_str) == 3)
	{
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[0] - 48], WIDTH / (1.8), HEIGHT / 8);
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[1] - 48], WIDTH / (1.75), HEIGHT / 8);
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[fov_str[2] - 48], WIDTH / (1.70), HEIGHT / 8);
	}
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_r_options, WIDTH / 1.65, HEIGHT / 7.2);
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_l_options, WIDTH / 1.9, HEIGHT / 7.2);
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62 && cub->mouse_y > HEIGHT / 7.2 && cub->mouse_y < HEIGHT / 6 && cub->key.mouse_l)
	{
		// printf("YES !!!!!!");
		cub->fov += 10;
		cub->key.mouse_l = 0;
	}
}

void draw_options(t_cube *cub)
{
	char *sensi_str;

	mlx_mouse_show(cub->con, cub->win);
	mlx_put_image_to_window(cub->con, cub->win, cub->options_menu, WIDTH / 2.7, HEIGHT / 10);
	fov_option(cub);
	// SENSI
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[18], WIDTH / 2.5, HEIGHT / 4);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[4], WIDTH / 2.38, HEIGHT / 4);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[13], WIDTH / 2.27, HEIGHT / 4);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[18], WIDTH / 2.18, HEIGHT / 4);
	mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[8], WIDTH / 2.09, HEIGHT / 4);
	sensi_str = to_str(cub->sensi);
	if (cub->sensi <= 0)
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[0], WIDTH / (1.8), HEIGHT / 4);
	else if (ft_strlen(sensi_str) == 1)
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[sensi_str[0] - 48], WIDTH / (1.8), HEIGHT / 4);
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_r_options, WIDTH / 1.65, HEIGHT / 3.8);
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_l_options, WIDTH / 1.9, HEIGHT / 3.8);
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62 && cub->mouse_y > HEIGHT / 3.8 && cub->mouse_y < HEIGHT / 3.4 && cub->key.mouse_l && cub->sensi <= 10)
	{
		// printf("YES !!!!!!");
		cub->p_rotation += cub->p_rotation;
		cub->sensi++;
		cub->key.mouse_l = 0;
	}
}

int handle_key_press(int key, t_cube *cub)
{
	// printf("you pressed this %d\n\n", key);
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
	else if (key == L_CONTROL_KEY)
		cub->option_bool = -cub->option_bool;
	else if (key == 1)
		printf("hahahahah");
	return (0);
}

int handle_key_release(int key, t_cube *cub)
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

void draw_square_to_image(char *addr, int line_length, int x, int y, int color)
{
	int i;
	int j;

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			((int *)(addr))[(y + i) * line_length / 4 + x + j] = color;
		}
	}
}

void draw_p_to_image(char *addr, int line_length, int x, int y, int color)
{
	int i;
	int j;

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

void draw_player_to_image(t_cube *cub, char *addr, int line_length)
{
	int x;
	int y;
	int color;

	// Set the player color
	color = 0xFF0000; // Red

	// Calculate the player's position in pixels
	x = cub->player.x * TILE_SIZE;
	y = cub->player.y * TILE_SIZE;

	// Draw the player as a square
	draw_p_to_image(addr, line_length, x, y, color);
}

void draw_map_to_image(t_cube *cub, char *addr, int line_length)
{
	int x;
	int y;
	int color;

	for (y = 0; y < cub->map.rows; y++)
	{
		for (x = 0; x < cub->map.cols; x++)
		{
			if (cub->map.map[y][x] == '1') // Wall
				color = 0xFFFFFF;		   // White
			else if (cub->map.map[y][x] == '0')
				color = 0x008000; // Green
			else if (cub->map.map[y][x] == ' ')
				color = 0x000000;				// Green
			else if (cub->map.map[y][x] == 'D') // Doors
				color = 0x964B00;				// Brown
			draw_square_to_image(addr, line_length, x * TILE_SIZE, y * TILE_SIZE, color);
		}
	}
}

int remove_corners(t_cube *cub, int x, int y)
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

int is_corner(t_cube *cub, int x, int y)
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

void mouse_rotate(t_cube *cub)
{
	int m_x;

	m_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x >= WIDTH - (WIDTH / 50) || cub->mouse_x <= WIDTH / 50)
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

int loop_hook(t_cube *cub)
{
	void *img;
	int bits_per_pixel;
	int endian;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);
	// printf ("Player y is %d and x is %d\n", (int)cub->player.y, (int)cub->player.x);
	if (cub->key.w)
	{
		if ((cub->map.map[(int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '1'))
		{
			if ((cub->map.map[(int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '2') && remove_corners(cub, (int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad))), (int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad)))))
			{
				cub->player.y += PLAYER_SPEED * (sin(-cub->rr.angle_rad));
				cub->player.x += PLAYER_SPEED * (cos(-cub->rr.angle_rad));
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '2')
				cub->player.y += PLAYER_SPEED * (sin(-cub->rr.angle_rad));
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x += PLAYER_SPEED * (cos(-cub->rr.angle_rad));
		}
	}
	if (cub->key.s)
	{
		if (cub->map.map[(int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '1' && remove_corners(cub, (int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad))), (int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))))
		{
			if (cub->map.map[(int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad)))][(int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad)))] != '2')
			{
				cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad);
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad);
			}
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)(cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad))))
		{
			if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '2')
				cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad);
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad);
		}
	}
	if (cub->key.a)
	{
		if (cub->map.map[(int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))), (int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int)(cub->player.y - (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x - (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
			{
				cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2);
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y - PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '2')
				cub->player.y -= PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2);
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))] != '1' && !is_corner(cub, (int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x -= PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2);
		}
	}
	if (cub->key.d)
	{
		if (cub->map.map[(int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))), (int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int)(cub->player.y + (PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x + (PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
			{
				cub->player.y += PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2);
				cub->player.x += PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '2')
				cub->player.y += PLAYER_SPEED * sin(-cub->rr.angle_rad + M_PI / 2);
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))] != '1' && is_corner(cub, (int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x += PLAYER_SPEED * cos(-cub->rr.angle_rad + M_PI / 2);
		}
	}
	draw_map_to_image(cub, cub->addr, cub->line_length);
	if (cub->start == 1)
		player_rotation_init(cub);
	if (cub->option_bool == -1)
		mouse_rotate(cub);
	if (cub->key.left && cub->option_bool == -1)
		rotate_player(cub, (cub->p_rotation));
	if (cub->key.right && cub->option_bool == -1)
		rotate_player(cub, -(cub->p_rotation));
	draw_player_to_image(cub, cub->addr, cub->line_length);
	cast_ray(cub);
	mlx_put_image_to_window(cub->con, cub->win, img, 0, 0);
	if (cub->option_bool == 1)
		draw_options(cub);
	else
		mlx_mouse_hide(cub->con, cub->win);
	mlx_destroy_image(cub->con, img);
	return (0);
}

void start_keys(t_cube *cub)
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
	cub->mouse_click = 0;
}

void increment_alphabet(char *str, int index)
{
	int i;

	i = 0;
	while (str[i] && (str[i] < 65 || str[i] > 90))
		i++;
	str[i] = 65 + index;
}

void increment_numbers(char *str, int index)
{
	int i;

	i = 0;
	while (str[i] && (str[i] < 48 || str[i] > 57))
		i++;
	str[i] = 48 + index;
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
	cub->win = mlx_new_window(cub->con, WIDTH, HEIGHT, "cub3d");
	if (cub->win == NULL)
	{
		mlx_destroy_display(cub->con);
		free(cub->con);
		printf("Error\nCouldn't open the window.\n");
		exit_free(cub);
	}
	i = 0;
	// cub->alphabet = (void **)malloc(26 * sizeof(void *));
	while (i < 26)
	{
		cub->alphabet[i] = mlx_xpm_file_to_image(cub->con, alpha, &x, &y);
		mlx_put_image_to_window(cub->con, cub->win, cub->alphabet[i], x, y);
		i++;
		increment_alphabet(alpha, i);
	}
	i = 0;
	while (i < 10)
	{
		cub->numbers[i] = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		mlx_put_image_to_window(cub->con, cub->win, cub->numbers[i], x, y);
		i++;
		increment_numbers(num, i);
	}
	cub->arr_r_options = mlx_xpm_file_to_image(cub->con, "./textures/arrow_right.xpm", &x, &y);
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_r_options, x, y);
	cub->arr_l_options = mlx_xpm_file_to_image(cub->con, "./textures/arrow_left.xpm", &x, &y);
	mlx_put_image_to_window(cub->con, cub->win, cub->arr_l_options, x, y);
	cub->options_menu = mlx_xpm_file_to_image(cub->con, "./textures/options_menu_resized.xpm", &x, &y);
	mlx_mouse_hide(cub->con, cub->win);
	mlx_put_image_to_window(cub->con, cub->win, cub->options_menu, x, y);
	load_textures(cub);
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

void player_rotation_init(t_cube *cub)
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

void rotate_player(t_cube *cub, double dir)
{
	// double	distance;
	// double	cx;
	// double	cy;
	// double	n_angle;
	// double	x[7];
	// double	y[7];

	// cx = (cub->player.x * TILE_SIZE);
	// cy = (cub->player.y * TILE_SIZE);
	cub->rr.angle_rad += dir;
	// printf("\n\nDegrees : %f\n\n", cub->rr.angle_rad * (180 / M_PI));
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