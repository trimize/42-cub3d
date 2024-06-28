/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:48:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 17:00:46 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	color_background(t_cube *cub, int length, int ray_i)
{
	int	i;

	i = (HEIGHT - length) / 2;
	while (i >= 0)
		((int *)(cub->addr))[i-- * (cub->line_length / 4) + WIDTH - ray_i] = cub->c_rgb;
	i = (HEIGHT + length) / 2;
	while (i <= HEIGHT)
			((int *)(cub->addr))[i++ * (cub->line_length / 4) + WIDTH - ray_i] = cub->f_rgb;
}

void	draw_horizontal_line(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		((int *)(cub->addr))[(HEIGHT / 2) * (cub->line_length / 4) + i] = 0xFFFFFF;
		i++;;
	}
}
void	draw_vertical_line(t_cube *cub, t_raycast *ray)
{
	int		length;
	double	dist;
	int		ray_i;
	int		color;
	int		tex_y;
	int		*txt_addr;
	double	factor;
	double	x_o;
	int		t_pix;
	int		b_pix;
	double	y_o;
	int		txt_index;

	dist = ray->dist;
	ray_i = ray->r;
	length = (int)(WALL_SIZE * (1 / dist));
	// if (length > HEIGHT) // Ensure length does not exceed screen height
	// 	length = HEIGHT;

	txt_index = search_txt(cub, ray->flag);
	txt_addr = (int *)cub->txt[txt_index].addr;
	factor = (double)cub->txt[txt_index].height / length;

	if (ray->flag == 'N' || ray->flag == 'S' || ray->flag == 'D') {
		x_o = (int)fmod(ray->rx, TILE_SIZE) * cub->txt[txt_index].width / TILE_SIZE;
		if (ray->flag == 'S') {
			x_o = cub->txt[txt_index].width - x_o - 1; // Flip for south
		}
	} else {
		x_o = (int)fmod(ray->ry, TILE_SIZE) * cub->txt[txt_index].width / TILE_SIZE;
		if (ray->flag == 'W') {
			x_o = cub->txt[txt_index].width - x_o - 1; // Flip for west
		}
	}

	t_pix = (HEIGHT / 2) - (length / 2);
	b_pix = (HEIGHT / 2) + (length / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0) // Ensure t_pix does not go beyond the top of the screen
		t_pix = 0;

	y_o = (t_pix - (HEIGHT / 2) + (length / 2)) * factor;

	while (t_pix < b_pix)
	{
		// Calculate the y coordinate of the texture
		tex_y = (int)y_o & (cub->txt[txt_index].height - 1);

		// Get the color from the texture
		color = txt_addr[tex_y * cub->txt[txt_index].width + (int)x_o];

		((int *)(cub->addr))[t_pix * (cub->line_length / 4) + WIDTH - ray_i] = color;
		y_o += factor;
		t_pix++;
	}

	// Fill the rest of the screen with background colors
	color_background(cub, length, ray_i);
}


// void	draw_vertical_line(t_cube *cub, t_raycast *ray)
// {
// 	int		i;
// 	int 	length;
// 	double	dist;
// 	int		ray_i;
// 	int		color;

// 	dist = ray->dist;
// 	ray_i = ray->r;
// 	length = (int)( WALL_SIZE * (1 / dist));
// 	i = 0;
// 	if (ray->flag == 'N' || ray->flag == 'S')
// 		color = 0xFFFFFF;
// 	else
// 		color = 0xCCCCCC;
// 	while (i < length)
// 	{
// 		if (length > HEIGHT)
// 			length = HEIGHT;
// 		// color = cub->txt[0].addr[i + (cub->txt[0].line_length / 4) + (i * 64)];
// 		((int *)(cub->addr))[((HEIGHT / 2) + i - (length / 2)) * (cub->line_length / 4) + WIDTH - ray_i] = color;
// 		i++;
// 	}
// 	color_background(cub, length, ray_i);
// }

void	render_3d(t_cube *cub, t_raycast *ray)
{
	double	dist;
	int		ray_i;

	dist = ray->dist;
	ray_i = ray->r;
	// draw_horizontal_line(cub);
	draw_vertical_line(cub, ray);
}
