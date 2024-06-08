/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:23:05 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 17:56:30 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	tablen(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	get_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid file.");
		exit(1);
	}
	return (fd);
}

int	ft_equalstr(char const *str, char const *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (!str[i] && !str2[i])
		return (1);
	return (0);
}
