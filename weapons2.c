/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:39:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 16:39:16 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	shield_handler(t_cube *cub)
{
	if (cub->weapons_in_slot[cub->player.weapon - 1] == 3)
		draw_xpm_texture(12, WIDTH / 1.8, HEIGHT / 1.9, cub);
}
