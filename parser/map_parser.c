/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:30:52 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/11 16:30:54 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void    calculate_grid_size(t_data *data)
{
    int map_height;
    int map_width;
    int ppg_height;
    int ppg_width;
    int i;

    i = 0;
    while ((data->map->matrix)[i] != NULL)
        i++;
    map_height = i;
    ppg_height = HEIGHT / map_height;
    i = 0;
    while ((data->map->matrix)[0][i] != '\0')
        i++;
    map_width = i;
    ppg_width = WIDTH / 2 / map_width; 
    if (ppg_height < ppg_width)
        data->map->grid_size= ppg_height;
    else
        data->map->grid_size = ppg_width;
}

char	*replace_word(char *word, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (word[i] == '\n')
			break ;
		new[i] = word[i];
		i++;
	}
	while (i < len)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**add_line_to_map(char **map, char *line)
{
	char	**new;
	int		i;

	i = 0;
	if (map == NULL)
		new = ft_calloc(2, sizeof(char *));
	else
	{
		while (map[i] != NULL)
			i++;
		new = ft_calloc(i + 2, sizeof(char *));
	}
	if (new == NULL)
		return (NULL);
	i = 0;
	while (map != NULL && map[i] != NULL)
	{
		new[i] = map[i];
		i++;
	}
	new[i] = ft_strdup(line);
	i++;
	new[i] = NULL;
	free(map);
	return (new);
}

static int	reformat_map(char **map)
{
	int		len;
	int		i;
	char	*new_word;

	len = row_len(map);
	i = 0;
	while (map[i] != NULL)
	{
		new_word = replace_word(map[i], len);
		if (new_word == NULL)
			return (-1);
		free(map[i]);
		map[i] = new_word;
		i++;
	}
	return (0);
}

int	map_parser(t_data *data)
{
	if (reformat_map(data->map->matrix) == -1)
		return (-1);
	if (is_valid_map(data->map->matrix) == 0)
		return (-1);
	calculate_grid_size(data);
	return (0);
}