/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:41:46 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/01 16:42:49 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_opposite_tints(double t, int *main, int *more, int *less)
{
	if (t < 0.6425)
	{
		*more = (t - 0.42) / 0.2225 * 255;
		*less = 255;
		*main = 255 - (t - 0.42) / 0.2225 * 255;
	}
	else if (t < 0.8575)
	{
		*more = 255;
		*less = 255 - (t - 0.6425) / 0.215 * 255;
		*main = 0;
	}
	else
	{
		*more = 255 - (t - 0.8575) / 0.1425 * 255;
		*less = 0;
		*main = 0;
	}
}

int	get_green_colors(int iteration, int iter_max)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)iteration / (double)iter_max;
	if (t == 1)
		return (0);
	if (t < 0.16)
	{
		blue = 0;
		red = 0;
		green = 0.5 + (t / 0.16) * 255;
	}
	else if (t < 0.42)
	{
		blue = 0;
		red = (t - 0.16) / 0.26 * 255;
		green = 255;
	}
	else
		get_opposite_tints(t, &green, &blue, &red);
	return (red * 0x10000 + green * 0x100 + blue);
}

int	get_blue_colors(int iteration, int iter_max)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)iteration / (double)iter_max;
	if (t == 1)
		return (0);
	if (t < 0.16)
	{
		red = 0;
		green = 0;
		blue = 0.5 + (t / 0.16) * 255;
	}
	else if (t < 0.42)
	{
		red = 0;
		green = (t - 0.16) / 0.26 * 255;
		blue = 255;
	}
	else
		get_opposite_tints(t, &blue, &red, &green);
	return (red * 0x10000 + green * 0x100 + blue);
}

int	get_red_colors(int iteration, int iter_max)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)iteration / (double)iter_max;
	if (t == 1)
		return (0);
	if (t < 0.16)
	{
		green = 0;
		blue = 0;
		red = 0.5 + (t / 0.16) * 255;
	}
	else if (t < 0.42)
	{
		green = 0;
		blue = (t - 0.16) / 0.26 * 255;
		red = 255;
	}
	else
		get_opposite_tints(t, &red, &green, &blue);
	return (red * 0x10000 + green * 0x100 + blue);
}
