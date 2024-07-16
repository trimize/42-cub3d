/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:20:00 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 14:30:23 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures2(t_cube *cub)
{
	cub->txt[14].path = ft_strdup("textures/fire_weapon_slot.xpm");
	cub->txt[15].type = NULL;
	cub->txt[15].path = ft_strdup("textures/speed_item_hud.xpm");
	cub->txt[16].type = NULL;
	cub->txt[16].path = ft_strdup("textures/attack_item_hud.xpm");
	cub->txt[17].type = NULL;
	cub->txt[17].path = ft_strdup("textures/arrow_item_hud.xpm");
	cub->txt[18].type = NULL;
	cub->txt[18].path = ft_strdup("textures/Casket.xpm");
	cub->txt[19].type = NULL;
	cub->txt[19].path = ft_strdup("textures/crosshair.xpm");
	cub->txt[20].type = NULL;
	cub->txt[20].path = ft_strdup("textures/rat.xpm");
	cub->txt[21].type = NULL;
	cub->txt[21].path = ft_strdup("textures/rat_left.xpm");
	cub->txt[22].type = NULL;
	cub->txt[22].path = ft_strdup("textures/health_potion.xpm");
	cub->txt[23].type = NULL;
	cub->txt[23].path = ft_strdup("textures/button.xpm");
	cub->txt[24].type = NULL;
	cub->txt[24].path = ft_strdup("textures/button_2.xpm");
	cub->txt[25].type = NULL;
	cub->txt[25].path = ft_strdup("textures/line_level.xpm");
}

void	init_textures(t_cube *cub)
{
	cub->txt[4].type = NULL;
	cub->txt[4].path = ft_strdup("./textures/options_menu_resized.xpm");
	cub->txt[5].type = NULL;
	cub->txt[5].path = ft_strdup("./textures/arrow_right.xpm");
	cub->txt[6].type = NULL;
	cub->txt[6].path = ft_strdup("./textures/arrow_left.xpm");
	cub->txt[7].type = NULL;
	cub->txt[7].path = ft_strdup("./textures/weapon_slot.xpm");
	cub->txt[8].type = NULL;
	cub->txt[8].path = ft_strdup("./textures/weapon_slot_white.xpm");
	cub->txt[9].type = NULL;
	cub->txt[9].path = ft_strdup("./textures/sword_weapon_slot.xpm");
	cub->txt[10].type = NULL;
	cub->txt[10].path = ft_strdup("./textures/sword_weapon_slot.xpm");
	cub->txt[11].type = NULL;
	cub->txt[11].path = ft_strdup("textures/crossbow_weapon_slot.xpm");
	cub->txt[12].type = NULL;
	cub->txt[12].path = ft_strdup("textures/shield.xpm");
	cub->txt[13].type = NULL;
	cub->txt[13].path = ft_strdup("textures/shield_weapon_slot.xpm");
	cub->txt[14].type = NULL;
	init_textures2(cub);
}
