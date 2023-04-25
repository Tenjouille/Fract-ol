/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:10:34 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/25 16:13:30 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	directional_arrow(int keysym, t_data *data)
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
}

void	zoom_event(int keysym, t_data *data)
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
}

void	julia_shift(int keysym, t_data *data)
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
}

int	handle_keypress(int keysym, t_data *data)
{
	directional_arrow(keysym, data);
	zoom_event(keysym, data);
	julia_shift(keysym, data);
	if (keysym == XK_Escape)
		end_of_prog(data);
	else if (keysym == 99)
	{
		data->fractal.color += 10;
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
