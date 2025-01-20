/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:18:07 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/11 17:18:17 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	row_len(char **char_map)
{
	int	i;
	int	len;
	int	longest;

	longest = 0;
	i = 0;
	while (char_map[i] != NULL)
	{
		len = ft_strlen(char_map[i]);
		if (ft_strchr(char_map[i], '\n'))
			len--;
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

void	no_other_ws(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\v' || line[i] == '\f')
			line[i] = ' ';
		else if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}