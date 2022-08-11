/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:07:12 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 11:44:55 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h" 

void *get_img(void *mlx,char *name)
{
	void *im;
	int x;
	int y;

	if (!(im = mlx_xpm_file_to_image(mlx,name,&x,&y)))
    	{
      		return(NULL);
    	}
	return im;
}
int cell_up(map *carte,int x, int y)
{
	if(carte->data[x][y] == '1')
		return(0);
	return(1);
}

int	mouse(map *carte)
{
	mlx_loop_end(carte->mlx);
}

void update(map *carte)
{	
	if(carte->data[carte->start.x][carte->start.y] == 'C')
	{
		carte->nb_food = carte->nb_food - 1;
		carte->data[carte->start.x][carte->start.y] = '0'; 
	}
	if(carte->data[carte->start.x][carte->start.y]  == 'E')
	{
		if(carte->nb_food == 0)
		{
			mlx_loop_end(carte->mlx);
		}
	}	
		
}

void mv_down(map *p)
{
	int x;
	
	if(cell_up(p,p->start.x + 1,p->start.y))
	{
		p->start.x = p->start.x + 1;
		p->mv = p->mv + 1;
		display_d(p->mv);	
		x = write(1,"\n",1);
	}
}
void mv_up(map *p)
{
	int x;
	
	if(cell_up(p,p->start.x - 1,p->start.y))
	{
		p->start.x = p->start.x - 1;
		p->mv = p->mv + 1;
		display_d(p->mv);	
		x =write(1,"\n",1);
	}
}
void mv_right(map *p)
{
	int x;
	if(cell_up(p,p->start.x,p->start.y + 1))
	{
		p->start.y = p->start.y + 1;
		p->mv = p->mv + 1;
		display_d(p->mv);	
		x =write(1,"\n",1);
	}
}
void mv_left(map *p)
{
	int x;	
	if(cell_up(p,p->start.x, p->start.y - 1))
	{
		p->start.y = p->start.y - 1;
		p->mv = p->mv + 1;
		display_d(p->mv);	
		x = write(1,"\n",1);
	}
}
int	key_win(int key,map *p)
{
	if(key == 119)
	{
		mv_up(p);
	}
	if(key == 97)
	{
		mv_left(p);
	}
	if(key == 115)
	{
		mv_down(p);
	}
	if(key == 100)
	{
		mv_right(p);
	}
	update(p);
	if(key == 65307)
		mlx_loop_end(p->mlx);
	print_map(p);
}

int get_images(map *carte)
{	
	t_img **tab;
	
	tab = malloc(sizeof(t_img *) * 6);
	if(!(tab[WALL] = get_img(carte->mlx,"images/wall.xpm")))
		return(0);	
	if(!(tab[FLOOR] = get_img(carte->mlx,"images/floor.xpm")))
		return(0);
	if(!(tab[FOOD] = get_img(carte->mlx,"images/food.xpm")))
		return(0);
	if(!(tab[END] = get_img(carte->mlx,"images/end.xpm")))
		return(0);
	if(!(tab[PLAYER] = get_img(carte->mlx,"images/player.xpm")))
		return(0);
	tab[5] = 0;
	carte->imgs = tab;
	return(1);
}
int print_cell(map *carte,int x,int y)
{
	char g;	
	g = carte->data[x][y];
	if(g == '1')
		mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[WALL],30*y,30*x);
	if(g == 'E')
		mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[END],30*y,30*x);
	if(g == '0')
		mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[FLOOR],30*y,30*x);
	if(g == 'C')	
		mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[FOOD],30*y,30*x);
	if(g == 'P')
		mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[FLOOR],30*y,30*x);
	mlx_put_image_to_window(carte->mlx,carte->win,carte->imgs[PLAYER],carte->start.y*30
	,carte->start.x*30);


}
void print_map(map *carte)
{
	int i ;
	int j ;
	
	i = 0;
	while(i	< carte->size_y)
	{	
		j = 0;
		while(j < carte->size_x)
		{
			print_cell(carte,i,j);
			j++;
		}	
		i++;
	}
}

int  init_window(map *carte,int x ,int y)
{
	void	*mlx;
	void	*win;
	
	if(!(mlx = mlx_init()))
	{
		return(0);
	}
	if(!(win = mlx_new_window(mlx,x,y,"j'aime les pates")))
	{
		return(0);
	}
	carte->mlx = mlx;
	carte->win = win;
	return(1);
}
