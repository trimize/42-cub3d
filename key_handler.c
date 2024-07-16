/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:46:37 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 13:28:54 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	press_key_helper(int key, t_cube *cub)
{
	if (key == XK_Tab)
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
}

int	handle_key_press(int key, t_cube *cub)
{
	if (key == XK_Escape)
	{
		printf("You pressed ESC and closed the game\n");
		close_x(cub);
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
	else
		press_key_helper(key, cub);
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
