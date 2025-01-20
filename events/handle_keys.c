/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:24:37 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/12 16:24:49 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	handle_escape(t_data *data)
{
	ft_putstr_fd("Exiting Cub3d\n", 1);
	free_data(data);
	exit(0);
}

int	handle_destroy(t_data *data)
{
	ft_putstr_fd("Exiting Cub3d\n", 1);
	free_data(data);
	exit(0);
}

int	handle_keys(int key, t_data *data)
{
	if (key == KEY_ESCAPE)
		handle_escape(data);
	else if (key == KEY_W)
		handle_movement(key, data);
	else if (key == KEY_A)
		handle_movement(key, data);
	else if (key == KEY_S)
		handle_movement(key, data);
	else if (key == KEY_D)
		handle_movement(key, data);
	else if (key == KEY_LEFT)
		handle_rotation(key, data);
	else if (key == KEY_RIGHT)
		handle_rotation(key, data);
	return (0);
}

int	handle_rkeys(int key, t_data *data)
{
	if (key == KEY_W)
		handle_stop_movement(key, data);
	else if (key == KEY_A)
		handle_stop_movement(key, data);
	else if (key == KEY_S)
		handle_stop_movement(key, data);
	else if (key == KEY_D)
		handle_stop_movement(key, data);
	else if (key == KEY_LEFT)
		handle_stop_rotation(key, data);
	else if (key == KEY_RIGHT)
		handle_stop_rotation(key, data);
	return (0);
}