/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:30:58 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/11 16:30:59 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	create_rgb(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
    return (r << 16 | g << 8 | b);
}

static int	repetion(t_map *map, char *type)
{
	if (ft_strcmp(type, "C") == 0 && map->ceiling_color != -1)
		return (ft_putstr_fd("File Error: Duplicate C Color\n", 2), 1);
	else if (ft_strcmp(type, "F") == 0 && map->floor_color != -1)
		return (ft_putstr_fd("File Error: Duplicate F Color\n", 2), 1);
	return (0);
}

int	rgb_parser(t_map *map, char *type, char *str)
{
	char		**rgb;
	int			int_rgb[3];
	int			i;

	if (repetion(map, type) == 1)
		return (-1);
	i = 0;
	rgb = ft_split(str, ',');
	if (rgb == NULL)
		return (-1);
	while (rgb[i] != NULL)
		i++;
	if (i != 3)
		return (ft_putstr_fd("File Error : Wrong RGB Values\n", 2), -1);
	int_rgb[0] = ft_atoi(rgb[0]);
	int_rgb[1] = ft_atoi(rgb[1]);
	int_rgb[2] = ft_atoi(rgb[2]);
	free_array_of_pointers((void **)rgb);
	if (ft_strcmp(type, "C") == 0)
		map->ceiling_color = create_rgb(int_rgb[0], int_rgb[1], int_rgb[2]);
	else if (ft_strcmp(type, "F") == 0)
		map->floor_color = create_rgb(int_rgb[0], int_rgb[1], int_rgb[2]);
	map->info++;
	return (0);
}