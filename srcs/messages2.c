/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:13:43 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	change_print(int *print)
{
	if (*print == 0)
		*print = 1;
	else
		*print = 0;
}

void	display_dropped_msg2(t_cube *cub, int *print, int *i)
{
	if (cub->dropped_items[*i].type == 'V'
		&& !cub->dropped_items[*i].display && get_current_time()
		- cub->dropped_items[*i].last_text < 3000 && !*print)
		(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
				HEIGHT - (HEIGHT / 4), 0xFFFFFF,
				"You picked up a speed bonus."));
	else if (cub->dropped_items[*i].type == 'H'
		&& !cub->dropped_items[*i].display && get_current_time()
		- cub->dropped_items[*i].last_text < 3000 && !*print)
		(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
				HEIGHT - (HEIGHT / 4), 0xFFFFFF,
				"You picked up a health potion."));
	else if (cub->dropped_items[*i].type == 'H'
		&& cub->dropped_items[*i].display && (cub->dropped_items[*i].msg == 1
			|| (cub->dropped_items[*i].last_text != -1 && get_current_time()
				- cub->dropped_items[*i].last_text < 3000)) && !*print)
	{
		cub->dropped_items[*i].msg = 0;
		(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
				HEIGHT - (HEIGHT / 4), 0xFFFFFF, "Your health is full."));
	}
}

void	display_dropped_msg(t_cube *cub, int *print)
{
	int	i;

	i = -1;
	while (++i < cub->dropped_index)
	{
		if (cub->dropped_items[i].type == 'Q'
			&& !cub->dropped_items[i].display && get_current_time()
			- cub->dropped_items[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4), 0xFFFFFF,
					"You picked up three arrows."));
		else if (cub->dropped_items[i].type == 'A'
			&& !cub->dropped_items[i].display && get_current_time()
			- cub->dropped_items[i].last_text < 3000 && !*print)
			(change_print(print), mlx_string_put(cub->con, cub->win, WIDTH / 2,
					HEIGHT - (HEIGHT / 4), 0xFFFFFF,
					"You picked up an attack bonus."));
		else
			display_dropped_msg2(cub, print, &i);
	}
}
