/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:43:54 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/12 16:44:03 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	rotate(t_data *data, double rad)
{
	float new_dir_x;
    float new_dir_y; 

	new_dir_x = data->player->dir.x * cos(rad) - data->player->dir.y * sin(rad);
	new_dir_y = data->player->dir.x * sin(rad) + data->player->dir.y * cos(rad);
    data->player->dir.x = new_dir_x;
    data->player->dir.y = new_dir_y;
}

void	handle_rotation(int key, t_data *data)
{
	if (key == KEY_LEFT)
		data->player->rotating_left = 1;
	else if (key == KEY_RIGHT)
		data->player->rotating_right = 1;
}

void	handle_stop_rotation(int key, t_data *data)
{
	if (key == KEY_LEFT)
		data->player->rotating_left = 0;
	else if (key == KEY_RIGHT)
		data->player->rotating_right = 0;
}
