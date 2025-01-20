/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:29:08 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/12/10 18:29:09 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	*free_array_of_pointers(void **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

void	*free_map(t_map *map)
{
	free(map->no_text.path);
	free(map->so_text.path);
	free(map->we_text.path);
	free(map->ea_text.path);
	free(map->no_text.pixel_array);
	free(map->so_text.pixel_array);
	free(map->we_text.pixel_array);
	free(map->ea_text.pixel_array);
	free_array_of_pointers((void **)map->matrix);
	//free mlx stuff
	return (NULL);
}

void	*free_data(t_data *data)
{
	free_map(data->map);
	return (NULL);
}