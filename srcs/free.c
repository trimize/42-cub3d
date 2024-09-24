/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:32:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_free(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->txt[i].type)
			free(cub->txt[i].type);
		if (cub->txt[i].path)
			free(cub->txt[i].path);
		i++;
	}
	free(cub->txt);
	if (cub->weapon_counter)
		free(cub->weapons);
	if (cub->enemy_counter)
	{
		free(cub->all_enemies);
		free(cub->dropped_items);
	}
	if (cub->items_counter)
		free(cub->items);
	if (cub->door_counter)
		free(cub->doors);
	(free(cub->rays), freetab(cub->map.map));
	(free(cub->path), exit(1));
}

void	free_stuff(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->txt[i].type)
			free(cub->txt[i].type);
		if (cub->txt[i].path)
			free(cub->txt[i].path);
		i++;
	}
}

void	free_stuff2(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->txt[i].type)
			free(cub->txt[i].type);
		if (cub->txt[i].path)
		{
			free(cub->txt[i].path);
			mlx_destroy_image(cub->con, cub->txt[i].img);
			cub->txt[i].img = NULL;
		}
		i++;
	}
}

void	free_txt(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		if (cub->txt[i].type)
			free(cub->txt[i].type);
		if (cub->txt[i].path)
		{
			free(cub->txt[i].path);
			if (cub->txt[i].img)
				mlx_destroy_image(cub->con, cub->txt[i].img);
		}
		i++;
	}
	free(cub->txt);
}

void	free_imgs(t_cube *cub, t_txt *txts, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		mlx_destroy_image(cub->con, txts[i].img);
		i++;
	}
	free(txts);
}
