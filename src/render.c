/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:32:26 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/01 18:10:52 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	coloring_win(t_data *data, double x, double y)
{
	t_complex	c;
	t_fract		fract;
	int			iter;

	fract.y = 0;
	while (fract.y < 300)
	{
		fract.x = 0;
		while (fract.x < 300)
		{
			c.r = pix_to_comp(fract.x, 300, 4, data->zoom.zoom) + x / 2;
			c.i = pix_to_comp(-fract.y, -300, -4, data->zoom.zoom) + y / 2;
			iter = select_fractal(data->set, c, data);
			if (iter == data->zoom.iter_max)
				img_pix_put(&data->img, fract.x, fract.y, 0);
			else
			{
				fract.color = select_color_set(data->fractal.rgb, iter, data);
				img_pix_put(&data->img, fract.x, fract.y, fract.color);
			}
			fract.x++;
		}
		fract.y++;
	}
}

void	render(t_data *data, double x, double y)
{
	data->img.mlx_img = mlx_new_image(data->mlx, 300, 300);
	data->img.addr = mlx_get_data_addr
		(data->img.mlx_img, &data->img.bpp, &data->img.rowlen, &data->img.end);
	coloring_win(data, x, y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.mlx_img);
}

int	mandelbrot(t_complex c, int iter_max)
{
	t_complex	z;
	t_complex	tmp;
	int			i;

	z.r = 0;
	z.i = 0;
	i = 0;
	while ((z.r * z.r + z.i * z.i) < 4 && i < iter_max)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		i++;
	}
	return (i);
}

int	julia(t_complex z, int iter_max, t_data *data)
{
	t_complex	c;
	t_complex	tmp;
	int			i;

	c.r = data->crdnt.r;
	c.i = data->crdnt.i;
	i = 0;
	while ((z.r * z.r + z.i * z.i) < 4 && i < iter_max)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		i++;
	}
	return (i);
}

int	burning_ship(t_complex c, int iter_max)
{
	t_complex	z;
	t_complex	tmp;
	int			i;

	z.r = 0;
	z.i = 0;
	i = 0;
	while ((z.r * z.r + z.i * z.i) < 4 && i < iter_max)
	{
		tmp = z;
		z.r = ft_abs(tmp.r) * ft_abs(tmp.r);
		z.r += -ft_abs(tmp.i) * ft_abs(tmp.i) + c.r;
		z.i = 2 * ft_abs(tmp.r) * ft_abs(tmp.i) + c.i;
		i++;
	}
	return (i);
}
