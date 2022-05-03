/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:35:07 by jmorneau          #+#    #+#             */
/*   Updated: 2022/05/02 22:20:38 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next_line(char *stach)
{
	char	*new_stach = NULL;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stach[i] && stach[i] != '\n')
		i++;
	if (!stach[i])
		return (NULL);
	new_stach = ft_calloc(ft_strlen(stach) - i + 1, sizeof(char));
	i++;
	while (stach[i])
		new_stach[j++] = stach[i++];
	free(stach);
	new_stach[j] = '\0';
	return (new_stach);
}

char	*ft_line(char *stach)
{
	int		i;
	char	*line;

	i = 0;
	if (!*stach)
		return (NULL);
	while (stach[i] && stach[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (stach[i] && stach[i] != '\n')
	{
		line[i] = stach[i];
		i++;
	}
	if (stach[i] && stach[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_free(char *stach, char *buffer)
{
	char	*join;

	join = ft_strjoin(stach, buffer);
	free (stach);
	return (join);
}

char	*read_file(int fd, char *stach)
{
	char	*buffer;
	int		bytes_read;

	if (!stach)
		stach = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stach = ft_free(stach, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (stach);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stach = read_file(fd, stach);
	if (!stach)
		return (NULL);
	line = ft_line(stach);
	stach = ft_next_line(stach);
	return (line);
}

 int main()
 {
 	int fd;
 	char *line;

 	fd = open("text.txt", O_RDONLY);
 	while (1)
 	{
 		line = get_next_line(fd);
 		if (line == NULL)
 			break;
 		printf("%s", line);
 		free(line);
 	}
 	return (0);
 }