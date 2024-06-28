/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:40:15 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 18:26:10 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_one_pixel(char *addr, int line_length, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	((int *)(addr))[y * (line_length / 4) + x] = color;
}


double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay))));
}
void check_horizontal(t_cube *cub, t_raycast *ray)
{
    double atan;

	double px = cub->player.x * TILE_SIZE;
	double py = cub->player.y * TILE_SIZE;

    atan = -1 / tan(ray->ra);
    if (ray->ra < M_PI) // Player is looking up 
    {
        ray->ry = ((int) (py / TILE_SIZE)) * TILE_SIZE - 0.00001;
        ray->rx = px + (ray->ry - py) * atan;
        ray->yo = - TILE_SIZE;
        ray->xo = (ray->yo * atan);
        // printf("Looking up, initial ry: %f, rx: %f\n", ray->ry, ray->rx);
    }
    else if (ray->ra > M_PI) // Player is looking down
    {
        ray->ry = ((int) (py / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
        ray->rx = px + (ray->ry - py) * atan;
        ray->yo = TILE_SIZE;
        ray->xo = (ray->yo * atan);
        // printf("Looking down, initial ry: %f, rx: %f\n", ray->ry, ray->rx);
    }
    else if (ray->ra == 0 || ray->ra == M_PI) // Player is looking left or right
    {
        ray->rx = px;
        ray->ry = py;
        ray->dof = WIDTH;
        // printf("Looking left/right, rx: %f, ry: %f\n", ray->rx, ray->ry);
    }
    while (ray->dof < WIDTH)
    {
        ray->mx = (int)(ray->rx / TILE_SIZE);
        ray->my = (int)(ray->ry / TILE_SIZE);
        // if (ray->mx < 0 || ray->my < 0)
        //     return;
        // printf("Values, mx: %d, my: %d\n", ray->mx, ray->my);
        if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows && ray->mx < cub->map.cols && (cub->map.map[ray->my][ray->mx] == '1' || cub->map.map[ray->my][ray->mx] == 'D')) // Wall was hit
        {
        //     printf("Wall hit at mx: %d, my: %d\n", ray->mx, ray->my);
            ray->hx = ray->rx;
            ray->hy = ray->ry;
            ray->h_dist = dist(px, py, ray->hx, ray->hy);
	//     printf("dist : %f\n\n", ray->h_dist);
            ray->dof = WIDTH;
        }
        else
        {
        //     printf("\n\nERROR\n\n");
            ray->ry += ray->yo;
            ray->rx += ray->xo;
            ray->dof++;
        }
    }
	
	// double xx = cub->player.x * TILE_SIZE;
	// double yy = cub->player.y * TILE_SIZE;

	// double dirX = cos(cub->rr.angle_rad);
	// double dirY = sin(cub->rr.angle_rad);

	// double i = 0;

	// while((int) xx != (int) ray->rx && (int) yy != (int) ray->ry)
	// {
	// 	i += 0.01;
	// 	xx += dirX * i;
	// 	yy += dirY * i;
	// 	draw_one_pixel(cub->addr, cub->line_length, xx, yy, 0xFFFF00);
	// }
}

void	check_vertical(t_cube *cub, t_raycast *ray)
{
	double	ntan;

	double px = cub->player.x * TILE_SIZE;
	double py = cub->player.y * TILE_SIZE;

	ntan = - tan(ray->ra);
	if (ray->ra > M_PI / 2 && ray->ra < ((3 * M_PI) / 2)) //Player is looking left
	{
		ray->rx = ((int) (px / TILE_SIZE)) * TILE_SIZE - 0.00001;
		ray->ry = (py + (ray->rx - px) * ntan);
		ray->xo = - TILE_SIZE;
		ray->yo = (ray->xo * ntan);
		// printf("Looking left, initial ry: %f, rx: %f\n", ray->ry, ray->rx);
	}
	else if (ray->ra < M_PI / 2 || ray->ra > ((3 * M_PI) / 2)) //Player is looking right
	{
		ray->rx = ((int) (px / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
		ray->ry = (py + (ray->rx - px) * ntan);
		ray->xo = TILE_SIZE;
		ray->yo = (ray->xo * ntan);
		// printf("Looking right, initial ry: %f, rx: %f\n", ray->ry, ray->rx);
	}
	else if (ray->ra == 0 || ray->ra == M_PI) //Player is looking left or right
	{
		ray->rx = cub->player.x;
		ray->ry = cub->player.y;
		ray->dof = WIDTH;
		// printf("Looking left/right, rx: %f, ry: %f\n", ray->rx, ray->ry);
	}


	while (ray->dof < WIDTH)
	{
		ray->mx = (int) (ray->rx / TILE_SIZE);
		ray->my = (int) (ray->ry / TILE_SIZE);
		// if (ray->mx < 0 || ray->my < 0)
		// 	return ;
		// printf("Values , mx: %d, my: %d\n", ray->mx, ray->my);
		if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows && ray->mx < cub->map.cols && (cub->map.map[ray->my][ray->mx] == '1' || cub->map.map[ray->my][ray->mx] == 'D')) //Wall was hit
		{
			// printf("Wall hit at mx: %d, my: %d value of the wall : %c\n", ray->mx, ray->my, cub->map.map[ray->my][ray->mx]);
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->v_dist = dist(px, py, ray->vx, ray->vy);
			ray->dof = WIDTH;
			// printf("dist : %f\n\n", ray->v_dist);
		}
		else
		{
			// printf("Updating, rx: %f, ry: %f\n", ray->rx, ray->ry);
			ray->ry += ray->yo;
			ray->rx += ray->xo;
			ray->dof++;
		}
	}

	// double xx = cub->player.x * TILE_SIZE;
	// double yy = cub->player.y * TILE_SIZE;

	// double dirX = cos(cub->rr.angle_rad);
	// double dirY = sin(cub->rr.angle_rad);

	// double i = 0;

	// while((int) xx != (int) ray->rx && (int) yy != (int) ray->ry)
	// {
	// 	i += 0.01;
	// 	xx += dirX * i;
	// 	yy += dirY * i;
	// 	draw_one_pixel(cub->addr, cub->line_length, xx, yy, 0xFFFF00);
	// }
	
}

void draw_ray(char *addr, int line_length, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
            ((int *)(addr))[y0 * (line_length / 4) + x0] = color;
        }

        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void	cast_ray(t_cube *cub)
{
	t_raycast ray;
	int color;

	int	mx;
	int	my;

	ray.ra = cub->rr.angle_rad;

	// printf("\n ANGLE %f\n", ray.ra * (180 / M_PI));
	for (ray.r = 0; ray.r < WIDTH; ray.r++)
	{
		ray.ra = cub->rr.angle_rad + (ray.r - WIDTH / 2) * (cub->fov * 0.0174533 / WIDTH); // Adjust the angle based on the screen width
		if (ray.ra < 0)
			ray.ra += 2 * M_PI;
		else if (ray.ra > 2 * M_PI)
			ray.ra -= 2 * M_PI;
		ray.dof = 0;
		ray.h_dist = 9999999;
		ray.hx = cub->player.x * TILE_SIZE;
		ray.hy = cub->player.y * TILE_SIZE;
		check_horizontal(cub, &ray);
		ray.dof = 0;
		ray.v_dist = 9999999;
		ray.vx = cub->player.x * TILE_SIZE;
		ray.vy = cub->player.y * TILE_SIZE;
		check_vertical(cub, &ray);
		if (ray.v_dist < ray.h_dist)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			mx = (int)(ray.rx / TILE_SIZE);
			my = (int)(ray.ry / TILE_SIZE);
			ray.dist = ray.v_dist;
			if (cub->map.map[my][mx] == '1')
			{
				if (ray.ra > M_PI / 2 && ray.ra < ((3 * M_PI) / 2))
					ray.flag = 'W';
				else
					ray.flag = 'E';
			}
			else if (cub->map.map[my][mx] == 'D')
				ray.flag = 'D';
		}
		else
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			mx = (int)(ray.rx / TILE_SIZE);
			my = (int)(ray.ry / TILE_SIZE);
			ray.dist = ray.h_dist;
			if (cub->map.map[my][mx] == '1')
			{
				if (ray.ra < M_PI)
					ray.flag = 'N';
				else
					ray.flag = 'S';
			}
			else if (cub->map.map[my][mx] == 'D')
				ray.flag = 'D';
		}
		color = 0xFFC0CB;
		// printf("distance is %f\n", ray.v_dist);
		// draw_p_to_image(cub->addr, cub->line_length, ray.rx, ray.ry, color);

		//call the function to render the 3d
		// double xx = cub->player.x * TILE_SIZE;
		// double yy = cub->player.y * TILE_SIZE;
		render_3d(cub, &ray);
		// draw_ray(cub->addr, cub->line_length, xx, yy, ray.rx, ray.ry, color);
		

	}
}


