/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:48:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 15:53:18 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	color_background(t_cube *cub, int length, int ray_i)
{
	int	i;

	i = (HEIGHT - length) / 2;
	if (i < 0)
		return ;
	while (i >= 0)
		((int *)(cub->addr))[i-- * (cub->line_length / 4) + WIDTH - ray_i] = cub->c_rgb;
	i = (HEIGHT + length) / 2;
	if (i > HEIGHT)
		return ;
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
	double	y_o;
	int		t_pix;
	int		b_pix;

	dist = ray->dist;
	double x = ray->rx;
	double y = ray->ry;
	if (ray->is_door && !ray->door->is_open)
	{
		dist = ray->d_dist;
		x = ray->dx;
		y = ray->dy;
	}
	ray_i = ray->r;
	length = (int)(WALL_SIZE * (1 / dist));
	// if (length > HEIGHT) // Ensure length does not exceed screen height
	// 	length = HEIGHT;

	ray->txt = &cub->txt[search_txt(cub, ray->flag)];
	if (ray->is_door && !ray->door->is_open)
	{
		ray->txt = ray->door->txt;
	}
	txt_addr = (int *)ray->txt->addr;
	factor = (double)ray->txt->height / length;

	if (ray->flag == 'N' || ray->flag == 'S') {
		x_o = (int)fmod(x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->flag == 'S') {
			x_o = ray->txt->width - x_o - 1; // Flip for south
		}
	} else {
		x_o = (int)fmod(y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->flag == 'W') {
			x_o = ray->txt->width - x_o - 1; // Flip for west
		}
	}

	if (ray->is_door && !ray->door->is_open && (ray->door_flag == 'N' || ray->door_flag == 'S')) {
		x_o = (int)fmod(x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->door_flag == 'S') {
			x_o = ray->txt->width - x_o - 1; // Flip for south
		}
	} else if (ray->is_door && !ray->door->is_open) {
		x_o = (int)fmod(y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->door_flag == 'W') {
			x_o = ray->txt->width - x_o - 1; // Flip for west
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
		tex_y = (int)y_o & (ray->txt->height - 1);

		// Get the color from the texture
		color = txt_addr[tex_y * (ray->txt->line_length / 4) + (int)x_o];
		if (color == 0x0000FF)
		{
			dist = ray->dist;
			x = ray->rx;
			y = ray->ry;
			length = (int)(WALL_SIZE * (1 / dist));
			ray->txt = &cub->txt[search_txt(cub, ray->flag)];
			
			txt_addr = (int *)ray->txt->addr;
			factor = (double)ray->txt->height / length;

			if (ray->flag == 'N' || ray->flag == 'S') {
				x_o = (int)fmod(x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
				if (ray->flag == 'S') {
					x_o = ray->txt->width - x_o - 1; // Flip for south
				}
			} else {
				x_o = (int)fmod(y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
				if (ray->flag == 'W') {
					x_o = ray->txt->width - x_o - 1; // Flip for west
				}
			}

			// if (ray->is_door && !ray->door->is_open && (ray->door_flag == 'N' || ray->door_flag == 'S')) {
			// 	x_o = (int)fmod(x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
			// 	if (ray->door_flag == 'S') {
			// 		x_o = ray->txt->width - x_o - 1; // Flip for south
			// 	}
			// } else if (ray->is_door) {
			// 	x_o = (int)fmod(y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
			// 	if (ray->door_flag == 'W') {
			// 		x_o = ray->txt->width - x_o - 1; // Flip for west
			// 	}
			// }

			t_pix = (HEIGHT / 2) - (length / 2);
			b_pix = (HEIGHT / 2) + (length / 2);
			if (b_pix > HEIGHT)
				b_pix = HEIGHT;
			if (t_pix < 0) // Ensure t_pix does not go beyond the top of the screen
				t_pix = 0;

			y_o = (t_pix - (HEIGHT / 2) + (length / 2)) * factor;
			continue ;
		}
		((int *)(cub->addr))[t_pix * (cub->line_length / 4) + WIDTH - ray_i] = color;
		y_o += factor;
		t_pix++;
	}
	cub->rays[ray->r].txt = ray->txt;
	// Fill the rest of the screen with background colors
	color_background(cub, length, ray_i);
}
// void	draw_xpm_texture_sprite(int alpha, int x, int y, t_cube *cub, t_raycast *ray)
// {
// 	int	j;
// 	int	i;

// 	i = 0;
// 	j = 0;
// 	int screenEnd = x + cub->txt[alpha].width;
// 	if (ray->r > x && ray->r < screenEnd && cub->casket_dist <= ray->dist)
// 	{
// 		while (i < cub->txt[alpha].height)
// 		{
// 			while (j < cub->txt[alpha].width) 
// 			{
// 					if (alpha == 5 || alpha == 6)
// 					{
// 						if (((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] == 0xFFFFFF)
// 							((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
// 					}
// 					else if (alpha == 7 || alpha == 8 || alpha == 9 || alpha == 11 || alpha == 12 || alpha == 13 || alpha == 14 || alpha == 15)
// 					{
// 						if (x + j < WIDTH && y + i < HEIGHT && ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] != 0x0000FF)
// 							((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
// 					}
// 					else
// 						((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
// 					j++;
// 			}
// 			j = 0;
// 			i++;
// 		}
// 	}
// }


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

// void draw_casket(t_cube *cub, int screen_x, int casket_height) {
// 	int tex_y = 0;
//     int t_pix = (HEIGHT / 2) - (casket_height / 2);
//     int b_pix = (HEIGHT / 2) + (casket_height / 2);
//     if (b_pix > HEIGHT) b_pix = HEIGHT;
//     if (t_pix < 0) t_pix = 0;

//     double factor_y = (double)cub->txt[15].height / casket_height;
//     double y_o = 0;

//     while (y < cub->txt[15].width) {
//         int color = cub->txt[15].addr[tex_y * cub->txt[15].width + (screen_x % cub->txt[15].width)];

//         if (color != 0x000000) { // Assuming 0x000000 is the transparent color
//             ((int *)(cub->addr))[y * (cub->line_length / 4) + screen_x] = color;
//         }
//         y_o += 1;
// 		y++;
//     }
// }


// void render_props(t_cube *cub, t_raycast *ray) {
//     double casket_dist = dist(cub->player.x, cub->player.y, cub->casket_x, cub->casket_y);
//     double angle_to_casket = atan2(cub->casket_y - cub->player.y, cub->casket_x - cub->player.x);
//     double angle_diff = angle_to_casket - cub->rr.angle_rad;

//     if (angle_diff < -M_PI) angle_diff += 2 * M_PI;
//     if (angle_diff > M_PI) angle_diff -= 2 * M_PI;

//     if (fabs(angle_diff) < (cub->fov * 0.0174533 / 2)) {
//         int screen_x = (WIDTH / 2) + (angle_diff * (WIDTH / (cub->fov * 0.0174533)));
//         int casket_height = 1000 / casket_dist;
//         // int casket_width = casket_height; // Assuming the casket is square

//         if (ray->dist > casket_dist) {
// 			draw_casket(cub, screen_x, casket_height);
//         }
//     }
// }


// void	draw_sprite(t_cube *cub, t_raycast *ray)
// {
// 	int	spx = 2 * TILE_SIZE;
// 	int	spy = 2 * TILE_SIZE;
	
// 	double sx = spx - (cub->player.x * TILE_SIZE);
// 	double sy = spy - (cub->player.y * TILE_SIZE);
// 	double sz = 60;

// 	double CS = cos(cub->rr.angle_rad);
// 	double SN = sin(cub->rr.angle_rad);
// 	double a = sy * CS + sx * SN;
// 	double b = sx * CS - sy * SN;

// 	sx = (a * 1280 / b) + (WIDTH / 2);
// 	sy = (sz * 1280 / b) + (HEIGHT / 2);
	
// 	if (ray->r >= sx && ray->r <= sx + cub->txt[15].width && cub->casket_dist <= ray->dist)
// 		printf("ray index: %d raystart: %d rayend: %d\n", (int) ray->r, (int) sx, (int) (sx + cub->txt[15].width));
//     // if (b > 0)
// 	// {
//         if (sx > 0 && sx < WIDTH) {
//             // draw_xpm_texture_sprite(15, (int) sx, (int) sy, cub, ray);
// 			draw_square_to_image(cub->addr, cub->line_length, sx, sy, YELLOW);
//         }
//     // }
// }

void draw_enemy(t_cube *cub, t_enemy *enemy)
{
	double scale = enemy->scale;
	double z_index = enemy->z_index;
    double spriteX = (enemy->x) - (cub->player.x);
    double spriteY = (enemy->y) - (cub->player.y);

	double fovRadians = cub->fov * (M_PI / 180.0);
	double planeLength = tan(fovRadians / 2.0);

    double dirX = cos(-cub->rr.angle_rad);
    double dirY = sin(-cub->rr.angle_rad);

    double planeX = -dirY * planeLength;
    double planeY = dirX * planeLength;

    double invDet = 1.0 / (planeX * dirY - dirX * planeY); // required for correct matrix multiplication

    double transformX = invDet * (dirY * spriteX - dirX * spriteY) * scale;
    double transformY = invDet * (-planeY * spriteX + planeX * spriteY) * scale; // this is actually the depth inside the screen, that what Z is in 3D

    int spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	int scaledZPosition = (int)(z_index / transformY);

    // calculate height of the sprite on screen
    int spriteHeight = abs((int) (HEIGHT / (transformY))); // using 'transformY' instead of the real distance prevents fisheye
    // calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

	double aspectRatio = (double)enemy->txt.width / (double)enemy->txt.height;
    // calculate width of the sprite
    // int spriteWidth = abs((int) (HEIGHT / (transformY)));
    int spriteWidth = abs((int) (spriteHeight * aspectRatio));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    enemy->draw_start = drawStartX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    enemy->draw_end = drawEndX;
    if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

    // loop through every vertical stripe of the sprite on screen
	// int stripe = index;
	// if (stripe >= drawStartX && stripe < drawEndX)
	// {
		for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
			if (cub->rays[WIDTH - stripe].dist < enemy->dist || (cub->rays[WIDTH - stripe].is_door && !cub->rays[WIDTH - stripe].door->is_open && enemy->dist > cub->rays[WIDTH - stripe].d_dist))
				continue ;
			// printf("\ndrawStart %d, drawEnd %d and ray %d\n", drawStartX, drawEndX, stripe);
			int texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * enemy->txt.width / spriteWidth) / 256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH) {
				for (int y = drawStartY; y < drawEndY; y++) { // for every pixel of the current stripe
					int d = (y - scaledZPosition) * 256 - HEIGHT * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
					int texY = ((d * enemy->txt.height) / spriteHeight) / 256;

					// int color = cub->txt[15].addr[texY * (cub->txt[15].line_length / 4) + texX];
					int color = *(int*) (enemy->txt.addr + ((texX + (texY * enemy->txt.width)) * (enemy->txt.bits_per_pixel / 8)));

					if ((color) != 0x0000FF) { // Assuming 0x000000 is the transparent color
						// if (index > 120 && stripe < 126)
						// {
						// 	printf("HAHAH %d and %d\n", y, stripe);
						// 	color = YELLOW;
						// }
						((int *)(cub->addr))[y * (cub->line_length / 4) + stripe] = color;
						// mlx_pixel_put(cub->con, cub->win, index, y, color);
					}
				}
			}
		// }
	}
}

void	draw_weapon(t_cube *cub, int index)
{
    double spriteX = (cub->weapons[index].x) - (cub->player.x);
    double spriteY = (cub->weapons[index].y) - (cub->player.y);

	double fovRadians = cub->fov * (M_PI / 180.0);
	double planeLength = tan(fovRadians / 2.0);

    double dirX = cos(-cub->rr.angle_rad);
    double dirY = sin(-cub->rr.angle_rad);

    double planeX = -dirY * planeLength;
    double planeY = dirX * planeLength;

    double invDet = 1.0 / (planeX * dirY - dirX * planeY); // required for correct matrix multiplication

    double transformX = invDet * (dirY * spriteX - dirX * spriteY) * 2;
    double transformY = invDet * (-planeY * spriteX + planeX * spriteY) * 2; // this is actually the depth inside the screen, that what Z is in 3D

    int spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	int zPosition = 800;
	int scaledZPosition = (int)(zPosition / transformY);

    // calculate height of the sprite on screen
    int spriteHeight = abs((int) (HEIGHT / (transformY))); // using 'transformY' instead of the real distance prevents fisheye
    // calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

	double aspectRatio = (double)cub->weapons[index].txt->width / (double)cub->weapons[index].txt->height;
    // calculate width of the sprite
    // int spriteWidth = abs((int) (HEIGHT / (transformY)));
    int spriteWidth = abs((int) (spriteHeight * aspectRatio));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

    // loop through every vertical stripe of the sprite on screen
	// int stripe = index;
	// if (stripe >= drawStartX && stripe < drawEndX)
	// {
		for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
			if (cub->rays[WIDTH - stripe].dist < cub->weapons[index].dist || (cub->rays[WIDTH - stripe].is_door && !cub->rays[WIDTH - stripe].door->is_open && cub->weapons[index].dist > cub->rays[WIDTH - stripe].d_dist))
				continue ;
			// printf("\ndrawStart %d, drawEnd %d and ray %d\n", drawStartX, drawEndX, stripe);
			int texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * cub->weapons[index].txt->width / spriteWidth) / 256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH) {
				for (int y = drawStartY; y < drawEndY; y++) { // for every pixel of the current stripe
					int d = (y - scaledZPosition) * 256 - HEIGHT * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
					int texY = ((d * cub->weapons[index].txt->height) / spriteHeight) / 256;

					// int color = cub->txt[15].addr[texY * (cub->txt[15].line_length / 4) + texX];
					int color = *(int*) (cub->weapons[index].txt->addr + ((texX + (texY * cub->weapons[index].txt->width)) * (cub->weapons[index].txt->bits_per_pixel / 8)));

					if ((color) != 0x0000FF) { // Assuming 0x000000 is the transparent color
						// if (index > 120 && stripe < 126)
						// {
						// 	printf("HAHAH %d and %d\n", y, stripe);
						// 	color = YELLOW;
						// }
						((int *)(cub->addr))[y * (cub->line_length / 4) + stripe] = color;
						// mlx_pixel_put(cub->con, cub->win, index, y, color);
					}
				}
			}
		// }
	}
}

void	draw_item(t_cube *cub, t_item item)
{
    double spriteX = (item.x) - (cub->player.x);
    double spriteY = (item.y) - (cub->player.y);

	double fovRadians = cub->fov * (M_PI / 180.0);
	double planeLength = tan(fovRadians / 2.0);

    double dirX = cos(-cub->rr.angle_rad);
    double dirY = sin(-cub->rr.angle_rad);

    double planeX = -dirY * planeLength;
    double planeY = dirX * planeLength;

    double invDet = 1.0 / (planeX * dirY - dirX * planeY); // required for correct matrix multiplication

    double transformX = invDet * (dirY * spriteX - dirX * spriteY) * 2;
    double transformY = invDet * (-planeY * spriteX + planeX * spriteY) * 2; // this is actually the depth inside the screen, that what Z is in 3D

    int spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	int zPosition = 800;
	int scaledZPosition = (int)(zPosition / transformY);

    // calculate height of the sprite on screen
    int spriteHeight = abs((int) (HEIGHT / (transformY))); // using 'transformY' instead of the real distance prevents fisheye
    // calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

	double aspectRatio = (double)item.txt->width / (double)item.txt->height;
    // calculate width of the sprite
    // int spriteWidth = abs((int) (HEIGHT / (transformY)));
    int spriteWidth = abs((int) (spriteHeight * aspectRatio));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

    // loop through every vertical stripe of the sprite on screen
	// int stripe = index;
	// if (stripe >= drawStartX && stripe < drawEndX)
	// {
		for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
			if (cub->rays[WIDTH - stripe].dist < item.dist || (cub->rays[WIDTH - stripe].is_door && !cub->rays[WIDTH - stripe].door->is_open && item.dist > cub->rays[WIDTH - stripe].d_dist))
				continue ;
			// printf("\ndrawStart %d, drawEnd %d and ray %d\n", drawStartX, drawEndX, stripe);
			int texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * item.txt->width / spriteWidth) / 256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH) {
				for (int y = drawStartY; y < drawEndY; y++) { // for every pixel of the current stripe
					int d = (y - scaledZPosition) * 256 - HEIGHT * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
					int texY = ((d * item.txt->height) / spriteHeight) / 256;

					// int color = cub->txt[15].addr[texY * (cub->txt[15].line_length / 4) + texX];
					int color = *(int*) (item.txt->addr + ((texX + (texY * item.txt->width)) * (item.txt->bits_per_pixel / 8)));

					if ((color) != 0x0000FF) { // Assuming 0x000000 is the transparent color
						// if (index > 120 && stripe < 126)
						// {
						// 	printf("HAHAH %d and %d\n", y, stripe);
						// 	color = YELLOW;
						// }
						((int *)(cub->addr))[y * (cub->line_length / 4) + stripe] = color;
						// mlx_pixel_put(cub->con, cub->win, index, y, color);
					}
				}
			}
		// }
	}
}

void	draw_sprite(t_cube *cub, t_txt *txt, double scale, int z_index)
{
    double spriteX = cub->explosion->x - (cub->player.x);
    double spriteY = cub->explosion->y - (cub->player.y);

    int distance = dist(cub->explosion->x, cub->explosion->y, cub->player.x, cub->player.y);

	double fovRadians = cub->fov * (M_PI / 180.0);
	double planeLength = tan(fovRadians / 2.0);

    double dirX = cos(-cub->rr.angle_rad);
    double dirY = sin(-cub->rr.angle_rad);

    double planeX = -dirY * planeLength;
    double planeY = dirX * planeLength;

    double invDet = 1.0 / (planeX * dirY - dirX * planeY); // required for correct matrix multiplication

    double transformX = invDet * (dirY * spriteX - dirX * spriteY) * scale;
    double transformY = invDet * (-planeY * spriteX + planeX * spriteY) * scale; // this is actually the depth inside the screen, that what Z is in 3D

    int spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	int zPosition = z_index;
	int scaledZPosition = (int)(zPosition / transformY);

    // calculate height of the sprite on screen
    int spriteHeight = abs((int) (HEIGHT / (transformY))); // using 'transformY' instead of the real distance prevents fisheye
    // calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
    if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

	double aspectRatio = (double)txt->width / (double)txt->height;
    // calculate width of the sprite
    // int spriteWidth = abs((int) (HEIGHT / (transformY)));
    int spriteWidth = abs((int) (spriteHeight * aspectRatio));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

    // loop through every vertical stripe of the sprite on screen
	// int stripe = index;
	// if (stripe >= drawStartX && stripe < drawEndX)
	// {
		for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
			if (cub->rays[WIDTH - stripe].dist < distance)
				continue ;
			// printf("\ndrawStart %d, drawEnd %d and ray %d\n", drawStartX, drawEndX, stripe);
			int texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * txt->width / spriteWidth) / 256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH) {
				for (int y = drawStartY; y < drawEndY; y++) { // for every pixel of the current stripe
					int d = (y - scaledZPosition) * 256 - HEIGHT * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
					int texY = ((d * txt->height) / spriteHeight) / 256;

					// int color = cub->txt[15].addr[texY * (cub->txt[15].line_length / 4) + texX];
					int color = *(int*) (txt->addr + ((texX + (texY * txt->width)) * (txt->bits_per_pixel / 8)));

					if ((color) != 0x0000FF) { // Assuming 0x000000 is the transparent color
						// if (index > 120 && stripe < 126)
						// {
						// 	printf("HAHAH %d and %d\n", y, stripe);
						// 	color = YELLOW;
						// }
						((int *)(cub->addr))[y * (cub->line_length / 4) + stripe] = color;
						// mlx_pixel_put(cub->con, cub->win, index, y, color);
					}
				}
			}
		// }
	}
}

// void draw_sprite(t_cube *cub, t_raycast *ray) {
//     double spriteX = (cub->casket_x) - (cub->player.x);
//     double spriteY = (cub->casket_y) - (cub->player.y);

//     double fovRadians = cub->fov * (M_PI / 180.0);
//     double planeLength = tan(fovRadians / 2.0);

//     double dirX = cos(-cub->rr.angle_rad);
//     double dirY = sin(-cub->rr.angle_rad);

//     double planeX = -dirY * planeLength;
//     double planeY = dirX * planeLength;

//     double invDet = 1.0 / (planeX * dirY - dirX * planeY); // required for correct matrix multiplication

//     double transformX = invDet * (dirY * spriteX - dirX * spriteY) * 2;
//     double transformY = invDet * (-planeY * spriteX + planeX * spriteY) * 2; // this is actually the depth inside the screen, that what Z is in 3D

//     int spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

//     int zPosition = 800;
//     int scaledZPosition = (int)(zPosition / transformY);

//     // calculate height of the sprite on screen
//     int spriteHeight = abs((int) (HEIGHT / (transformY))); // using 'transformY' instead of the real distance prevents fisheye
//     // calculate lowest and highest pixel to fill in current stripe
//     int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
//     if (drawStartY < 0) drawStartY = 0;
//     int drawEndY = spriteHeight / 2 + HEIGHT / 2 + scaledZPosition;
//     if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

//     double aspectRatio = (double)cub->txt[15].width / (double)cub->txt[15].height;
//     // calculate width of the sprite
//     int spriteWidth = abs((int) (spriteHeight * aspectRatio));
//     int drawStartX = -spriteWidth / 2 + spriteScreenX;
//     if (drawStartX < 0) drawStartX = 0;
//     int drawEndX = spriteWidth / 2 + spriteScreenX;
//     if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

//     // Debug prints
//     printf("spriteScreenX: %d, drawStartX: %d, drawEndX: %d, ray->r: %d\n", spriteScreenX, drawStartX, drawEndX, ray->r);

//     // loop through every vertical stripe of the sprite on screen
//     if (ray->r >= drawStartX && ray->r <= drawEndX && ray->dist <= cub->casket_dist) {
//         int texX = (int) (256 * (ray->r - (-spriteWidth / 2 + spriteScreenX)) * cub->txt[15].width / spriteWidth) / 256;
        
//         // Debug print
//         printf("texX: %d\n", texX);

//         if (transformY > 0 && ray->r > 0 && ray->r < WIDTH) {
//             for (int y = drawStartY; y < drawEndY; y++) { // for every pixel of the current stripe
//                 int d = (y - scaledZPosition) * 256 - HEIGHT * 128 + spriteHeight * 128;
//                 int texY = ((d * cub->txt[15].height) / spriteHeight) / 256;

//                 int color = *(int*) (cub->txt[15].addr + ((texX + (texY * cub->txt[15].width)) * (cub->txt[15].bits_per_pixel / 8)));

//                 if ((color) != 0x0000FF) { // Assuming 0x000000 is the transparent color
//                     ((int *)(cub->addr))[y * (cub->line_length / 4) + ray->r] = color;
//                 }
//             }
//         }
//     }
// }

void	render_3d(t_cube *cub, t_raycast *ray)
{
	// draw_horizontal_line(cub);
	draw_vertical_line(cub, ray);
	// draw_sprite(cub, ray);
}
