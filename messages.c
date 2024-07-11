/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:48:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/11 21:37:49 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	change_print(int *print)
{
	if (*print == 0)
		*print = 1;
	else
		*print = 0;
}

void	display_messages(t_cube *cub)
{
	int	i;
	int	print;

	i = 0;
	print = 0;
	if (cub->door_open_msg && !print)
		(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Press E to open door."));
	if (cub->door_close_msg && !print)
		(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Press E to close door."));
	while (i < cub->weapon_counter)
	{
		if (cub->weapons[i].type == '|' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a sword."));
		else if (cub->weapons[i].type == 'O' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a shield."));
		else if (cub->weapons[i].type == 'C' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a crossbow."));
		else if (cub->weapons[i].type == 'G' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a dragon's staff."));
		i++;
	}
	i = 0;
	while (i < cub->items_counter)
	{
		if (cub->items[i].type == 'Q' && !cub->items[i].display && get_current_time() - cub->items[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up three arrows."));
		else if (cub->items[i].type == 'A' && !cub->items[i].display && get_current_time() - cub->items[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up an attack bonus."));
		else if (cub->items[i].type == 'V' && !cub->items[i].display && get_current_time() - cub->items[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up an speed bonus."));
		else if (cub->items[i].type == 'H' && !cub->items[i].display && get_current_time() - cub->items[i].last_text < 3000 && !print)
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a health potion."));
		else if (cub->items[i].type == 'H' && cub->items[i].display && (cub->items[i].msg == 1 || (cub->items[i].last_text != -1 && get_current_time() - cub->items[i].last_text < 3000)) && !print)
		{
			cub->items[i].msg = 0;
			(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Your health is full."));
		}
		i++;
	}
}