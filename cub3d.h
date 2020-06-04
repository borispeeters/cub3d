/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 13:29:52 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:43:22 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef	struct		s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				img_width;
	int				img_height;
}					t_img;

typedef	struct		s_ray
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
	float			raydirx0;
	float			raydiry0;
	float			raydirx1;
	float			raydiry1;
	float			rowdistance;
	float			floorstepx;
	float			floorstepy;
	float			floorx;
	float			floory;
	int				cellx;
	int				celly;
	int				tx;
	int				ty;
	int				x;
	int				y;
}					t_ray;

typedef	struct		s_sprite
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				stripe;
	int				d;
	int				i;
}					t_sprite;

typedef	struct		s_data
{
	void			*mlx;
	void			*win;
	t_img			*img[2];
	t_img			*tex[8];
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				start;
	int				key_forward;
	int				key_back;
	int				key_left;
	int				key_right;
	int				key_rot_left;
	int				key_rot_right;
	int				screenwidth;
	int				screenheight;
	char			*path[8];
	int				floor;
	int				ceiling;
	char			**arr;
	int				**map;
	int				*mapwidth;
	int				mapheight;
	int				map_check;
	double			**sprites;
	int				num_sprite;
	int				type_check[9];
	int				fd;
	double			*zbuffer;
	double			hp;
	int				status;
}					t_data;

typedef	struct		s_bitmap
{
	int				padding;
	int				filesize;
	unsigned char	header[54];
	unsigned char	pad[3];
	unsigned char	px[3];
	int				fd;
}					t_bitmap;

typedef	struct		s_argb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_argb;

typedef	union		u_color
{
	unsigned int	color;
	t_argb			argb;
}					t_color;

void				ft_raycast(t_data *data);
void				rotate_player(t_data *data, double rotspeed);
void				move_forward(t_data *data, double movespeed, \
					double buffer);
void				move_backwards(t_data *data, double movespeed, \
					double buffer);
void				move_left(t_data *data, double movespeed, double buffer);
void				move_right(t_data *data, double movespeed, double buffer);
int					quit_program(t_data *data);
int					mouse_movement(int x, int y, t_data *data);
int					key_check(t_data *data);
int					key_release(int keycode, t_data *data);
int					key_press(int keycode, t_data *data);
void				set_north(t_data *data, int i, int k);
void				set_south(t_data *data, int i, int k);
void				set_east(t_data *data, int i, int k);
void				set_west(t_data *data, int i, int k);
void				set_sprite(t_data *data, int i, int k, int obj);
int					ft_isvalidmap(int c);
int					ft_isspace(int c);
int					ft_atoi_ref(char **str);
void				check_eol(char **str, t_data *data);
void				skip_space(char **str);
void				init_mlx(t_data *data);
void				calc_ray(t_ray *ray, t_data *data);
void				calc_raydist(t_ray *ray, t_data *data);
void				ft_dda(t_ray *ray, t_data *data);
void				calc_drawpos(t_ray *ray, t_data *data);
void				ft_raycast(t_data *data);
void				init_mlx(t_data *data);
void				sprite_cast(t_data *data, t_ray *ray, int bool);
void				draw_sprite(t_ray *ray, t_data *data, t_sprite *sprite, \
					int bool);
void				calc_sprite_draw(t_sprite *sprite, t_data *data);
void				sprite_calc(t_sprite *sprite, t_data *data);
void				draw_fc_tex(t_data *data, int bool);
void				mlx_pixel_to_image(t_img *img, int x, int y, int color);
unsigned int		fog_color(double distance, unsigned int color);
void				allocate_map(t_data *data);
void				read_map(t_data *data);
int					parse_res(char **str, t_data *data);
int					parse_path(t_data *data, char **str, char **path, \
					int type);
int					parse_color(t_data *data, char **str, int *rgb, \
					int type);
void				error_exit(char *str, t_data *data);
void				map_parser(t_data *data);
void				reset_map(t_data *data);
void				ft_floodfill(t_data *data, int x, int y);
void				parse_hub(t_data *data, char *cub);
void				lose_health(t_data *data);
void				gain_health(t_data *data);
void				draw_health(t_data *data, int bool);
void				game_over(t_data *data);
void				pickup_obj(t_data *data, int x, int y);
void				draw_map(t_data *data, int bool);
void				cat_title_res(t_data *data, char *title);
void				write_bmp(t_data *data);
void				set_tex_img(t_data *data, t_img *texture);
void				create_frames(t_data *data, t_img *img);
void				allocate_map_height(t_data *data);
void				allocate_sprites(t_data *data);

#endif
