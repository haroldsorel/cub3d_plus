/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:06:18 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/12 16:06:26 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void    render_minimap(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while ((data->map->matrix)[y] != NULL)
    {
        x = 0;
        while ((data->map->matrix)[y][x] != '\0')
        {
            if ((data->map->matrix)[y][x] == '1')
                mlx_draw_square(data, x * data->map->grid_size, y * data->map->grid_size, WHITE);
            else
                mlx_draw_square(data, x * data->map->grid_size, y * data->map->grid_size, BLACK);
            x++;
        }
        y++;    
    }
}
