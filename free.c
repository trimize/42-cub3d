/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: to <to@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:32:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/18 19:28:02 by to               ###   ########.fr       */
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
