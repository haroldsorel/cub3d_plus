/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:23:33 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/12/24 14:23:42 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void    init_dda(t_data *data, t_dda *dda, t_ray *ray)
{
    dda->x = (int)(data->player->pos.x / data->map->grid_size);
    dda->y = (int)(data->player->pos.y / data->map->grid_size);
    dda->delta_x = fabs(data->map->grid_size / ray->dir.x);
    dda->delta_y = fabs(data->map->grid_size / ray->dir.y);
    if (ray->dir.x < 0.0f)
    {
        dda->inc_x = -1;
        dda->len_x = fabs((data->player->pos.x - (dda->x * data->map->grid_size)) / ray->dir.x);
    }
    else
    {
        dda->inc_x = 1;
        dda->len_x = fabs((((dda->x + 1) * data->map->grid_size) - data->player->pos.x) / ray->dir.x);
    }
    if (ray->dir.y < 0.0f)
    {
        dda->inc_y = -1;
        dda->len_y = fabs((data->player->pos.y - (dda->y * data->map->grid_size)) / ray->dir.y);
    }
    else
    {
        dda->inc_y = 1;
        dda->len_y = fabs((((dda->y + 1) * data->map->grid_size) - data->player->pos.y) / ray->dir.y);
    }
}

static void get_dda_info(t_data *data, t_dda *dda, t_ray *ray)
{
    double  player_angle;
    double  ray_angle;
    double  angle_diff;

    if (ray->wall == 1)
        ray->len = dda->len_x - dda->delta_x;
    else
        ray->len = dda->len_y - dda->delta_y;
    player_angle = atan2(data->player->dir.y, data->player->dir.x);
    ray_angle = atan2(ray->dir.y, ray->dir.x);
    angle_diff = player_angle - ray_angle;
    ray->perp_len = ray->len * cos(angle_diff);
}

void    dda(t_data *data, t_ray *ray)
{
    int     wall;
    t_dda   dda;

    init_dda(data, &dda, ray);
    while ((data->map->matrix)[dda.y][dda.x] != '1')
    {
        if (dda.len_x < dda.len_y)
        {
            if (ray->dir.x > 0.0f)
                my_mlx_pixel_put(&(data->img), (dda.x + 1) * data->map->grid_size, data->player->pos.y + (dda.len_x * ray->dir.y), GREEN);
            else
                my_mlx_pixel_put(&(data->img), dda.x * data->map->grid_size, data->player->pos.y + (dda.len_x * ray->dir.y), GREEN);
            dda.x += dda.inc_x;
            dda.len_x += dda.delta_x;
            wall = 1;
        }
        else
        {
            if (ray->dir.y > 0.0f)
                my_mlx_pixel_put(&(data->img), data->player->pos.x + (dda.len_y * ray->dir.x),  (dda.y + 1) * data->map->grid_size, GREEN);
            else
                my_mlx_pixel_put(&(data->img), data->player->pos.x + (dda.len_y * ray->dir.x),  dda.y * data->map->grid_size, GREEN);
            dda.y += dda.inc_y;
            dda.len_y += dda.delta_y;
            wall = 0;
        }
    }
    ray->wall = wall;
    get_dda_info(data, &dda, ray);
}