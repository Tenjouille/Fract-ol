/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:05:59 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/25 17:39:40 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	select_fractal(char set, t_complex c, t_data *data)
{
	if (set == 'M')
		return (mandelbrot(c, data->zoom.iter_max));
	if (set == 'J')
		return (julia(c, data->zoom.iter_max, data));
	if (set == 'B')
		return (burning_ship(c, data->zoom.iter_max));
	return (0);
}

double	ft_abs(double res)
{
	if (res < 0)
		return (-res);
	return (res);
}

double	pix_to_comp(int x, int size, int cmp_plane, double zoom)
{
	return (((double)x - (size / 2)) * ((zoom * cmp_plane) / size));
}
