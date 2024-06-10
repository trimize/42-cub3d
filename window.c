/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/10 21:40:58 by mbrandao         ###   ########.fr       */
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

void	draw_dot(t_cube *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = MAP_SIZE;
	i = x - size / 2;
	while (i <= x + size / 2)
    {
		j = y - size / 2;
        while (j <= y + size / 2)
        {
            mlx_pixel_put(cub->con, cub->win, i, j, color);
            j++;
        }
        i++;
    }
}

void	draw_dot_map(t_cube *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 20;
	i = x - size / 2;
	while (i <= x + size / 2)
    {
		j = y - size / 2;
        while (j <= y + size / 2)
        {
            mlx_pixel_put(cub->con, cub->win, i, j, color);
            j++;
        }
        i++;
    }
}

void	draw_player(t_cube *cub)
{
	int	color;

	color = 0xFFFFFF; // White color, you can choose any color you prefer

	// printf("\n PLAYER X IS %d AND PLAYER Y IS %d\n", x, y);
	draw_dot(cub, (cub->player.x * 5) + 200, (cub->player.y * 5) + 200, color);
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
				draw_dot_map(cub, (j * 20) + 200, (i * 20) + 200, 0x0000FF);
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
		cub->player.y--;
	else if (key == 115)
		cub->player.y++;
	else if (key == 97)
		cub->player.x--;
	else if (key == 100)
		cub->player.x++;

	mlx_clear_window(cub->con, cub->win);
	draw_map(cub);
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

int	loop_hook(t_cube *cub)
{
	mlx_clear_window(cub->con, cub->win);
	draw_map(cub);
    draw_player(cub);
    mlx_do_sync(cub->con);
    return (0);
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
	// init_rays(cub);
	load_textures(cub);
	mlx_key_hook(cub->win, handle_input, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	// mlx_loop_hook(cub->con, loop_hook, cub);
	mlx_loop(cub->con);
}
