/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:20:37 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/15 15:33:41 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <stddef.h>

typedef struct s_tracer
{
	char			**f_map;
	char			**f_map_raw;	
	int				f_map_fd;
	char			f_map_textures[4];			
	// char			*f_map_no;
	// char			*f_map_so;
	// char			*f_map_we;
	// char			*f_map_ea;
	int				**f_p_verts;

	char			*err;
	char			*err_map_invalid;
	char			*err_mlx;	
	char			*err_overflow;

	int				exit;
	int				exit_status;	

	int				map_c[3]; // celing RGB
	int				map_cols;
	int				map_f[3]; // floor RGB
	int				map_init;
	int				map_init_nswecf;
	int				map_invalid;	
	char			map_player;
	int				map_player_row_idx;
	int				map_player_col_idx;
	int				map_raw_rows;	
	int				map_rows;

	void			*mlx;
	void			*mlx_win;
	int				mlx_wdth;
	int				mlx_hght;
	void			*mlx_img;
	char			*mlx_addr;
	int				mlx_bpp;
	int				mlx_line_len;
	int				mlx_endian;

	double			p_b;
	double			p_d; // player direction angle
	double			p_d_step;
	int				p_incr_y;
	int				p_incr_x;
	double			p_dist_c_y;
	double			p_dist_r_x;
	double			p_dist_t_x;
	double			p_dist_t_y;		
	double			p_m;

	int				p_vertidx;
	int				p_wh_dist; // dist for the wall to be window heigh exactly	
	int				p_x;
	int				p_y;

	enum e_textures
	{
		NO,
		EA,
		SO,
		WE
	};

	char			*prog;
}	t_tr;

# ifdef NDEBUG
#  define DEBUG_MODE 0
# else
#  define DEBUG_MODE 1
# endif

void	ft_add_str_malloc(char **dst, char *add, size_t add_len, t_tr *t);
void	ft_free_2d_char(char ***arr);
void	ft_free_2d_int(int ***arr);
int		ft_free_close_fd(int *fd);
void	ft_free_str(char **str);

void	ft_cleanup(t_tr *t);
void	ft_err(int condition, t_tr *t, char *file_name, int line);

void	ft_check_args(int argc, char **argv, t_tr *t);
void	ft_calc_maze(t_tr *t);
void	ft_draw_maze(t_tr *t);
void	ft_get_map_entry(char *entry, t_tr *t);
char	*ft_get_prog_name(char *prog_name);
void	ft_init_mlx(t_tr *t);
int		ft_is_space_tab_newline(char *entry);
int		ft_is_valid_map(t_tr *t);
void	ft_set_map(t_tr *t);
void	ft_set_player(t_tr *t);
void	ft_set_tracer(char *map_file, t_tr *t);
void	ft_transform_rawmap_to_arr2d(t_tr *t);

// calc maze
void	ft_get_vertices(t_tr *t);

#endif