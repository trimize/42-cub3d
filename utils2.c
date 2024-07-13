/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:22:08 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 17:59:07 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	*to_str(int n)
{
	int		i;
	int		len;
	char	*str;
	char	*tmp;

	if (n == 0)
		return (ft_strdup("0"));
	i = n;
	len = 0;
	while (i > 0 && ++len > -1)
		i /= 10;
	str = (char *)malloc((len + 1) * sizeof(char));
	tmp = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		tmp[i++] = n % (10) + 48;
		n /= 10;
	}
	i = -1;
	while (++i < len)
		str[i] = tmp[(len - 1) - i];
	return (free(tmp), str[i] = 0, str);
}

long int	get_current_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	set_size(t_map *map)
{
	int	i;
	int	big;

	i = 0;
	big = ft_strlen(map->map[0]);
	while (map->map[i])
		i++;
	map->rows = i;
	i = 1;
	while (map->map[i])
	{
		if ((int) ft_strlen(map->map[i]) > big)
			big = ft_strlen(map->map[i]);
		i++;
	}
	map->cols = big;
}

void	map_filler(t_map *map)
{
	int	i;
	int	cols;

	i = 0;
	set_size(map);
	while (map->map[i])
	{
		cols = ft_strlen(map->map[i]);
		if (cols < map->cols)
		{
			while (cols < map->cols)
			{
				map->map[i] = ft_strjoin_gnl(map->map[i], " ");
				cols++;
			}
		}
		i++;
	}
}

int	check_cub(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (len < 4)
		return (1);
	if (file[len] != 'b')
		return (1);
	if (file[len - 1] != 'u')
		return (1);
	if (file[len - 2] != 'c')
		return (1);
	if (file[len - 3] != '.')
		return (1);
	return (0);
}
