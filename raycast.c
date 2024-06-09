/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:40:15 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/09 18:07:22 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_rays(t_cube *cub)
{
	cub->ray = (t_ray *) malloc (sizeof(t_ray) * WIDTH);
	if (!cub->ray)
	{
		printf("Error\nCouldn't allocate memory for rays.\n");
		exit_free(cub);
	}
}
