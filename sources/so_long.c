/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:15:17 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 11:27:35 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include "map.h"



void clean_up(map *carte)
{
	int i;
	
	i = 0;
	if(carte->imgs)
	{
		while(carte->imgs[i])
		{
			mlx_destroy_image(carte->mlx,carte->imgs[i]);
			i++;
		}
	}
	i = 0;
	while(i < carte->size_y)
	{
		free(carte->data[i]);
		i++;
	}
	if(carte->data)
		free(carte->data);
	if(carte->imgs)
		free(carte->imgs);
	if(carte->mlx && carte->win)
		mlx_destroy_window(carte->mlx,carte->win);
	if(carte->mlx)
		mlx_destroy_display(carte->mlx);
		free(carte->mlx);
}

int start(map *carte,char *name)
{
	if(!check_extension(name,".ber"))
	{
		error("mauvaise extension\n");	
		return(0);
	}	
	if(!(read_map(name,carte)))	
	{
		error("mauvais fichier\n");
		return(0);
	}
	carte->data = fill_tab(carte,name);
	if(!carte->data)
	{
		error("malloc de data\n");
		return(0);
	}
	edit_map(carte);
	carte->size_x = ft_strlen(carte->data[0]); 	
	init_map(carte);
	return(1);
}

int set_up(map *carte)
{
	
	if(!(init_window(carte,carte->size_x*30,carte->size_y*30)))
	{
		error("Init_window \n");
		return(0);
	}
	if(!(get_images(carte)))
	{
		error("get images\n");
		return(0);
	}
	print_map(carte);
	mlx_key_hook(carte->win,key_win,(void *)carte);
  	mlx_hook(carte->win,17,0,mouse,(void *)carte);
  	mlx_loop(carte->mlx);
	return(1);
}

int main(int argc,char **argv)
{
	if(argc == 2)
	{
		map carte;	
		if(!(start(&carte,argv[1])))
			return(0);
		if(check_all(&carte))
		{
			if(!(set_up(&carte)))
				return(0);
			clean_up(&carte);	 	
		}
		else
			clean_up(&carte);
		
	}
	else
		error("quelque chose cloche au niveau des arguments");
}
 
