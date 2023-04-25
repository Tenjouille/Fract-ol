/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:10:04 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/25 16:54:16 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int iteration, int iter_max)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)iteration / (double)iter_max;
	if (iteration == iter_max)
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
	else if (t < 0.6425)
	{
		red = (t - 0.42) / 0.2225 * 255;
		green = 255;
		blue = 255 - (t - 0.42) / 0.2225 * 255;
	}
	else if (t < 0.8575)
	{
		red = 255;
		green = 255 - (t - 0.6425) / 0.215 * 255;
		blue = 0;
	}
	else
	{
		red = 255 - (t - 0.8575) / 0.1425 * 255;
		green = 0;
		blue = 0;
	}
	return (red * 0x10000 + green * 0x100 + blue);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (x * (img->bpp / 8) + y * img->rowlen);
	*(unsigned int *)pixel = color;
}

int	end_of_prog(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_parsing(ac, av, &data))
		return (0);
	data.zoom.mouse_x = 0;
	data.zoom.mouse_y = 0;
	data.zoom.zoom = 1;
	data.zoom.iter_max = 300;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 300, 300, "Fract-ol");
	data.img.mlx_img = mlx_new_image(data.mlx, 300, 300);
	data.img.addr = mlx_get_data_addr
		(data.img.mlx_img, &data.img.bpp, &data.img.rowlen, &data.img.end);
	render(&data, data.zoom.mouse_x, data.zoom.mouse_y);
	if (!data.win)
		return (free(data.mlx), 1);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, ButtonPress, ButtonPressMask, &mouse_stuff, &data);
	mlx_loop(data.mlx);
	return (0);
}
