/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:39:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/21 16:26:44 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

double	atod(char *src)
{
	int		i;
	double	res;
	int		sign;
	int		div;

	div = 0;
	i = 0;
	res = 0;
	sign = 1;
	if (src[i] == '-')
	{
		i++;
		sign = -sign;
	}
	else if (src[i] == '+')
		i++;
	if (src[i] == '0' && src[i + 1] == '.')
	{
		i += 2;
		div = 1;
	}
	while (src[i] >= '0' && src[i] <= '9')
	{
		if (src[i] < '0' || src[i] > '9')
		{
			display_options();
			exit (0);
		}
		res = res * 10 + src[i] - '0';
		i++;
		div *= 10;
	}
	if (div == 0)
		return (res * sign);
	return (res * sign / div);
}

void	display_options(void)
{
	write (2, "Here are the differents available options :\n", 44);
	write (2, "\t1. [M] for Mandelbrot set\n\t2.  for Julia set", 45);
	write (2, " with \"x + yi\" to determinate which one,", 40);
}

int	error_msg(int ac, char **av)
{
	if (ac == 1)
	{
		write (2, "Please specify which fractal set you want to see\n\n", 50);
		return (0);
	}
	if (ft_strlen(av[1]) != 1 || av[1][0] != 'J' && av[1][0] != 'M')
	{
		write (2, "Sorry, this option does not exist.\n\n", 36);
		return (0);
	}
	if ((ac > 2 && av[1][0] == 'M') || ac > 4)
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
	char	**buff;

	if (!error_msg(ac, av))
	{
		display_options();
		return (0);
	}
	if (ac == 4 && av[1][0] == 'J')
	{
		data->crdnt.r = atod(av[2]);
		data->crdnt.i = atod(av[3]);
		printf ("%f + %fi", data->crdnt.r, data->crdnt.i);
	}
	return (1);
}
