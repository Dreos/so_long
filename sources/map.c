/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:31:04 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 11:23:08 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int read_map(char *name,map *m)
{
	int fd;
	int i;
	char *s;
		
	fd=open(name,O_RDONLY);
	if(fd < 0)
		return(0);
	i = 0;
	s = get_next_line(fd);
	while(s)
	{
		free(s);
		s = get_next_line(fd);
		i++;
	}
	if(s)
		free(s);
	m->size_y = i;
	close(fd);
	return(1);
}

char **fill_tab(map *carte,char *name)
{
	char **tab;
	int i;
	int fd;
	char *s;
		
	if(!(tab  = malloc(sizeof(char **) * ((carte->size_y) + 1))))
		return(NULL);
	tab[carte->size_y] = NULL;
	fd=open(name,O_RDONLY);
	i = 0;
	s = get_next_line(fd);
	while(s)
	{
		tab[i] = s;
		i++;		
		s = get_next_line(fd);
	}
	close(fd);
	return (tab);
}

void edit_map(map *carte)
{
	int i ;
	int j ;
	
	i = 0;
	while(i	< carte->size_y)
	{	
		j = 0;
		while(carte->data[i][j])
		{	
			if(carte->data[i][j] == '\n')
				carte->data[i][j] ='\0';
			j++;
		}
		i++;
	}
}
pos create_pos(int x,int y)
{
	pos p;
	
	p.x = x;
	p.y = y;
	return (p);
}

void init_map(map *carte)
{
	carte->nb_food 	= 0;
	carte->mv = 0;
	carte->end = create_pos(-1,-1);
	carte->start = create_pos(-1,-1);
	carte->imgs = NULL;
	carte->win = NULL;
	carte->mlx = NULL;
}
