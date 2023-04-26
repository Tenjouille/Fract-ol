/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:39:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/26 12:50:10 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	define_sign(char *src, int *div, int *sign)
{
	int	i;

	i = 0;
	if (src[i] == '-')
	{
		*sign *= -1;
		i++;
	}
	else if (src[i] == '+')
		i++;
	if (src[i] == '0' && src[i + 1] == '.')
	{
		i += 2;
		*div = 1;
	}
	return (i);
}

double	atod(char *src)
{
	int		i;
	int		sign;
	double	res;
	int		div;

	div = 0;
	res = 0;
	sign = 1;
	i = define_sign(src, &div, &sign);
	if (src[i] < '0' || src[i] > '9')
		display_options();
	while (src[i] >= '0' && src[i] <= '9')
	{
		if (src[i] < '0' || src[i] > '9')
			display_options();
		res = res * 10 + src[i] - '0';
		i++;
		div *= 10;
	}
	if (div == 0)
		return (res * sign);
	return (res * sign / div);
}

int	display_options(void)
{
	write (2, "Here are the differents available options :\n", 44);
	write (2, "\t1. [M] for Mandelbrot set\n\t2.  for Julia set", 45);
	write (2, " with \"x + yi\" to determinate which one,", 40);
	exit (0);
}

int	error_msg(int ac, char **av)
{
	if (ac == 1)
	{
		write (0, "Please specify which fractal set you want to see\n\n", 50);
		return (0);
	}
	if (ft_strlen(av[1]) != 1
		|| (av[1][0] != 'J' && av[1][0] != 'M' && av[1][0] != 'B'))
	{
		write (2, "Sorry, this option does not exist.\n\n", 36);
		return (0);
	}
	if ((ac > 2 && (av[1][0] == 'M' || av[1][0] == 'B')) || ac > 4)
	{
		write (2, "Sorry, this option does not exist.\n\n", 36);
		return (0);
	}
	if (ac != 4 && av[1][0] == 'J')
	{
		write (2, "Please specify correctly which Julia set you ", 45);
		write (2, "want to see\n\n", 13);
		return (0);
	}
	return (1);
}

int	ft_parsing(int ac, char **av, t_data *data)
{
	if (!error_msg(ac, av))
	{
		display_options();
		return (0);
	}
	if (ac == 4 && av[1][0] == 'J')
	{
		data->crdnt.r = atod(av[2]);
		data->crdnt.i = atod(av[3]);
	}
	data->set = av[1][0];
	return (1);
}
