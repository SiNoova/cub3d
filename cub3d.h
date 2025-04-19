/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:10 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/08 15:41:57 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"

# define NO 11
# define SO 12
# define WE 13
# define EA 14
# define F 15
# define C 16
# define TILESIZE 64
# define PLAYER_RADIUS 9.14285714286
# define STRAFE_SPEED 4
# define FOV 60
# define W_HEIGHT 700
# define WIN_WIDTH 1000

# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define RED 0xFF0000FF
# define CYAN 0x00FFFFFF
# define LIGHT_GREEN 0x008080FF

# define MINI_MAP_WH 200

typedef struct s_trash
{
	void			*to_free;
	struct s_trash	*next;
}	t_trash;

typedef struct s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_rgb;

typedef struct s_point
{
	double	x;
	double	y;
	int		hori_or_vert;
}	t_point;

typedef struct s_player
{
	long	x;
	long	y;
	double	radius;
	int		turn_direction;
	int		walk_direction;
	double	rotation_angle;
	int		move_speed;
	double	rotation_speed;
	int		strafe_direction;
	int		spawn_direction;
	bool	up;
	bool	left;
	bool	down;
	bool	right;
}	t_player;

typedef struct s_sprite
{
	mlx_texture_t	*textures[13];
	mlx_image_t		*img;
}	t_sprite;

typedef struct s_cub
{
	char			*no;
	char			*we;
	char			*so;
	char			*ea;
	char			*color_floor;
	char			*color_ceiling;
	t_rgb			*ceiling;
	t_rgb			*floor;
	char			**map;
	t_trash			*garbage;
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_img;
	double			window_height;
	double			window_width;
	t_player		*player;
	double			closest_inter_x;
	double			closest_inter_y;
	double			hor_closest_inter_x;
	double			hor_closest_inter_y;
	mlx_texture_t	*no_pic_data;
	mlx_texture_t	*so_pic_data;
	mlx_texture_t	*we_pic_data;
	mlx_texture_t	*ea_pic_data;
	mlx_texture_t	*door_pic_data;
	t_sprite		sprites;
	int				x_mouse;
	int				y_mouse;
	int				map_fd;
	bool			sprites_ready;
}	t_cub;

typedef struct s_pinfo
{
	int		new_x;
	int		new_y;
	int		step;
	double	strafe_step;
	int		tmp_x;
	int		tmp_y;
	int		count;
	double	angle;
}	t_pinfo;

typedef struct s_textinf
{
	double	x;
	double	y0;
	double	y1;
	double	wall_strip_height;
	int		pixels;
}	t_tinfo;

typedef struct s_list
{
	char			*c;
	struct s_list	*next;
}	t_list;

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strcmp(char *s1, char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len, t_cub *cub);
size_t	ft_strlen(const char *s);
int		parse_map_name(char *map_file, t_cub *cub);
char	*ft_strdup(const char *s1, t_cub *cub);
char	*ft_strjoin(char *s1, char *s2, t_cub *cub);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd, t_cub *cub);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_iswspace(unsigned char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		element_type(char *line);
int		fill_field(char *line, int type, t_cub *cub);
int		empty_line(char *line);
int		full_cub(t_cub *cub);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check_rgb(t_cub *cub);
void	init_cub(t_cub *cub);
int		fill_cub(t_cub *cub, int map_fd);
t_list	*ft_lstnew(void *c, t_cub *cub);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*map_split(int map_fd, char *map_file, t_cub *cub);
int		ft_lstsize(t_list *lst);
void	gc_free(t_cub *data);
t_trash	*gc_new(void *address, t_cub *data);
void	gc_add(t_trash **head, t_trash *new);
void	*gc_malloc(size_t size, t_cub *data);
void	gc_free(t_cub *data);
void	free_trash(t_trash *head);
void	textures(t_cub *cube, double id, t_tinfo t_data,
			mlx_texture_t *pic_data);
void	player_update(t_cub *cub);
void	my_keyhook(void *param);
int		check_line(char *str);
int		map_checker(t_list *map);
int		map_check(t_cub *cub, char *map_file);
void	put_map(t_cub *cub);
void	put_frame(t_cub *cub);
double	limit_angle(double angle);
double	get_distance(double x1, double y1, double x2, double y2);
bool	check_coordinates(double x, double y, t_cub *cub);
double	closest_vertical_inter(t_cub *cub, double ray_angle, t_point *point);
double	closest_horizontal_inter(t_cub *cub, double ray_angle, t_point *point);
void	put_ceiling(t_cub *cub, int color);
void	put_floor(t_cub *cub, int color);
void	put_frame(t_cub *cub);
void	ray_cast(t_cub *cub, double ray_angle,
			double fov_in_rad, t_tinfo t_data);
void	init_sprites(t_cub *cube);
void	sprite(t_cub *cube, bool first, bool is_it_moving);
void	doors(mlx_key_data_t key, void *param);
void	replace_whitespace(char *line);
void	transform_mtl(char *line, t_cub *cub, t_list **head);
void	extend_line(t_list *node, size_t max, t_cub *cub);
int		check_adjacent_x(t_list *head);
void	replace_x_with_one(t_list *head);
t_list	*map_to_list(int map_fd, t_cub *cub);
char	**list_to_arr(t_list *head, t_cub *data);
void	player_location(t_cub *cub);
int		pre_check(char **string);
int		rgb_range(int color);
t_rgb	*rgb_new(unsigned char r,
			unsigned char g, unsigned char b, t_cub *cub);
void	mouse_hook(t_cub *cube);
void	wasd_keyhook(t_cub *cub, int *is_moving);
void	arrows_keyhook(t_cub *cub);
void	initialize_step(double ray_angle, t_cub *cub,
			double *step_x, double *step_y);
double	process_intersections(t_cub *cub, double step_x,
			double step_y, t_point *point);
void	set_spawn_direction(t_cub *cub);
void	change_map(t_cub *cub, char old, char new);
char	**ft_split(char const *s, char c, t_cub *data);
int		misplaced_space(char *input, t_cub *cub);
char	*ft_strtrim(const char *s1, const char *set, t_cub *cub);
int		is_all(char *string, int c);
t_list	*process_map_lines(int map_fd, t_cub *cub, size_t *max);
void	extend_all_lines(t_list *head, size_t max, t_cub *cub);
int		validate_twos(t_list *head);
void	terminate(void *cub);
void	clear_textures(t_cub *cub);
int		is_p(int c);

#endif
