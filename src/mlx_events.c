/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:10:34 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/01 16:16:02 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	directional_arrow(int keysym, t_data *data)
{
	if (keysym == 65361)
	{
		data->zoom.mouse_x -= 1 * data->zoom.zoom;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 65362)
	{
		data->zoom.mouse_y += 1 * data->zoom.zoom;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 65363)
	{
		data->zoom.mouse_x += 1 * data->zoom.zoom;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 65364)
	{
		data->zoom.mouse_y -= 1 * data->zoom.zoom;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else
		return (0);
	return (1);
}

int	zoom_event(int keysym, t_data *data)
{
	if (keysym == 61)
	{
		data->zoom.iter_max += 100;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 45)
	{
		data->zoom.iter_max -= 100;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else
		return (0);
	return (1);
}

int	julia_shift(int keysym, t_data *data)
{
	if (keysym == 119)
	{
		data->crdnt.r += 0.1;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 115)
	{
		data->crdnt.r -= 0.1;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 100)
	{
		data->crdnt.i += 0.1;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else if (keysym == 97)
	{
		data->crdnt.i -= 0.1;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	else
		return (0);
	return (1);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (!directional_arrow(keysym, data) && !zoom_event(keysym, data)
		&& !julia_shift(keysym, data) && keysym != 99 && keysym != 65307)
	{
		write (1, "\nUnknown command, here's a list of valid commands :\n\n", 53);
		write (1, "Directionals arrows : moove horizontally & vertically", 53);
		write (1, "into the fractal.\n[-] & [=] : Decrease and increase", 51);
		write (1, "the maximum iteration number.\nFor the Julia set, [W]", 52);
		write (1, "[A][S][D] : increase or decrease the 2 values given in", 54);
		write (1, " parameter to have a different Julia set.\n", 42);
		write (1, "[C] : Change the fractal's tint\n", 32);
	}
	if (keysym == XK_Escape)
		end_of_prog(data);
	else if (keysym == 99)
	{
		if (data->fractal.rgb == 3)
			data->fractal.rgb = 1;
		else
			data->fractal.rgb++;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	return (0);
}

int	mouse_stuff(int mousesym, int x, int y, t_data *data)
{
	if (mousesym == 4)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
		data->zoom.mouse_x += pix_to_comp(x, 300, 4, data->zoom.zoom);
		data->zoom.mouse_y += pix_to_comp(-y, -300, -4, data->zoom.zoom);
		data->zoom.zoom /= 1.5;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	if (mousesym == 5)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
		data->zoom.mouse_x += pix_to_comp(x, 300, 4, data->zoom.zoom);
		data->zoom.mouse_y += pix_to_comp(-y, -300, -4, data->zoom.zoom);
		data->zoom.zoom *= 1.5;
		render(data, data->zoom.mouse_x, data->zoom.mouse_y);
	}
	return (0);
}
