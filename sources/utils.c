/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:49:44 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 10:31:51 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <unistd.h>

static long int	nbdigit(long int i)
{
	long int	size;

	size = 0;
	if (i == 0)
		return (1);
	if (i < 0)
	{
		size++;
	}
	while (i != 0)
	{
		size++;
		i = i / 10;
	}
	return (size);
}

static char	*convert(char *s, long int i)
{
	if (i / 10 == 0)
	{
		*s = i + '0';
		return (s + 1);
	}
	s = convert(s, i / 10);
	*s = i % 10 + '0';
	return (s + 1);
}

char	*ft_itoa(long int i)
{
	char		*s;
	int			size;
	long int	j;

	j = i;
	size = nbdigit(j);
	s = malloc(size + 1);
	if (!(s))
		return (0);
	s[size] = '\0';
	if (j < 0)
	{
		*s = '-';
		convert(s + 1, -j);
	}
	else
	{	
		convert(s, j);
	}
	return (s);
}

int	display_d(int nb)
{
	char	*str;
	int x;
	str = ft_itoa(nb);
	if (!(str))
		return (0);
	nb = 0;
	while (str[nb])
	{
		x = write(1, (str + nb), 1);
		nb++;
	}
	free(str);
	return (nb);
}

void error(char *s)
{
	int x;
	int l;
	
	l = ft_strlen(s);
	x = write(2,"Error : ",8); 
	x = write(2,s,l);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;

	i = 0;
	while (i < n && s1[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		if (!(s2[i]))
			return (0);
		i++;
	}
	if (i != n)
		return (-s2[i]);
	return (0);
}

int check_extension(char *filename,char *ext)
{
	int i;
	
	i = 0;
	if(ft_strlen(filename) <= 4)
		return(0);
	while(filename[i])
		i++;
	if(!(ft_strncmp(filename + i - ft_strlen(ext),ext,ft_strlen(ext))))
		return (1);
	return(0);
}
