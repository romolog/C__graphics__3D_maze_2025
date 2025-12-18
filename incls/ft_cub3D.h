/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:20:37 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/27 13:47:51 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <stddef.h>

typedef struct s_player
{
	double			d;
	double			d_sin;
	double			rotate;
	double			move_x;
	double			move_y;

	double			mxa;
	double			mya;
	double			mxd;
	double			myd;
	double			mxs;
	double			mys;	
	double			mxw;
	double			myw;

	int				c;
	int				r;
	double			x;
	double			y;
	double			min_to_wall;
	double			step;
	double			rad;	
}	t_pl;

typedef struct s_tracer
{
	t_pl			*p;

	char			**f_map;
	char			**f_map_raw;
	int				f_map_fd;
	char			*f_map_textures[4];
	void			*f_tex[4];
	int				**f_vert;
	double			*f_vert_angle;

	char			*err;
	char			*err_algorithm;
	char			*err_map_invalid;
	char			*err_mlx;
	char			*err_overflow;

	int				exit;
	int				exit_status;

	int				map_c[4];
	int				map_cols;
	int				map_f[4];
	int				map_init;
	int				map_init_nswecf;
	int				map_invalid;
	char			map_player;

	int				map_raw_rows;
	int				map_rows;

	void			*mlx;
	void			*mlx_win;
	int				mlx_wdth;
	int				mlx_hght;
	void			*mlx_img;
	int				*mlx_addr;
	int				mlx_bpp;
	int				mlx_line_len;
	int				mlx_endian;

	char			*prog;

	double			ray_x;
	double			ray_angle;
	double			ray_tan;
	int				ray_tan_err;
	double			ray_c_dx;
	double			ray_c_dy;
	double			ray_r_dx;
	double			ray_r_dy;
	double			ray_dx;
	double			ray_dy;
	int				ray_quarter;

	int				*tex_addr[4];
	int				tex_h[4];
	int				tex_w[4];

	int				vert_idx;
	int				vert_height;
	int				vert_tex_idx;
	int				vert_tex_point;
}	t_tr;

# ifdef NDEBUG
#  define DEBUG_MODE 0
# else
#  define DEBUG_MODE 1
# endif

int		ft_abs(int a);
void	ft_add_str_malloc(char **dst, char *add, size_t add_len, t_tr *t);
void	ft_free_2d_char(char ***arr);
void	ft_free_2d_int(int ***arr);
int		ft_free_close_fd(int *fd);
void	ft_free_str(char **str);

void	ft_cleanup(t_tr *t);
void	ft_err(int condition, t_tr *t, char *file_name, int line);

void	ft_calc_maze(t_tr *t);
void	ft_calc_texture(t_tr *t);
void	ft_check_args(int argc, char **argv, t_tr *t);
int		ft_get_cross_xy(int *r, int *c, t_tr *t);
void	ft_get_height(char *master, int r, int c, t_tr *t);
void	ft_draw_maze(t_tr *t);
void	ft_get_cross(int r, int c, t_tr *t);
void	ft_get_map_entry(char *entry, t_tr *t);
char	*ft_get_prog_name(char *prog_name);
void	ft_get_tex_point(t_tr *t);
void	ft_init_mlx(t_tr *t);
void	ft_init_mlx_window(t_tr *t);
int		ft_is_45degree(double angle);
int		ft_is_space_tab_newline(char *entry);
int		ft_is_valid_map(t_tr *t);
int		ft_is_valid_textures(t_tr *t);
void	ft_move_rotate(t_tr *t);
void	ft_passby_zero_one_player(char **k, char *entry, t_tr *t);
void	ft_record_vertice(t_tr *t);

void	ft_set_map(t_tr *t);
void	ft_set_player(t_tr *t);
void	ft_set_textures(t_tr *t);
void	ft_set_tracer(char *map_file, t_pl *p, t_tr *t);
void	ft_set_vars_map(char *map_file, t_tr *t);
void	ft_set_vars_player(t_tr *t);
void	ft_set_vars_vertices(t_tr *t);
void	ft_transform_rawmap_to_arr2d(t_tr *t);

int		ft_event_key_press(int key, t_tr *t);
int		ft_event_key_release(int key, t_tr *t);
int		ft_event_red_button(t_tr *t);

#endif