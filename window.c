/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 21:16:26 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	close_x(t_cube *cub)
{
	printf("You closed the game.");
	// free_imgs(data);
	mlx_destroy_window(cub->con, cub->win);
	mlx_destroy_display(cub->con);
	free(cub->con);
	// free_map(data->map);
	exit_free(cub);
	return (0);
}
// Key codes
// W -> 119
// A -> 119
// S -> 119
// D -> 119
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
		;// move_up(cub);
	else if (key == 115)
		;// move_down(cub);
	else if (key == 97)
		;// move_left(cub);
	else if (key == 100)
		;// move_right(cub);
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
	mlx_key_hook(cub->win, handle_input, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	mlx_loop(cub->con);
}
