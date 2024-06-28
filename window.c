/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 17:53:54 by trimize          ###   ########.fr       */
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

void	draw_xpm_alpha(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->abc[alpha].height)
	{
		while (j < cub->abc[alpha].width)
		{
			if (((int *)(cub->abc[alpha].addr))[(i) * cub->abc[alpha].line_length / 4 + j] == 0xFFFFFF)
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->abc[alpha].addr))[(i) * cub->abc[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_s_animation(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->sword_ani[alpha].height)
	{
		while (j < cub->sword_ani[alpha].width)
		{
			if (x + j < WIDTH && y + i < HEIGHT && ((int *)(cub->sword_ani[alpha].addr))[(i) * cub->sword_ani[alpha].line_length / 4 + j] != 0x0000FF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->sword_ani[alpha].addr))[(i) * cub->sword_ani[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_texture(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->txt[alpha].height)
	{
		while (j < cub->txt[alpha].width)
		{
			if (alpha == 5 || alpha == 6)
			{
				if (((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] == 0xFFFFFF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			}
			else if (alpha == 7 || alpha == 8 || alpha == 9)
			{
				if (((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] != 0x0000FF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			}
			else
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_hp(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->hp_frame[alpha].height)
	{
		while (j < cub->hp_frame[alpha].width)
		{
			((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->hp_frame[alpha].addr))[(i) * cub->hp_frame[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_number(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->nums[alpha].height)
	{
		while (j < cub->nums[alpha].width)
		{
			if (((int *)(cub->nums[alpha].addr))[(i) * cub->nums[alpha].line_length / 4 + j] == 0xFFFFFF)	
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->nums[alpha].addr))[(i) * cub->nums[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

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
	while (++i < len)
		str[i] = tmp[(len - 1) - i];
	return (free(tmp), str[i] = 0, str);
}

int mouse_events(int key)
{
	if (key == 1)
	{
		(call_cub())->key.mouse_l = 1;
	}
	return (1);
}

void	speed_option(t_cube *cub)
{
	char *p_speed_str;

	draw_xpm_alpha(18, WIDTH / 2.35, HEIGHT / 2.6, cub);
	draw_xpm_alpha(15, WIDTH / 2.25, HEIGHT / 2.6, cub);
	draw_xpm_alpha(4, WIDTH / 2.16, HEIGHT / 2.6, cub);
	draw_xpm_alpha(4, WIDTH / 2.08, HEIGHT / 2.6, cub);
	draw_xpm_alpha(3, WIDTH / 2.01, HEIGHT / 2.6, cub);
	p_speed_str = to_str(cub->speed);
	if (cub->fov == 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 2.6, cub);
	else if (ft_strlen(p_speed_str) == 1)
		draw_xpm_number(p_speed_str[0] - 48, WIDTH / 1.8, HEIGHT / 2.6, cub);
	else if (ft_strlen(p_speed_str) == 2)
	{
		draw_xpm_number(p_speed_str[0] - 48, WIDTH / 1.8, HEIGHT / 2.6, cub);
		draw_xpm_number(p_speed_str[1] - 48, WIDTH / 1.75, HEIGHT / 2.6, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 2.5, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 2.5, cub);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62 && cub->mouse_y > HEIGHT / 2.5 && cub->mouse_y < HEIGHT / 2.4 && cub->key.mouse_l && cub->speed < 10)
	{
		cub->p_speed += 0.009;
		cub->speed++;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85 && cub->mouse_y > HEIGHT / 2.5 && cub->mouse_y < HEIGHT / 2.4 && cub->key.mouse_l && cub->speed <= 10 && cub->speed > 1)
	{
		cub->p_speed -= 0.009;
		if (cub->p_speed <= 0)
			cub->p_speed = 0.006;
		cub->speed--;
		cub->key.mouse_l = 0;
	}
}

void	sensi_option(t_cube *cub)
{
	char *sensi_str;

	draw_xpm_alpha(18, WIDTH / 2.35, HEIGHT / 2, cub);
	draw_xpm_alpha(4, WIDTH / 2.25, HEIGHT / 2, cub);
	draw_xpm_alpha(13, WIDTH / 2.16, HEIGHT / 2, cub);
	draw_xpm_alpha(18, WIDTH / 2.08, HEIGHT / 2, cub);
	draw_xpm_alpha(8, WIDTH / 2.01, HEIGHT / 2, cub);
	sensi_str = to_str(cub->sensi);
	if (cub->sensi <= 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 2, cub);
	else if (ft_strlen(sensi_str) == 1)
		draw_xpm_number(sensi_str[0] - 48, WIDTH / 1.8, HEIGHT / 2, cub);
	else if (ft_strlen(sensi_str) == 2)
	{
		draw_xpm_number(sensi_str[0] - 48, WIDTH / 1.8, HEIGHT / 2, cub);
		draw_xpm_number(sensi_str[1] - 48, WIDTH / 1.75, HEIGHT / 2, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 1.94, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 1.94, cub);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62 && cub->mouse_y > HEIGHT / 1.94 && cub->mouse_y < HEIGHT / 1.85 && cub->key.mouse_l && cub->sensi < 10)
	{
		cub->p_rotation += 0.0299 / 4;
		cub->sensi++;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85 && cub->mouse_y > HEIGHT / 1.94 && cub->mouse_y < HEIGHT / 1.85 && cub->key.mouse_l && cub->sensi <= 10 && cub->sensi > 1)
	{
		cub->p_rotation -= 0.0299 / 4;
		cub->sensi--;
		cub->key.mouse_l = 0;
	}
}

void fov_option(t_cube *cub)
{
	char *fov_str;

	draw_xpm_alpha(5, WIDTH / 2.3, HEIGHT / 4, cub);
	draw_xpm_alpha(14, WIDTH / 2.2, HEIGHT / 4, cub);
	draw_xpm_alpha(21, WIDTH / 2.1, HEIGHT / 4, cub);
	fov_str = to_str(cub->fov);
	if (cub->fov == 0)
		draw_xpm_number(0, WIDTH / 1.8, HEIGHT / 4, cub);
	else if (ft_strlen(fov_str) == 1)
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
	else if (ft_strlen(fov_str) == 2)
	{
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[1] - 48, WIDTH / 1.75, HEIGHT / 4, cub);
	}
	else if (ft_strlen(fov_str) == 3)
	{
		draw_xpm_number(fov_str[0] - 48, WIDTH / 1.8, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[1] - 48, WIDTH / 1.75, HEIGHT / 4, cub);
		draw_xpm_number(fov_str[2] - 48, WIDTH / 1.7, HEIGHT / 4, cub);
	}
	draw_xpm_texture(5, WIDTH / 1.65, HEIGHT / 3.8, cub);
	draw_xpm_texture(6, WIDTH / 1.9, HEIGHT / 3.8, cub);
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x > WIDTH / 1.65 && cub->mouse_x < WIDTH / 1.62 && cub->mouse_y > HEIGHT / 3.8 && cub->mouse_y < HEIGHT / 3.4 && cub->key.mouse_l)
	{
		cub->fov += 10;
		cub->key.mouse_l = 0;
	}
	else if (cub->mouse_x > WIDTH / 1.91 && cub->mouse_x < WIDTH / 1.85 && cub->mouse_y > HEIGHT / 3.8 && cub->mouse_y < HEIGHT / 3.4 && cub->key.mouse_l)
	{
		cub->fov -= 10;
		cub->key.mouse_l = 0;
	}
}

void draw_options(t_cube *cub)
{
	mlx_mouse_show(cub->con, cub->win);
	draw_xpm_texture(4, WIDTH / 2.5, HEIGHT / 10, cub);
	draw_xpm_alpha(14, WIDTH / 1.99, HEIGHT / 8, cub);
	draw_xpm_alpha(15, WIDTH / 1.92, HEIGHT / 8, cub);
	draw_xpm_alpha(19, WIDTH / 1.86, HEIGHT / 8, cub);
	draw_xpm_alpha(8, WIDTH / 1.8, HEIGHT / 8, cub);
	draw_xpm_alpha(14, WIDTH / 1.75, HEIGHT / 8, cub);
	draw_xpm_alpha(13, WIDTH / 1.7, HEIGHT / 8, cub);
	draw_xpm_alpha(18, WIDTH / 1.65, HEIGHT / 8, cub);
	speed_option(cub);
	sensi_option(cub);
	fov_option(cub);
}

int handle_key_press(int key, t_cube *cub)
{
	printf("you pressed this %d\n\n", key);
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
	else if (key == 65513)
		cub->option_bool = -cub->option_bool;
	else if (key == 65289)
		cub->player.hp -= 25;
	else if (key == 49)
		cub->player.weapon = 1;
	else if (key == 50)
		cub->player.weapon = 2;
	else if (key == 51)
		cub->player.weapon = 3;
	else if (key == 52)
		cub->player.weapon = 4;
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
	if (cub->mouse_x >= WIDTH - (WIDTH / 5) || cub->mouse_x <= WIDTH / 5)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (cub->mouse_y >= HEIGHT - (HEIGHT / 5) || cub->mouse_x <= HEIGHT / 5)
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

void increment_numbers(char *str, int index);

void	weapon_slot_handler(t_cube *cub)
{
	if (cub->player.weapon == 1)
		draw_xpm_texture(8, WIDTH / 60, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 60, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 2)
		draw_xpm_texture(8, WIDTH / 19, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 19, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 3)
		draw_xpm_texture(8, WIDTH / 11.3, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 11.3, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 4)
		draw_xpm_texture(8, WIDTH / 8.05, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 8.05, HEIGHT / 1.2, cub);
	if (cub->weapons_in_slot[0] == 1)
		draw_xpm_texture(9, WIDTH / 35, HEIGHT / 1.19, cub);
}

void	sword_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1 && cub->weapons_in_slot[cub->player.weapon - 1] == 1)
	{
		update_animation(cub);
		draw_xpm_s_animation(cub->current_frame_num_sword, WIDTH / 2.5, HEIGHT / 4, cub);
		if (cub->current_frame_num_sword == 4)
		{
			cub->key.mouse_l = 0;
			cub->current_frame_num_sword = 0;
		}
	}
	else if (cub->weapons_in_slot[cub->player.weapon - 1] == 1)
		draw_xpm_s_animation(0, WIDTH / 2.5, HEIGHT / 4, cub);
}

void	hp_handler(t_cube *cub)
{
	if (cub->player.hp == 100)
		draw_xpm_hp(0, WIDTH / 60, HEIGHT / 1.1, cub);
	else if (cub->player.hp == 75 && cub->current_frame_num_hp <= 2)
	{
		if (cub->current_frame_num_hp < 2)
			animate_health_bar(cub, 2);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 50 && cub->current_frame_num_hp <= 4)
	{
		if (cub->current_frame_num_hp < 4)
			animate_health_bar(cub, 4);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 25 && cub->current_frame_num_hp <= 6)
	{
		if (cub->current_frame_num_hp < 6)
			animate_health_bar(cub, 6);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
}
int loop_hook(t_cube *cub)
{
	void *img;
	int bits_per_pixel;
	int endian;
	//int	i;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(img, &bits_per_pixel, &cub->line_length, &endian);
	// printf ("Player y is %d and x is %d\n", (int)cub->player.y, (int)cub->player.x);
	if (cub->key.w)
	{
		if ((cub->map.map[(int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad)))][(int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad)))] != '1'))
		{
			if ((cub->map.map[(int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad)))][(int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad)))] != '2') && remove_corners(cub, (int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad))), (int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad)))))
			{
				cub->player.y += cub->p_speed * (sin(-cub->rr.angle_rad));
				cub->player.x += cub->p_speed * (cos(-cub->rr.angle_rad));
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '2')
				cub->player.y += cub->p_speed * (sin(-cub->rr.angle_rad));
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x += cub->p_speed * (cos(-cub->rr.angle_rad));
		}
	}
	if (cub->key.s)
	{
		if (cub->map.map[(int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad)))][(int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad)))] != '1' && remove_corners(cub, (int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad))), (int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad)))))
		{
			if (cub->map.map[(int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad)))][(int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad)))] != '2')
			{
				cub->player.y -= cub->p_speed * sin(-cub->rr.angle_rad);
				cub->player.x -= cub->p_speed * cos(-cub->rr.angle_rad);
			}
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)(cub->player.y - cub->p_speed * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y - cub->p_speed * sin(-cub->rr.angle_rad))))
		{
			if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad))][(int)cub->player.x] != '2')
				cub->player.y -= cub->p_speed * sin(-cub->rr.angle_rad);
		}
		else if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad))] != '1' && is_corner(cub, (int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != 3 * M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad))] != '2')
				cub->player.x -= cub->p_speed * cos(-cub->rr.angle_rad);
		}
	}
	if (cub->key.a)
	{
		if (cub->map.map[(int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))), (int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int)(cub->player.y - (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x - (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
			{
				cub->player.y -= cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2);
				cub->player.x -= cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y - cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y - cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y - cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '2')
				cub->player.y -= cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2);
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))] != '1' && !is_corner(cub, (int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x - cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x -= cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2);
		}
	}
	if (cub->key.d)
	{
		if (cub->map.map[(int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)))] != '1' && remove_corners(cub, (int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))), (int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))))
		{
			if (cub->map.map[(int)(cub->player.y + (cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2)))][(int)(cub->player.x + (cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
			{
				cub->player.y += cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2);
				cub->player.x += cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2);
			}
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '1' && is_corner(cub, (int)cub->player.x, (int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)(cub->player.y + cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x] != '2')
				cub->player.y += cub->p_speed * sin(-cub->rr.angle_rad + M_PI / 2);
		}
		else if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))] != '1' && is_corner(cub, (int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2)), (int)cub->player.y))
		{
			if (-cub->rr.angle_rad != M_PI / 2 && cub->map.map[(int)cub->player.y][(int)(cub->player.x + cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2))] != '2')
				cub->player.x += cub->p_speed * cos(-cub->rr.angle_rad + M_PI / 2);
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
	sword_handler(cub);
	hp_handler(cub);
	weapon_slot_handler(cub);
	mlx_put_image_to_window(cub->con, cub->win, img, 0, 0);
	if (cub->option_bool == 1)
		draw_options(cub);
	else
		mlx_mouse_hide(cub->con, cub->win);
	mlx_destroy_image(cub->con, img);
	return (0);
}

void	init_w_slots(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
		cub->weapons_in_slot[i++] = 0;
	cub->weapons_in_slot[0] = 1;
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
	cub->p_speed = 0.006;
	cub->speed = 3;
	cub->current_frame_num_sword = 0;
	cub->sword_delay = 3;
	cub->player.hp = 100;
	cub->hp_delay = 6;
	cub->current_frame_num_hp = 1;
	cub->player.weapon = 1;
	init_w_slots(cub);
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
	cub->hp_frame = (t_txt *)malloc(7 * sizeof(t_txt));
	while (i < 7)
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
	cub->arr_r_options = mlx_xpm_file_to_image(cub->con, "./textures/arrow_right.xpm", &x, &y);
	cub->txt[5].addr = mlx_get_data_addr(cub->arr_r_options, &cub->txt[5].bits_per_pixel,
			&cub->txt[5].line_length, &cub->txt[5].endian);
	cub->txt[5].width = 16;
	cub->txt[5].height = 18;
	cub->arr_l_options = mlx_xpm_file_to_image(cub->con, "./textures/arrow_left.xpm", &x, &y);
	cub->txt[6].addr = mlx_get_data_addr(cub->arr_l_options, &cub->txt[6].bits_per_pixel,
			&cub->txt[6].line_length, &cub->txt[6].endian);
	cub->txt[6].width = 16;
	cub->txt[6].height = 18;
	cub->options_menu = mlx_xpm_file_to_image(cub->con, "./textures/options_menu_resized.xpm", &x, &y);
	cub->txt[4].addr = mlx_get_data_addr(cub->options_menu, &cub->txt[4].bits_per_pixel,
			&cub->txt[4].line_length, &cub->txt[4].endian);
	cub->txt[4].width = 400;
	cub->txt[4].height = 547;
	cub->w_slot = mlx_xpm_file_to_image(cub->con, "./textures/weapon_slot.xpm", &x, &y);
	cub->txt[7].addr = mlx_get_data_addr(cub->w_slot, &cub->txt[7].bits_per_pixel,
			&cub->txt[7].line_length, &cub->txt[7].endian);
	cub->txt[7].width = 44;
	cub->txt[7].height = 44;
	cub->w_slot_white = mlx_xpm_file_to_image(cub->con, "./textures/weapon_slot_white.xpm", &x, &y);
	cub->txt[8].addr = mlx_get_data_addr(cub->w_slot_white, &cub->txt[8].bits_per_pixel,
			&cub->txt[8].line_length, &cub->txt[8].endian);
	cub->txt[8].width = 44;
	cub->txt[8].height = 44;
	cub->sword_slot = mlx_xpm_file_to_image(cub->con, "./textures/sword_weapon_slot.xpm", &x, &y);
	cub->txt[9].addr = mlx_get_data_addr(cub->sword_slot, &cub->txt[9].bits_per_pixel,
			&cub->txt[9].line_length, &cub->txt[9].endian);
	cub->txt[9].width = 12;
	cub->txt[9].height = 34;
	mlx_mouse_hide(cub->con, cub->win);
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