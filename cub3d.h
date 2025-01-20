/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:52 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/12/10 17:25:59 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"

# define WIDTH 1400
# define HEIGHT 850
# define FOV (M_PI / 3)

#define SPEED 0.1
#define RSPEED 0.06

/*	color constants	*/
# define RED 0x00FF0000
# define DARKER_RED 0x00D90000
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define PINK 0xFFC0CB
# define BROWN 0xA52A2A

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ESCAPE 53
# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_mat_pos
{
	int	x;
	int	y;
}
	t_mat_pos;

typedef struct	s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct	s_grid
{
	int	x;
	int	y;
}	t_grid;

typedef struct s_text
{
	t_img	img;
	char	type;
	char	*path;
	int		width;
	int		height;
	int		*pixel_array;
}	t_text;

typedef struct s_map
{
	char		**matrix;
	t_text		no_text;
	t_text		so_text;
	t_text		we_text;
	t_text		ea_text;
	int			ceiling_color;
	int			floor_color;
	int			grid_size;
	int			mini_grid_size;
	int			info;
}	t_map;
           
typedef	struct s_player
{
	t_pos		pos;
	t_pos		dir;
	t_mat_pos	mat_pos;
	char		starting_dir;
	int			rotating_left;
	int			rotating_right;
	int			moving_left;
	int			moving_right;
	int			moving_forward;
	int			moving_back;
	double		radius;
	double		speed;
}	t_player;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_img		img2;
	int			width;
	int			height;
}	t_data;

typedef struct s_dda
{
    int     x;
    int     y;
    double  inc_x;
    double  inc_y;
    double  delta_x;
    double  delta_y;
    double  len_x;
    double  len_y;
}   t_dda;

typedef struct s_ray
{
	t_pos	dir;
	double	len;
	double	perp_len;
	int		wall;
	double	wall_intercept;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	t_text	text;
	int		text_x;
	int		text_y;
}	t_ray;

/*get_next_line*/
char	*get_next_line(int fd);

/*misc*/
void	*free_map(t_map *map);
void	*free_data(t_data *data);
void	*free_array_of_pointers(void **array);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		mlx_get_color(t_img *img, int x, int y);

/*parsing*/
int		ft_strcmp(char *s1, char *s2);
void	no_other_ws(char *line);
int		init_map(t_data *data, int fd);
int		row_len(char **map);
char	**add_line_to_map(char **map, char *line);
int		parser(t_data *data, int fd);
int		rgb_parser(t_map *map, char *type, char *str);
int		texture_parser(t_map *map, char *orientation, char *path);
int		map_parser(t_data *data);
int		is_valid_map(char **map);
void	player_parser(t_data *data);
void	calculate_grid_size(t_data *data);

/*events*/
int		handle_keys(int key, t_data *data);
int		handle_rkeys(int key, t_data *data);
int		handle_destroy(t_data *data);
void	handle_rotation(int key, t_data *data);
void	handle_stop_rotation(int key, t_data *data);
void	handle_movement(int key, t_data *data);
void	handle_stop_movement(int key, t_data *data);
void	rotate(t_data *data, double rad);
void    move(t_data *data, int key, double distance);
int		game_loop(t_data *data);
int		minimap_loop(t_data *data);
void	update_player_pos(t_data *data, int color);

int		is_valid_map(char **map);

/*render minimap*/
void    render_minimap(t_data *data);

void    mlx_draw_square(t_data *data, int x, int y, int color);
void    mlx_draw_circle(t_data *data, t_player *player, int color);
void	mlx_draw_line(t_data *data, t_player *player, int color);

void    raycaster(t_data *data);
void	castRay(t_data *data, t_player *player);
void  dda(t_data *data, t_ray *ray);
#endif