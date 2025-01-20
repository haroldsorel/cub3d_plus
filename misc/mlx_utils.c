/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:29:21 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/12/10 18:29:22 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void    mlx_draw_line(t_data *data, t_player *player, int color)
{
    double      y;
    double      x;
    int         i;

    i = 0;
    y = player->pos.y;
    x = player->pos.x;
    if ((player->dir.x == 0.0f || player->dir.x == -0.0f) && player->dir.x > 0.0f)
    {
        while ((data->map->matrix)[(int)(y + i) / data->map->grid_size][(int)x / data->map->grid_size] == '0')
        {
            my_mlx_pixel_put(&(data->img), (int)(player->pos.x), (int)(player->pos.y + i), color);
            i++;
        }
        return ;
    }
    if ((player->dir.x == 0.0f || player->dir.x == -0.0f) && player->dir.x < 0.0f)
    {
        while ((data->map->matrix)[(int)(y - i) / data->map->grid_size][(int)x / data->map->grid_size] == '0')
        {
            my_mlx_pixel_put(&(data->img), (int)(player->pos.x), (int)(player->pos.y - i), color);
            i++;
        }
        return ;
    }
    while ((data->map->matrix)[(int)y/data->map->grid_size][(int)x/data->map->grid_size] == '0')
    {
        my_mlx_pixel_put(&(data->img), (int)x, (int)y, color);
        y += player->dir.y;
        x += player->dir.x;
        i++;
    }
}


/*not a very efficient method, learn the midpoint cirlce algorithm to increase performance*/
void    mlx_draw_circle(t_data *data, t_player *player, int color)
{
    int radius;
    int i;
    int j;
    int x;
    int y;

    radius = (int)player->radius;
    i = 0;
    j = 0;
    x = (int)player->pos.x - radius;
    y = (int)player->pos.y - radius;
    while (i <= 2 * radius)
    {
        j = 0;
        while (j <=  2 * radius)
        {
            if (((i - radius) * (i - radius)) + ((j - radius) * (j - radius)) <=
                (radius * radius))
                my_mlx_pixel_put(&(data->img), x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void    mlx_draw_square(t_data *data, int x, int y, int color)
{
    int i;
    int j;
    int grid_size;

    grid_size = data->map->grid_size;
    i = 0;
    j = 0;
    while (j < grid_size)
    {
        i = 0;
        while (i < grid_size)
        {
            if (i == 0 || j == 0)
                my_mlx_pixel_put(&(data->img), x + i, y + j, BLUE);
            else
                my_mlx_pixel_put(&(data->img), x + i, y + j, color);
            i++;
        } 
        j++;
    }
}

int     mlx_get_color(t_img *img, int x, int y)
{
    char    *dst;
    int     color;

    dst = img->pixel_ptr + (y * img->line_len + x * (img->bpp / 8));
    color = *(unsigned int *)dst;
    return (color);    
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixel_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
