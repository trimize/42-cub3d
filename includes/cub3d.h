/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:40 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/11 21:31:49 by trimize          ###   ########.fr       */
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
# define PLAYER_SIZE 2
# define ENEMY_SPEED 0.01
# define TILE_SIZE 64
# define WALL_SIZE 80000

# define L_CONTROL_KEY 65507 //Replace

# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500
# define DARK_GREEN 0x013220

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
	int		tmp_delay;
	int		delay;
	int		current_frame;
	int		frame_max;
	int		x;
	int		y;
	int		launched;
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
	char	flag;
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
	int	hp;
	int	weapon;
	int	arrows;
	int	atk;
	int	atk_item_amount;
	int	speed_item_amount;
	int	hit;
	int	last_atk;
	double	speed;
}	t_player;

typedef struct s_enemy
{
	t_txt	txt;
	double	x;
	double	y;
	double	dist;
	long int		last_attack;
	int	hp;
	int	hurt;
	int	attacking_bool;
	int	draw_start;
	int	draw_end;
	int	dead;
	double	scale;
	int	z_index;
	int	atk_max_frame;
	int	death_max_frame;
	int	hurt_max_frame;
	int	idle_max_frame;
	int	run_max_frame;
	int	attack_range;
}	t_enemy;

typedef struct s_item
{
	t_txt	*txt;
	double	x;
	double	y;
	double	dist;
	char	type;
	int		display;
	long int	last_text;
}	t_item;


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
	t_txt		*txt;
	t_txt		*sword_ani;
	t_txt		*crossbow;
	t_txt		*dragon;
	t_txt		*explosion;
	t_txt		*nums;
	t_txt		*hp_frame;
	t_txt		*abc;
	t_txt		casket;
	t_txt		*title_screen;
	t_txt		*main_menu_bg;
	t_txt		*main_menu_assets;
	t_txt		*main_menu_start;
	t_txt		*game_over;
	t_txt		*keyboard;
	t_txt		**nightborne;
	t_txt		**skeleton;
	t_txt		**warrior;
	t_txt		**skullwolf;
	t_txt		**s_warrior;
	t_txt		**plague_doctor;
	t_txt		**cute_wolf;
	t_player	player;
	t_key		key;
	t_rr		rr;
	t_raycast	*rays;
	t_enemy		enemies[8];
	t_item		*weapons;
	void		*con;
	void		*win;
	char		*addr;
	void		*img;
	int			retry;
	int			enemies_nb;
	int			title_bool;
	int			bg_bool;
	int			fov;
	int			line_length;
	int			f_rgb;
	int			c_rgb;
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
	int			weapon_counter;
	int			items_counter;
	int			sensi;
	int			speed;
	int			weapons_in_slot[4];
	int			tuto;
	double			fade_factor;
	double			p_rotation;
	double		casket_x;
	double		casket_y;
	double		casket_dist;
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
long int	get_current_time(void);
void	player_checker(t_cube *cub);
void	load_textures(t_cube *cub, t_txt *txt, int num);
void	init_rays(t_cube *cub);
void	player_rotation_init(t_cube *cub);
void	rotate_player(t_cube *cub, double dir);
void	player_rotation_keys(int key, t_cube *cub);
void	cast_ray(t_cube *cub, int index);
void	items_parsing(t_cube *cub);
void	draw_p_to_image(char *addr, int line_length, int x, int y, int color);
void	render_3d(t_cube *cub, t_raycast *ray);
int		rgb_to_hex(int r, int g, int b);
void	draw_player_to_image(t_cube *cub, char *addr, int line_length);
void	draw_map_to_image(t_cube *cub, char *addr, int line_length);
int		search_txt(t_cube *cub, char c);
double	dist(double ax, double ay, double bx, double by);

void	draw_xpm_animation(int alpha, int x, int y, t_cube *cub, t_txt *txt);
void	draw_xpm_hp(int alpha, int x, int y, t_cube *cub);
void	draw_xpm_texture(int alpha, int x, int y, t_cube *cub);
void	draw_xpm_number(int alpha, int x, int y, t_cube *cub);
void	draw_xpm_alpha(int alpha, int x, int y, t_cube *cub);

int		update_animation(t_cube *cub);
void	animate_health_bar(t_cube *cub, int limite);
char	*to_str(int n);
void	increment_numbers(char *str, int index);
void	increment_numbers_2(char *str, int index);
void	increment_alphabet(char *str, int index);
void	hp_handler(t_cube *cub);
void	init_w_slots(t_cube *cub);
void	weapon_slot_handler(t_cube *cub);
void	sword_handler(t_cube *cub);
void	update_animation_crossbow(t_cube *cub);
void	crossbow_handler(t_cube *cub);
void	shield_handler(t_cube *cub);
void	dragon_handler(t_cube *cub);
void	update_animation_dragon(t_cube *cub);
void	explosion_handler(t_cube *cub);
void	update_animation_explosion(t_cube *cub);
void	title_handler(t_cube *cub);
void	bg_handler(t_cube *cub);
void	start_handler(t_cube *cub);
void	died_handler(t_cube *cub);
void	update_dist(t_cube *cub);

void	speed_option(t_cube *cub);
void	sensi_option(t_cube *cub);
void	fov_option(t_cube *cub);
void	draw_options(t_cube *cub);
void	fade_to_black(t_cube *cub, double fade_factor, int bits_per_pixel);
t_cube	*call_cub(void);

void	draw_square_to_image(char *addr, int line_length, int x, int y, int color); //DELETE
//void	draw_sprite(t_cube *cub, int index);
void	render_game(t_cube *cub);
void draw_enemy(t_cube *cub, t_enemy *enemy, double scale, int z_index);
void	draw_weapon(t_cube *cub, int index);
void	display_messages(t_cube *cub);
void	check_pick_up(t_cube *cub);
t_txt	enemy_animation_handler(t_txt *txt, int max_frame);
t_txt	enemy_animation_atk(t_cube *cub, t_txt *txt, int index, int dist);
t_txt	enemy_animation_death(t_cube *cub, t_txt *txt, int index, int max_frame);
void	draw_sprite(t_cube *cub, t_txt *txt, int x, int y, double scale, int z_index);
void	explosion_sprite(t_cube *cub);
t_txt	enemy_animation_hurt(t_cube *cub, t_txt *txt, int index, int max_frame);
void	start_keys(t_cube *cub);
void	init_enemies(t_cube *cub);

#endif