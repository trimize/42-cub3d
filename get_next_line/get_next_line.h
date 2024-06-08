/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:10:54 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 17:56:40 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../includes/cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		has_end(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*line_dealer(char *updated);
char	*get_next_line(int fd);

#endif