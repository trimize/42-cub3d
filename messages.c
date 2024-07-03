/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:48:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/04 01:33:27 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	display_messages(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < cub->weapon_counter)
	{
		if (cub->weapons[i].type == '|' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 5000)
			mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a sword.");
		else if (cub->weapons[i].type == 'O' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 5000)
			mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a shield.");
		else if (cub->weapons[i].type == 'C' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 5000)
			mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a crossbow.");
		else if (cub->weapons[i].type == 'G' && cub->weapons[i].display == 0 && get_current_time() - cub->weapons[i].last_text < 5000)
			mlx_string_put(cub->con, cub->win, WIDTH / 2, HEIGHT - (HEIGHT / 4), 0xFFFFFF, "You picked up a dragon's staff.");
		i++;
	}
}