/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:02:02 by tbourdea          #+#    #+#             */
/*   Updated: 2023/04/25 15:03:58 by tbourdea         ###   ########.fr       */
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

void	ft_freeall(char **dest, int j)
{
	while (j >= 0)
	{
		free(dest[j]);
		j--;
	}
	free(dest);
}

int	ft_mallocsize(char const *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	if (s[0] == '\0')
		return (0);
	if (c == '\0')
		return (1);
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		if (s[i + 1] == '\0' || s[i + 1] == c)
		{
			size++;
			while (s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (size);
}

char	*ft_sepwords(char	**dest, char const *s, int c, int j)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	dest[j] = malloc(sizeof(char) * (size + 1));
	if (!dest[j])
	{
		ft_freeall(dest, j - 1);
		return (NULL);
	}
	while (s[i] != c && s[i] != '\0')
	{
		dest[j][i] = s[i];
		i++;
	}
	dest[j][i] = '\0';
	return (dest[j]);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_mallocsize(s, c) + 1));
	if (!dest)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (j < ft_mallocsize(s, c))
	{
		dest[j] = ft_sepwords(dest, &s[i], c, j);
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		j++;
	}
	dest[ft_mallocsize(s, c)] = 0;
	return (dest);
}
