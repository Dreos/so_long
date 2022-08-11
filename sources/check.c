/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:32:21 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 10:19:17 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
int check_border(map *carte)
{	
	int i;
		
	i = 0;
	while(i < carte->size_x)
	{
		if((carte->data[0][i] != '1') || carte->data[carte->size_y - 1][i] != '1')
			return(0);
		i++;
	}
	i = 0;
	while(i < carte->size_y)
	{
		if((carte->data[i][0] != '1' || carte->data[i][carte->size_x-1] != '1'))
			return(0);
		i++;
	}
	return(1);
}

int check_case(int x,int y ,map *carte)
{
	char c;

	c = carte->data[x][y];
	if(c == 'E')
	{
		if(carte->end.x != -1)
			return(0);	
		carte->end = create_pos(x,y);
		return(1);
	}
	if(c == 'P')
	{
		if(carte->start.x != -1)
			return(0);
		carte->start = create_pos(x,y);
		return(1);
	}
	if(c == 'C')
	{
		carte->nb_food = carte->nb_food + 1;
		return(1);
	}
	if(c != '0' && c!= '1')
		return (0);
	return(1);
}

int check_inside(map *carte)
{
	int i;
	int j;
	
	i = 1;
	while(i<carte->size_y)
	{
		j=1;
		while(j < carte->size_x - 1)
		{					
			if(!(check_case(i,j,carte)))
				return(0);
			j++;
		} 
		i++;
	}
	if(carte->end.x != -1  && carte->start.x != -1 && carte->nb_food > 0)
		return(1);	
	return(0);
}

int check_rectangle(map *carte)
{
	int i;

	i = 0;
	if(carte->size_y <= 2)
		return(0);
	while(i < carte->size_y)
	{
		if(carte->size_x != strlen(carte->data[i]) || carte->size_x <=2)
			return (0);
		i++;
	}
	return(1);
}

int check_all(map *carte)
{
	if(check_rectangle(carte) == 0)
	{
		error("Carte pas rectangulaire\n");
		return(0);
	}
	if(check_border(carte) == 0)
	{
		error("Les murs sont pas bons\n");
		return(0);
	}
	if(check_inside(carte) == 0)
	{
		error("la carte n'est pas valide\n");
		return(0);
	}
	return(1);
}
