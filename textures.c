/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:33:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/15 17:31:38 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	load_texture(t_cube *cub, t_txt *txt)
{
	txt->img = mlx_xpm_file_to_image(cub->con, txt->path,
			&txt->width, &txt->height);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
			&txt->line_length, &txt->endian);
}

void	load_textures(t_cube *cub, t_txt *txt, int num)
{
	int	i;

	i = 0;
	while (i < num)
		load_texture(cub, &txt[i++]);
}

void	increment_alphabet(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] < 65 || str[i] > 90))
		i++;
	str[i] = 65 + index;
}

char	*str_add(char *str, char c)
{
	int	i;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = 0;
	free(str);
	return (tmp);
}

char	*rm_last_c(char *str)
{
	int	i;
	char	*tmp;

	tmp = (char *)malloc(ft_strlen(str) * sizeof(char));
	i = 0;
	while (i < (int)(ft_strlen(str) - 1))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	free(str);
	return (tmp);
}

char	*rm_xpm(char *str)
{
	int	i;
	char	*tmp;

	tmp = (char *)malloc((ft_strlen(str) - 3) * sizeof(char));
	i = 0;
	while (i < (int)(ft_strlen(str) - 4))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

void	increment_numbers(char **str, int index)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	while ((*str)[i] && ((*str)[i] < 48 || (*str)[i] > 57))	
		i++;
	if (index >= 10)
	{
		(*str)[i] = (index / 10) + 48;
		(c = (index % 10) + 48, i++);
		tmp = rm_xpm((*str));
		if (index > 10)
			tmp = rm_last_c(tmp);
		tmp = str_add(tmp, c);
		if (index > 10)
			tmp = ft_strjoin_gnl(tmp, &((*str)[i + 1]));
		else
			tmp = ft_strjoin_gnl(tmp, &((*str)[i]));
		(free((*str)), (*str) = ft_strdup(tmp));
		free(tmp);
		return ;
	}
	else
		(*str)[i] = 48 + index;
}
