/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:53:38 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/12/19 00:53:47 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void    draw_ceiling_floor(t_data *data, t_ray *ray, int slice)
{
    int i;

    i = 0;
    while (i < ray->draw_start)
    {
        my_mlx_pixel_put(&(data->img2), slice, i, data->map->ceiling_color);
        i++;
    }
    i = ray->draw_end;
    while (i < HEIGHT - 1)
    {
        my_mlx_pixel_put(&(data->img2), slice, i, data->map->floor_color);
        i++;
    }
}

int apply_shading(int color, double factor)
{
    int r = (color >> 16) & 0xFF;  
    int g = (color >> 8) & 0xFF;   
    int b = color & 0xFF;     
    int a = (color >> 24) & 0xFF;

    r = (int)(r * factor);
    g = (int)(g * factor);
    b = (int)(b * factor);

    return (a << 24) | (r << 16) | (g << 8) | b;
}

void    draw_slice(t_data *data, t_ray *ray, int slice)
{
    int     i;
    int     color;
    double  ratio;
    int     offset;

    i = ray->draw_start;
    ratio = 1.0 * ray->text.width / ray->wall_height;
    offset = 0;
    if (ray->wall_height > HEIGHT - 1)
        offset = (ray->wall_height - HEIGHT - 1) / 2;
    draw_ceiling_floor(data, ray, slice);
    while (i < ray->draw_end)
    {
        ray->text_y = (i + offset - ray->draw_start) * ratio;
        color = ray->text.pixel_array[ray->text_y + (ray->text.width * ray->text_x)];
        if (ray->wall == 1)
            color = apply_shading(color, 0.8);
        my_mlx_pixel_put(&(data->img2), slice, i, color);
        i++;
    }
}

void    fill_tex_info(t_data *data, t_ray *ray)
{
    double  ratio;

    ratio = fmod(ray->wall_intercept, data->map->grid_size) / data->map->grid_size;
    ray->text_x = (int)(ratio * ray->text.width);
    //you may want to flip. look at vicode get_text_coord function
}

void    fill_ray_info(t_data *data, t_ray *ray)
{
    ray->wall_height = (data->map->grid_size * HEIGHT)/ ray->perp_len;
    ray->draw_start = HEIGHT / 2 - (ray->wall_height / 2);
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->wall_height + ray->draw_start;
    if (ray->draw_end > HEIGHT - 1)
        ray->draw_end = HEIGHT - 1;
    if (ray->wall == 1)
    {
        if (ray->dir.x > 0.0f)
            ray->text = data->map->we_text;
        else
            ray->text = data->map->ea_text;
        ray->wall_intercept = data->player->pos.y + (ray->len * ray->dir.y);
    }
    else
    {
        if (ray->dir.y > 0.0f)
            ray->text = data->map->no_text;
        else
            ray->text = data->map->so_text;
        ray->wall_intercept = data->player->pos.x + (ray->len * ray->dir.x);
    }
}

void    raycaster(t_data *data)
{
    t_ray   ray;
    double  angle;
    double  step;
    int     i;

    i = 0;
    step = FOV / (WIDTH / 2);
    angle = -M_PI / 6;
    while (angle < M_PI / 6)
    {
        ray.dir.x = data->player->dir.x * cos(angle) - data->player->dir.y * sin(angle);
        ray.dir.y = data->player->dir.x * sin(angle) + data->player->dir.y * cos(angle);
        dda(data, &ray);
        fill_ray_info(data, &ray);
        fill_tex_info(data, &ray);
        draw_slice(data, &ray, i);
        i++;   
        angle += step;
    }
}