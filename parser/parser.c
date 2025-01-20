/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:32:21 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/11 16:32:26 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	valid_input(t_data *data, char **elem)
{
	int	len;

	len = 0;
	(void)data;
	while (elem[len] != NULL)
		len++;
	if (len != 2)
		return (-1);
	return (0);
}

int	parse_elements(t_data *data, char **elem)
{
	if (valid_input(data, elem) == -1)
		return (ft_putstr_fd("File Error : Wrong Arguments\n", 2), -1);
	if (ft_strcmp(elem[0], "NO") == 0 || ft_strcmp(elem[0], "SO") == 0
		|| ft_strcmp(elem[0], "WE") == 0 || ft_strcmp(elem[0], "EA") == 0)
		return (texture_parser(data->map, elem[0], elem[1]));
	else if (ft_strcmp(elem[0], "F") == 0 || ft_strcmp(elem[0], "C") == 0)
		return (rgb_parser(data->map, elem[0], elem[1]));
	ft_putstr_fd("File Error : Wrong Arguments\n", 2);
	return (-1);
}

int	extract_info(t_data *data, char *line)
{
	//int		i;
	char	**elem;

	//i = 0;
	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	no_other_ws(line);
	if (data->map->info == 6)
	{
		elem = add_line_to_map(data->map->matrix, line);
		if (elem == NULL)
			return (-1);
		data->map->matrix = elem;
		return (1);
	}
	elem = ft_split(line, ' ');
	if (elem == NULL)
		return (-1);
	if (parse_elements(data, elem) == -1)
		return (free_array_of_pointers((void **)elem), -1);
	free_array_of_pointers((void **)elem);
	return (0);
}

int	parser(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (extract_info(data, line) == -1)
		{
			free_data(data);
			return (free(line), -1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (data->map->matrix == NULL)
	{
		ft_putstr_fd("File Error : No Map\n", 2);
		return (free_data(data), -1);
	}
	if (map_parser(data) == -1)
		return (free_data(data), -1);
	player_parser(data);
	return (0);
}