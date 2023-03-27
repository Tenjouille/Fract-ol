/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:10:29 by tbourdea          #+#    #+#             */
/*   Updated: 2023/03/27 11:25:51 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# define OFFSET 0.0625

typedef struct	s_complex
{
	double		r;
	double		i;
}				t_complex;


typedef struct	s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			rowlen;
	int			end;
}				t_img;

typedef struct	s_fract
{
	int			x;
	int			y;
	int			win_width;
	int			win_height;
	int			color;
}				t_fract;

typedef struct	s_zoom
{
	double		zoom;
	double		mouse_x;
	double		mouse_y;
}				t_zoom;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_fract		fractal;
	t_img		img;
	t_zoom		zoom;
}				t_data;



int		end_of_prog(t_data *data);
// int		handle_keyrelease(int keysym, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_mouse_stuff(int mousesym, int x, int y, t_data *data);
int		handle_no_event(void *data);
void	test(t_data *data, double x, double y);
void	img_pix_put(t_img *img, int x, int y, int color);
int		mandelbrot(t_complex c, int iter_max);
int		get_color(int iteration, int iter_max);

#endif