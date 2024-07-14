/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:49:30 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 20:49:43 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	mouse_events(int key)
{
	if (key == 1)
		(call_cub())->key.mouse_l = 1;
	return (1);
}

void	mouse_rotate(t_cube *cub)
{
	int	m_x;

	m_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->con, cub->win, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x >= WIDTH - (WIDTH / 10) || cub->mouse_x <= WIDTH / 5)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (cub->mouse_y >= HEIGHT - (HEIGHT / 10) || cub->mouse_x <= HEIGHT / 5)
		mlx_mouse_move(cub->con, cub->win, WIDTH / 2, HEIGHT / 2);
	if (m_x != cub->mouse_x)
	{
		if (cub->mouse_x > m_x)
			rotate_player(cub, -(cub->p_rotation));
		else if (cub->mouse_x < m_x)
			rotate_player(cub, cub->p_rotation);
	}
}
