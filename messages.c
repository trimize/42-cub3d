/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:48:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 19:50:12 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	display_items_msg2(t_cube *cub, int *print, int *i)
{
	if (cub->items[*i].type == 'H' && !cub->items[*i].display
		&& get_current_time() - cub->items[*i].last_text < 3000 && !*print)
		(change_print(print), mlx_string_put(cub->con, cub->win,
				WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF,
				"You picked up a health potion."));
	else if (cub->items[*i].type == 'H' && cub->items[*i].display
		&& (cub->items[*i].msg == 1 || (cub->items[*i].last_text != -1
				&& get_current_time() - cub->items[*i].last_text < 3000))
		&& !*print)
	{
		cub->items[*i].msg = 0;
		(change_print(print), mlx_string_put(cub->con, cub->win,
				WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF,
				"Your health is full."));
	}
}

void	display_items_msg(t_cube *cub, int *print)
{
	int	i;

	i = -1;
	while (++i < cub->items_counter)
	{
		if (cub->items[i].type == 'Q' && !cub->items[i].display
			&& get_current_time() - cub->items[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win,
					WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF,
					"You picked up three arrows."));
		else if (cub->items[i].type == 'A' && !cub->items[i].display
			&& get_current_time() - cub->items[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win,
					WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF,
					"You picked up an attack bonus."));
		else if (cub->items[i].type == 'V' && !cub->items[i].display
			&& get_current_time() - cub->items[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win,
					WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF,
					"You picked up an speed bonus."));
		else
			display_items_msg2(cub, print, &i);
	}
}

void	display_weapons_msg(t_cube *cub, int *print)
{
	int	i;

	i = -1;
	while (++i < cub->weapon_counter)
	{
		if (cub->weapons[i].type == '|' && cub->weapons[i].display == 0
			&& get_current_time() - cub->weapons[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a sword."));
		else if (cub->weapons[i].type == 'O' && cub->weapons[i].display == 0
			&& get_current_time() - cub->weapons[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4),
					0xFFFFFF, "You picked up a shield."));
		else if (cub->weapons[i].type == 'C' && cub->weapons[i].display == 0
			&& get_current_time() - cub->weapons[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4),
					0xFFFFFF, "You picked up a crossbow."));
		else if (cub->weapons[i].type == 'G' && cub->weapons[i].display == 0
			&& get_current_time() - cub->weapons[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4),
					0xFFFFFF, "You picked up a dragon's staff."));
	}
}

void	display_messages(t_cube *cub)
{
	int	print;

	print = 0;
	if (cub->door_open_msg && !print)
		(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
				HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Press E to open door."));
	if (cub->door_close_msg && !print)
		(change_print(&print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
				HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Press E to close door."));
	display_weapons_msg(cub, &print);
	display_items_msg(cub, &print);
	display_dropped_msg(cub, &print);
}
