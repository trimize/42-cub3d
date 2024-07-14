/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nightborne2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:35:01 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 21:38:39 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	n_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->nightborne[*i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/run/run1.xpm");
	while (y < 6)
	{

		increment_numbers(num, y + 1);
		save_txt(cub, *i, y, num);
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	n_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->nightborne[*i] = (t_txt *)malloc(12 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/attack/attack1.xpm");
	while (y < 12)
	{
		if (y == 9)
			(free(num), num = ft_strdup
				("./textures/Enemies/Nightborne/attack/attack10.xpm"));
		else if (y >= 10 && y < 19)
			increment_numbers_2(num, y - 10 + 1);
		else
			increment_numbers(num, y + 1);
		save_txt(cub, *i, y, num);
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	free(num);
	(*i)++;
}
