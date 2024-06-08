/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:46:03 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 15:37:05 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "get_next_line_utils.c"

char	*helper_ft(int fd, char *updated)
{
	int		char_num;
	char	*previous;

	char_num = 1;
	previous = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!previous)
		return (NULL);
	while (!has_end(updated) && char_num != 0)
	{
		char_num = read(fd, previous, BUFFER_SIZE);
		if (char_num == -1)
		{
			free(previous);
			return (NULL);
		}
		previous[char_num] = 0;
		updated = ft_strjoin_gnl(updated, previous);
	}
	free(previous);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*updated;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	updated = helper_ft(fd, updated);
	if (!updated || updated[0] == 0)
	{
		free(updated);
		updated = NULL;
		return (NULL);
	}
	line = line_dealer(updated);
	if (updated)
	{
		if (updated[0] == 0)
		{
			free (updated);
			updated = NULL;
		}
	}
	return (line);
}

/*
int main() {
	int fd = open("poem.txt", O_RDONLY);
	
	// char *line;
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	if (!line)
	// 	{
	// 		free(line);
	// 		break;
	// 	}
	// 	printf("%s", line);
	// 	free(line);
	// }
	



	
	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	char *line4 = get_next_line(fd);
	char *line5 = get_next_line(fd);
	char *line6 = get_next_line(fd);

	
	printf("%s", line1);
	printf("%s", line2);
	printf("%s", line3);
	printf("%s", line4);
	printf("%s", line5);
	printf("%s", line6);

	free(line1);
	free(line2);
	free(line3);
	free(line4);
	free(line5);
	free(line6);
	

	close (fd);
}
*/
