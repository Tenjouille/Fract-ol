/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:10:04 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/01 18:10:26 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	exit (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_parsing(ac, av, &data))
		return (0);
	data.zoom.mouse_x = 0;
	data.zoom.mouse_y = 0;
	data.zoom.zoom = 1;
	data.fractal.rgb = 3;
	data.zoom.iter_max = 300;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 300, 300, "Fract-ol");
	render(&data, data.zoom.mouse_x, data.zoom.mouse_y);
	if (!data.win)
		return (free(data.mlx), 1);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, ButtonPress, ButtonPressMask, &mouse_stuff, &data);
	mlx_hook(data.win, 17, 1l << 17, &end_of_prog, &data);
	mlx_loop(data.mlx);
	return (0);
}
