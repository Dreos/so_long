/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:32:59 by lloisel           #+#    #+#             */
/*   Updated: 2022/06/27 13:59:29 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l;
	char	*rt;

	if (!s1)
	{	
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if ((!s1 || !s2) || (ft_strlen(s1) == 0 && ft_strlen(s2) == 0))
	{
		free(s1);
		return (NULL);
	}
	l = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	rt = malloc(l);
	if (!(rt))
		return (0);
	rt[l - 1] = '\0';
	l = -1;
	while (s1[++l])
		rt[l] = s1[l];
	while (*s2)
		rt[l++] = *s2++;
	free(s1);
	return (rt);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (s[i] == c)
		return (s + i);
	return (0);
}

char	*ft_line(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_cut(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
	{
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}
