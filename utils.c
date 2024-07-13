/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:23:05 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 11:36:11 by mbrandao         ###   ########.fr       */
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
		free(call_cub()->path);
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

int rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	search_txt(t_cube *cub, char c)
{
	int		i;
	
	i = 0;
	if (c == 'D')
		return (10);
	while (i < 4)
	{
		if (cub->txt[i].type && cub->txt[i].type[0] == c)
			return (i);
		i++;
	}
	return (-1);
}

char *to_str(int n)
{
	int i;
	int len;
	char *str;
	char *tmp;

	if (n == 0)
	{
		str = (char *)malloc(2 * sizeof(char));
		str[0] = '0';
		return (str[1] = 0, str);
	}
	i = n;
	len = 0;
	while (i > 0 && ++len > -1)
		i /= 10;
	str = (char *)malloc((len + 1) * sizeof(char));
	tmp = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len)
		(tmp[i++] = n % (10) + 48, n /= 10);
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
