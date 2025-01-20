/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:59:56 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/12 21:00:10 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


void move_forward(t_data *data, double distance)
{
    double new_pos_x;
    double new_pos_y;
    double checker_x;
    double checker_y;

    new_pos_x = data->player->pos.x + data->player->dir.x * distance;
    new_pos_y = data->player->pos.y + data->player->dir.y * distance;
    checker_x = new_pos_x + data->player->radius * data->player->dir.x;
    checker_y = new_pos_y + data->player->radius * data->player->dir.y;
    if ((data->map->matrix)[(int)(data->player->pos.y / data->map->grid_size)][(int)(checker_x / data->map->grid_size)] != '1')
        data->player->pos.x = new_pos_x;
    if ((data->map->matrix)[(int)(checker_y / data->map->grid_size)][(int)(data->player->pos.x / data->map->grid_size)] != '1')
        data->player->pos.y = new_pos_y;
}

void	move_backward(t_data *data, double distance)
{
	double  new_pos_x;
    double  new_pos_y;
    double  checker_x;
    double  checker_y;

	new_pos_x = data->player->pos.x + data->player->dir.x * distance;
	new_pos_y = data->player->pos.y + data->player->dir.y * distance;
    checker_x = new_pos_x - data->player->radius * data->player->dir.x;
    checker_y = new_pos_y - data->player->radius * data->player->dir.y;
    if ((data->map->matrix)[(int)(data->player->pos.y / data->map->grid_size)][(int)(checker_x / data->map->grid_size)] != '1')
        data->player->pos.x = new_pos_x;
    if ((data->map->matrix)[(int)(checker_y / data->map->grid_size)][(int)(data->player->pos.x / data->map->grid_size)] != '1')
        data->player->pos.y = new_pos_y;
}

void	move_right(t_data *data, double distance)
{
	double  new_pos_x;
    double  new_pos_y;
    double  checker_x;
    double  checker_y;

	new_pos_x = data->player->pos.x - data->player->dir.y * distance;
    new_pos_y = data->player->pos.y + data->player->dir.x * distance;
    checker_x = new_pos_x - data->player->radius * data->player->dir.y;
    checker_y = new_pos_y + data->player->radius * data->player->dir.x;
    if ((data->map->matrix)[(int)(data->player->pos.y / data->map->grid_size)][(int)(checker_x / data->map->grid_size)] != '1')
        data->player->pos.x = new_pos_x;
    if ((data->map->matrix)[(int)(checker_y / data->map->grid_size)][(int)(data->player->pos.x / data->map->grid_size)] != '1')
        data->player->pos.y = new_pos_y;
}

void	move_left(t_data *data, double distance)
{
	double  new_pos_x;
    double  new_pos_y;
    double  checker_x;
    double  checker_y;

	new_pos_x = data->player->pos.x + data->player->dir.y * distance;
    new_pos_y = data->player->pos.y - data->player->dir.x * distance;
    checker_x = new_pos_x + data->player->dir.y * data->player->radius;
    checker_y = new_pos_y - data->player->dir.x * data->player->radius;
    if ((data->map->matrix)[(int)(data->player->pos.y / data->map->grid_size)][(int)(checker_x / data->map->grid_size)] != '1')
        data->player->pos.x = new_pos_x;
    if ((data->map->matrix)[(int)(checker_y / data->map->grid_size)][(int)(data->player->pos.x / data->map->grid_size)] != '1')
        data->player->pos.y = new_pos_y;
}

void    move(t_data *data, int key, double distance)
{
    if (key == 'w')
        move_forward(data, distance);
    if (key == 's')
        move_backward(data, distance);
    if (key == 'a')
        move_left(data, distance);
    if (key == 'd')
        move_right(data, distance);
}