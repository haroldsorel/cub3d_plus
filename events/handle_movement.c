/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:43:25 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/12 16:43:38 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	handle_movement(int key, t_data *data)
{
	if (key == KEY_W)
		data->player->moving_forward = 1;
	else if (key == KEY_S)
		data->player->moving_back = 1;
	else if (key == KEY_A)
		data->player->moving_left = 1;
	else if (key == KEY_D)
		data->player->moving_right = 1;
}

void	handle_stop_movement(int key, t_data *data)
{
	if (key == KEY_W)
		data->player->moving_forward = 0;
	else if (key == KEY_S)
		data->player->moving_back = 0;
	else if (key == KEY_A)
		data->player->moving_left = 0;
	else if (key == KEY_D)
		data->player->moving_right = 0;
}