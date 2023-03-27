/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:11:27 by tbourdea          #+#    #+#             */
/*   Updated: 2023/03/22 14:45:20 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	test(t_data *data, double x, double y)
{
	t_complex	c;
	t_fract		fract;
	t_complex	min;
	t_complex	max;
	int			iter_max;

	min.r = -2;//x - OFFSET;
	min.i = -2;//y - OFFSET;
	max.r = 2;//x + OFFSET;
	max.i = 2;//y + OFFSET;
	iter_max = 100;
	fract.x = 0;
	while (fract.x < (max.r - min.r) * data->zoom.zoom)
	{
		fract.y = 0;
		while (fract.y < (max.i - min.i) * data->zoom.zoom)
		{
			c.r = (double)fract.x / data->zoom.zoom + min.r;
			c.i = (double)fract.y / data->zoom.zoom + min.i;
			if (mandelbrot(c, iter_max) == iter_max)
				img_pix_put(&data->img, fract.x, fract.y, 0);
			else
			{
				// fract.color = get_color(mandelbrot(c, iter_max) * 255 / 100, iter_max);
				img_pix_put(&data->img, fract.x, fract.y, 0xFFFFFF);				
			}
			fract.y++;		
		}
		fract.x++;
	}
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
	while (i < iter_max && (z.r * z.r + z.i * z.i) < 4)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i +  c.i;
		i++;
	}
	return (i);
}
