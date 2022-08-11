/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:55:14 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/11 10:57:59 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
#include "get_next_line.h"
#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <mlx_int.h>
#define WALL 0
#define END 1
#define PLAYER 2
#define FLOOR 3
#define FOOD 4




typedef struct{
	int x;
	int y;
}pos;
	
typedef struct{
	int size_x;
	int size_y;
	int nb_food;
	pos start;
	pos end;
	char **data;
	void *mlx;
	void *win;	
	t_img **imgs;
	int mv;
}map;

int	display_d(int nb);
void error(char *s);
int check_extension(char *filename,char *ext);
void clean_up(map *carte);
void cut_n(map *carte);
pos create_pos(int x,int y);
int check_all(map *carte);
int	mouse(map *carte);
int	expose(void *p);
int	key_win(int key,map *p);
void print_map(map *carte);
int get_images(map *carte);
int  init_window(map *carte,int x,int y);
void init_map(map *carte);
char **fill_tab(map *carte,char *name);
int read_map(char *name,map *m);
void edit_map(map *carte);
int check_rectangle(map *carte);
int check_border(map *carte);
int check_inside(map *carte);
#endif
