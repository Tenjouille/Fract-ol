/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:32:26 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/21 15:53:22 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int interpolate_color(int color1, int color2, int ratio)
{
	int r1, g1, b1, r2, g2, b2, r, g, b;

	r1 = (color1 >> 16) & 0xff;
	g1 = (color1 >> 8) & 0xff;
	b1 = color1 & 0xff;
	r2 = (color2 >> 16) & 0xff;
	g2 = (color2 >> 8) & 0xff;
	b2 = color2 & 0xff;

	r = (r1 * (100 - ratio) + r2 * ratio) / 100;
	g = (g1 * (100 - ratio) + g2 * ratio) / 100;
	b = (b1 * (100 - ratio) + b2 * ratio) / 100;

	return r * 0x10000 + g * 0x100 + b;
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

// int	julia(t_complex z, int iter_max, char *str)
// {
// 	char		**buff;
// 	t_complex	c;
// 	t_complex	tmp;
// 	int			i;

// 	buff = ft_split(str, ' ');
// 	z.r = atod(buff[0]);
// 	z.i = atod(buff[2]);
// 	if (buff[1][0] == '-')
// 		z.i *= -1;
// 	i = 0;
// 	while ((z.r * z.r + z.i * z.i) < 4 && i < iter_max)
// 	{
// 		tmp = z;
// 		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
// 		z.i = 2 * tmp.r * tmp.i +	c.i;
// 		i++;
// 	}
// 	return (i);
// }

// int julia(t_complex z, int iter_max)
// {
		
// }  