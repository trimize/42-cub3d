/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:32:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 16:21:35 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"

void	exit_free(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(cub->txt[i].type);
		free(cub->txt[i].path);
		i++;
	}
	freetab(cub->map.map);
	if (cub->level)
		free(cub->path);
	exit(1);
}

void	free_stuff(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
		(free(cub->txt[i].type), free(cub->txt[i].path), i++);
	freetab(cub->map.map);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
