/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:03:05 by fgomes-c          #+#    #+#             */
/*   Updated: 2023/05/29 18:38:44 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -*get_current_buffer(): le e retorna o conteudo de um buffer associado a um
// determinado "fd" ate encontrar uma quebra de linha ou o final do arquivo;
// -read(): usada para ler dados de arquivos regulares, dispositivos ou outros
// fluxos de entrada/saída. Retorna o numero de bytes lidos;
#include "get_next_line.h"

static char	*get_current_buffer(int fd, char *buffer)
{
	char	*current;
	ssize_t	bytes;

	bytes = 1;
	current = (char *)malloc(BUFFER_SIZE + 1);
	if (!current)
		return (NULL);
	while (bytes > 0 && !find_char(buffer, '\n'))
	{
		bytes = read(fd, current, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free(current);
			free(buffer);
			return (NULL);
		}
		current[bytes] = '\0';
		buffer = previous_and_current(buffer, current);
	}
	free(current);
	if (strlen_until(buffer, '\0') > 0)
		return (buffer);
	return (NULL);
}

static char	*get_line(char **buffer)
{
	char	*line;
	char	*keep;
	size_t	until_null;
	size_t	until_new;

	until_new = strlen_until(*buffer, '\n');
	if ((*buffer)[until_new] == '\n')
		until_new++;
	line = cpy_buffer(*buffer, until_new);
	if (!line)
		return (NULL);
	until_null = strlen_until(*buffer, '\0');
	keep = cpy_buffer(*buffer + until_new, until_null - until_new + 1);
	if (!keep)
	{
		free (keep);
		free (line);
		return (NULL);
	}
	free (*buffer);
	*buffer = keep;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_current_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(&buffer);
	if (!buffer[0])
	{
		free (buffer);
		buffer = NULL;
	}
	return (line);
}
/*
int main()
{
	int fd;
	char	*line;
	fd = open("teste.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	close(fd);
}
*/
