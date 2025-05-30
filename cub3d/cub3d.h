/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:43:33 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 15:15:19 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef ESC
#  define ESC 65307
#  define W 119
#  define S 115
#  define A 97
#  define D 100
#  define RIGHT 65363
#  define LEFT 65361
# endif
# define WIDTH 1920
# define HEIGHT 1080
# define TEXWIDTH 128
# define TEXHEIGHT 128
# include <stdbool.h>

typedef struct s_game
{
	double		player_dir;
	double		speed;
	double		rot;
	double		dir[2];
	double		ray_direction[2];
	double		ray_screen_x;
	double		camera_plane[2];
	double		grid_step_dist[2];
	double		border_dist[2];
	double		perp_wall_dist;
	double		hit_point_x;
	double		tex_step;
	double		tex_pos;
	int			tex_column[2];
	int			ray_step[2];
	int			grid_pos[2];
	int			hit_axis;
	int			wall_height;
	int			wall_top_pixel;
	int			wall_bot_pixel;
	int			left;
	int			right;

}				t_game;

typedef struct s_image
{
	void		*img;
	int			*addr;
}				t_image;

typedef struct mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_image		west;
	t_image		east;
	t_image		north;
	t_image		south;
}				t_mlx_data;
typedef struct s_key
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_key;

typedef struct s_data
{
	char		**map;
	int			size;
	int			map_size;
	char		*no;
	char		*so;
	char		rot;
	int			player_xy[2];
	double		pos[2];
	char		*we;
	char		*ea;
	int			f[3];
	int			c[3];
	t_mlx_data	mlx_data;
	t_game		game;
	t_key		key;
}				t_data;
bool			check_player(t_data *data);
void			map_pars(char *file, t_data *data);
void			program_exit(char *error, int exit_code);
void			texture_check(t_data **data, int count);
void			change_texture(char *line, int *count, char **data_2);
void			change_texture_2(char *line, int *count, int *data_2);
int				line_control(char *line);
void			player_loc(t_data *data);
void			create_mlx(t_data *data);
void			mlx_free(t_data *data, char *error);
int				game_quit(t_data *data);
int				key_release(int keycode, t_data *data);
int				key_press(int keycode, t_data *data);
int				loop(t_data *data);
void			set_pixel_color(t_data *data, int x, int y, int color);
void			render_texture(t_data *data, int x, int y);
void			compute_ray_properties(t_data *data, int x);
void			compute_ray_step_and_distance(t_data *data);
void			calculate_collision_distance(t_data *data);
void			compute_wall_dimensions_and_texture(t_data *data);
void			render_column(t_data *data, int x, int y);
void			rotate(t_data *data);
void			map_dup(int fd, t_data *data, int i);
void			texture_pars(int fd, t_data *data, int count, char *line);
int				map_size(int fd, t_data *data);
#endif
