/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:10:04 by tbourdea          #+#    #+#             */
/*   Updated: 2023/03/27 14:57:33 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	pix_to_comp(int x, int size, int cmp_plane, double zoom)
{
	return (((double)x - (size / 2)) * ((zoom * cmp_plane) / size));
}

int	get_color(int iteration, int iter_max)
{
    int red;
    int green;
    int blue;

    if (iteration == iter_max)
		return (0);
	red = (iteration * 15) % 256;
    green = (iteration * 2) % 256;
    blue = (iteration * 4) % 256;
    return (red * 0x10000 + green * 0x100 + blue);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (x * (img->bpp / 8) + y * img->rowlen);
	*(unsigned int *)pixel = color;
}

void	render(t_data *data, double x, double y)
{
	t_complex	c;
	t_fract		fract;
	int			iter_max;
	
	iter_max = 300;// data->zoom.zoom;
	fract.win_width = 800;
	fract.win_height = 800;
	fract.y = 0;
	while (fract.y < fract.win_height)
	{
		fract.x = 0;
		while (fract.x < fract.win_width)
		{
			c.r = pix_to_comp(fract.x, fract.win_width, 4, data->zoom.zoom) + x;
			c.i = pix_to_comp(-fract.y, -fract.win_height, -4, data->zoom.zoom) + y;
			if (mandelbrot(c, iter_max) == iter_max)
				img_pix_put(&data->img, fract.x, fract.y, 0);
			else
			{
				// img_pix_put(&data->img, fract.x, fract.y, 0xFFFFFF);
				fract.color = get_color(mandelbrot(c, iter_max) * 255 / 100, 50);
				img_pix_put(&data->img, fract.x, fract.y, fract.color * 0x10000 + fract.color * 0x100 + fract.color);				
			}
			fract.x++;
		}
		fract.y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.mlx_img);
}

int	handle_no_event(void *data)
{
	return (0);
}

// int	handle_keyrelease(int keysym, t_data *data)
// {
// 	printf("6 : %d\n", data->zoom);
// 	printf("Key released : %d\n", keysym);
// 	return (0);
// }

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		end_of_prog(data);
	return (0);
}

int	handle_mouse_stuff(int mousesym, int x, int y, t_data *data)
{
	if (mousesym == 4)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
		// printf("%f\n", data->zoom.mouse_x);
		data->zoom.mouse_x += pix_to_comp(x, 800, 4, data->zoom.zoom);
		data->zoom.mouse_y += pix_to_comp(-y, -800, -4, data->zoom.zoom);
		data->zoom.zoom /= 1.5;
		printf("(%f,%f)\n", data->zoom.mouse_x, data->zoom.mouse_y);
		data->img.mlx_img = mlx_new_image(data->mlx, 1080/*(fractal.width)*/, 1080/*(fractal.height)*/);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.rowlen, &data->img.end);
		render(data, x, y);
		// get_zoom_data(data->fractal, &data->zoom);
	}
	if (mousesym == 5)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
		// printf("%f\n", data->zoom.mouse_y);
		data->zoom.mouse_x -= pix_to_comp(x, 800, 4, data->zoom.zoom);
		data->zoom.mouse_y -= pix_to_comp(-y, -800, -4, data->zoom.zoom);
		data->zoom.zoom *= 1.5;
		data->img.mlx_img = mlx_new_image(data->mlx, 1080/*(fractal.width)*/, 1080/*(fractal.height)*/);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.rowlen, &data->img.end);
		render(data, pix_to_comp(data->zoom.mouse_x, 800, 4, data->zoom.zoom), pix_to_comp(-data->zoom.mouse_y, -800, -4, data->zoom.zoom));
		// get_zoom_data(data->fractal, &data->zoom);
	}
	// printf("Zoom : %f%%\n", data->zoom.zoom);
	return (0);
}

int	end_of_prog(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
}

int	main(void)
{
	t_data	data;

	data.zoom.mouse_x = 0;
	data.zoom.mouse_y = 0;
	data.zoom.zoom = 1;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 1080, 1080, "Fract-ol");
	data.img.mlx_img = mlx_new_image(data.mlx, 1080/*(fractal.width)*/, 1080/*(fractal.height)*/);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.rowlen, &data.img.end);
	render(&data, data.zoom.mouse_x, data.zoom.mouse_y);
	if (!data.win)
		return (free(data.mlx), 1);
	// mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, ButtonPress, ButtonPressMask, &handle_mouse_stuff, &data);
	// mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx);
	
	return (0);
}