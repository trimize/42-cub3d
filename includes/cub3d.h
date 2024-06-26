/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:40 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/26 17:23:51 by mbrandao         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720
# define PLAYER_SPEED 0.006
# define PLAYER_SIZE 2
# define TILE_SIZE 10
# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500
# define DARK_GREEN 0x013220
# define L_CONTROL_KEY 65507

extern int	mouse_clicked;

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

typedef struct s_rotation_ray
{
	double	ray_x[50];
	double	ray_y[50];
	double	angle_rad;
	double	pdx;
	double	pdy;
}	t_rr;

typedef struct s_raycast
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	hx;
	double	hy;
	double	h_dist;
	double	vx;
	double	vy;
	double	v_dist;
	double	dist;
}	t_raycast;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		mouse_l;
}	t_key;

typedef struct s_cube
{
	t_map		map;
	t_txt		txt[6];
	t_player	player;
	t_key		key;
	t_rr		rr;
	void		*con;
	void		*win;
	void		*options_menu;
	void		*alphabet[26];
	void		*numbers[10];
	void		*arr_r_options;
	void		*arr_l_options;
	char		*addr;
	int		line_length;
	int		fov;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
	int			start;
	int			mouse_x;
	int			mouse_y;
	int			option_bool;
	int			mouse_click;
	int			sensi;
	double			p_rotation;			
}	t_cube;

char	**ft_split(char const *s, char const c);
char	**read_file(char *path);
void	save_file(t_cube *cub, char **file);
void	freetab(char **tab);
t_cube	*call_cub(void);
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
void	player_rotation_init(t_cube *cub);
void	rotate_player(t_cube *cub, double dir);
void	player_rotation_keys(int key, t_cube *cub);
void	cast_ray(t_cube *cub);
void	draw_p_to_image(char *addr, int line_length, int x, int y, int color);
void	render_3d(t_cube *cub, double dist, int ray_i);

#endif