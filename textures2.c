/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:45:00 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 18:14:10 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*rm_xpm(char *str)
{
	int		i;
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
		(*str)[i++] = (index / 10) + 48;
		(c = (index % 10) + 48);
		tmp = rm_xpm((*str));
		if (index > 10)
			tmp = rm_last_c(tmp);
		tmp = str_add_end(tmp, c);
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
