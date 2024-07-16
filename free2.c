/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:43:35 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 15:43:54 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_animations(t_cube *cub, t_txt **txts, int max)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i < max)
	{
		while (y < txts[i]->frame_max + 1)
		{
			mlx_destroy_image(cub->con, txts[i][y].img);
			y++;
		}
		free(txts[i]);
		y = 0;
		i++;
	}
	free(txts);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
