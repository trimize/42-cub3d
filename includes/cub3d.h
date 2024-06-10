/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:40 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/10 21:17:49 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/time.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 800
# define FOV 60
# define PLAYER_SPEED 4
# define TILE_SIZE 30
# define MAP_SIZE 5

typedef struct s_txt
{
	char	*type;
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_txt;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	double	dir;
}	t_player;

typedef struct s_cube
{
	t_map		map;
	t_txt		txt[6];
	t_player	player;
	void		*con;
	void		*win;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
}	t_cube;

char	**ft_split(char const *s, char const c);
char	**read_file(char *path);
void	save_file(t_cube *cub, char **file);
void	freetab(char **tab);
int		tablen(char **tab);
int		get_fd(char *file);
int		ft_equalstr(char const *str, char const *str2);
void	variables_checker(t_cube *cub);
int		first_and_last_checker(char **map);
int		char_checker(char *line);
int		space_checker_horizontal(char **map);
int		space_checker_vertical(char **map);
void	exit_free(t_cube *cub);
void	free_stuff(t_cube *cub);
void	map_filler(t_map *map);
int		check_cub(char *file);
void	window_init(t_cube *cub);
void	fill_player(t_cube *cub);
void	player_checker(t_cube *cub);
void	load_textures(t_cube *cub);
void	init_rays(t_cube *cub);

#endif