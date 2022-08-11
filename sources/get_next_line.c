/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:32:38 by lloisel           #+#    #+#             */
/*   Updated: 2022/05/10 04:30:42 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		boul;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	boul = 1;
	while ((!(ft_strchr(str, '\n') || (ft_strchr(str, EOF))) && boul != 0))
	{
		boul = read(fd, buffer, BUFFER_SIZE);
		if (boul == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[boul] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}	

char	*get_next_line(int fd)
{
	char		*rt;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	rt = ft_line(str);
	str = ft_cut(str);
	return (rt);
}
/*
int main()
{
	int fd;
	char *str;
	printf("-------------\n");	
	fd = open("test2", O_RDONLY);
	str = get_next_line(fd);
	printf("str final |%s|\n",str);
	free(str);
	str = get_next_line(fd);
	printf("str final |%s|\n",str);
	free(str);
	str = get_next_line(fd);
	printf("str final |%s|\n",str);
	free(str);
	str = get_next_line(fd);
	printf("str final |%s|\n",str);
	free(str);
	printf("-------------\n");	
		 
}*/
