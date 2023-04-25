/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:10:29 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/25 17:18:03 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_complex
{
	double	r;
	double	i;
}			t_complex;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		rowlen;
	int		end;
}			t_img;

typedef struct s_fract
{
	int	x;
	int	y;
	int	win_width;
	int	win_height;
	int	color;
}		t_fract;

typedef struct s_zoom
{
	double	zoom;
	double	mouse_x;
	double	mouse_y;
	int		iter_max;
}			t_zoom;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		set;
	t_complex	crdnt;
	t_fract		fractal;
	t_img		img;
	t_zoom		zoom;
}				t_data;

/*				fractol_utils.c				*/
int		select_fractal(char set, t_complex c, t_data *data);
double	ft_abs(double res);
double	pix_to_comp(int x, int size, int cmp_plane, double zoom);
/*				ft_split.c				*/
int		ft_strlen(char *str);
void	ft_freeall(char **dest, int j);
int		ft_mallocsize(char const *s, char c);
char	*ft_sepwords(char **dest, char const *s, int c, int j);
char	**ft_split(char const *s, char c);
/*				mlx_events.c				*/
void	directional_arrow(int keysym, t_data *data);
void	zoom_event(int keysym, t_data *data);
void	julia_shift(int keysym, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		mouse_stuff(int mousesym, int x, int y, t_data *data);
/*				parsing.c				*/
int		define_sign(char *src, int *div, int *sign);
double	atod(char *src);
int		display_options(void);
int		error_msg(int ac, char **av);
int		ft_parsing(int ac, char **av, t_data *data);
/*				render.c				*/
void	coloring_win(t_data *data, double x, double y);
void	render(t_data *data, double x, double y);
int		mandelbrot(t_complex c, int iter_max);
int		julia(t_complex z, int iter_max, t_data *data);
int		burning_ship(t_complex c, int iter_max);
/*				main.c				*/
int		get_color(int iteration, int iter_max);
void	img_pix_put(t_img *img, int x, int y, int color);
int		end_of_prog(t_data *data);

#endif