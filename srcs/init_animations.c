/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:23 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 18:08:14 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_keyboard(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->keyboard = (t_txt *)malloc(12 * sizeof(t_txt));
	num = ft_strdup("./textures/keyboard_assets/1.xpm");
	while (i < 12)
	{
		increment_numbers(&num, i + 1);
		cub->keyboard[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->keyboard[i].width, &cub->keyboard[i].height);
		cub->keyboard[i].addr = mlx_get_data_addr
			(cub->keyboard[i].img, &cub->keyboard[i].bits_per_pixel,
				&cub->keyboard[i].line_length,
				&cub->keyboard[i].endian);
		cub->keyboard[i].tmp_delay = 0;
		i++;
	}
	free(num);
}

void	init_game_over(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->game_over = (t_txt *)malloc(11 * sizeof(t_txt));
	num = ft_strdup("./textures/game_over/died1.xpm");
	while (i < 11)
	{
		increment_numbers(&num, i + 1);
		cub->game_over[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->game_over[i].width,
				&cub->game_over[i].height);
		cub->game_over[i].addr = mlx_get_data_addr
			(cub->game_over[i].img, &cub->game_over[i].bits_per_pixel,
				&cub->game_over[i].line_length,
				&cub->game_over[i].endian);
		cub->game_over[i].tmp_delay = 0;
		i++;
	}
	cub->game_over->delay = 20;
	cub->game_over->current_frame = 0;
	free(num);
}

void	init_main_menu_start(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->main_menu_start = (t_txt *)malloc(19 * sizeof(t_txt));
	num = ft_strdup("./textures/main_menu/start/start1.xpm");
	while (i < 19)
	{
		increment_numbers(&num, i + 1);
		cub->main_menu_start[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->main_menu_start[i].width,
				&cub->main_menu_start[i].height);
		cub->main_menu_start[i].addr = mlx_get_data_addr
			(cub->main_menu_start[i].img,
				&cub->main_menu_start[i].bits_per_pixel,
				&cub->main_menu_start[i].line_length,
				&cub->main_menu_start[i].endian);
		cub->main_menu_start[i].tmp_delay = 0;
		i++;
	}
	cub->main_menu_start->delay = 10;
	cub->main_menu_start->current_frame = 0;
	free(num);
}

void	init_main_menu_bg(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->main_menu_bg = (t_txt *)malloc(24 * sizeof(t_txt));
	num = ft_strdup("./textures/main_menu/bg1.xpm");
	while (i < 24)
	{
		increment_numbers(&num, i + 1);
		cub->main_menu_bg[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->main_menu_bg[i].width,
				&cub->main_menu_bg[i].height);
		cub->main_menu_bg[i].addr = mlx_get_data_addr
			(cub->main_menu_bg[i].img, &cub->main_menu_bg[i].bits_per_pixel,
				&cub->main_menu_bg[i].line_length,
				&cub->main_menu_bg[i].endian);
		cub->main_menu_bg[i].tmp_delay = 0;
		i++;
	}
	cub->main_menu_bg->delay = 20;
	cub->main_menu_bg->current_frame = 0;
	free(num);
}

void	init_title(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->title_screen = (t_txt *)malloc(29 * sizeof(t_txt));
	num = ft_strdup("./textures/title_screen/title1.xpm");
	while (i < 29)
	{
		increment_numbers(&num, i + 1);
		cub->title_screen[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->title_screen[i].width,
				&cub->title_screen[i].height);
		cub->title_screen[i].addr = mlx_get_data_addr
			(cub->title_screen[i].img, &cub->title_screen[i].bits_per_pixel,
				&cub->title_screen[i].line_length,
				&cub->title_screen[i].endian);
		cub->title_screen[i].tmp_delay = 0;
		i++;
	}
	cub->title_screen->delay = 70;
	cub->title_screen->current_frame = 0;
	free(num);
}
