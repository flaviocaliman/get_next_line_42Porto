/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:27:56 by fgomes-c          #+#    #+#             */
/*   Updated: 2023/05/28 16:24:56 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - *find_char(): procura o caracter. O while faz a busca, se nao encontrar
// entra no lood if abaixo para verificar se o char procurado eh um nulo '\0';
// - strlen_until(): calcula comprimento de uma string ate encontrar um
// caractere a ser evitado "int avoid";
// - *previous_and_current(): concatena 2 strings e retorna um ponteiro
// para a string resultante;
// - strlen_until(): calcula o tamanho de uma string ate um caracter
// especificado (avoid);
// - *ft_memcpy(): copia uma string de origem (src) para uma 
// string de destino (dest) ate um comprimento especificado (n);
// - *cpy_buffer(): copia uma string ate um tamanho especificado (len) e 
// retorna um ponteiro para a copia resultante;

#include "get_next_line.h"

char	*find_char(const char *buffer, int find)
{
	if (!buffer)
		return (NULL);
	while (*buffer)
	{
		if (*(unsigned char *)buffer == (unsigned char)find)
			return ((char *)buffer);
		buffer++;
	}
	if (*(unsigned char *)buffer == (unsigned char)find)
		return ((char *)buffer);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*cpy_buffer(const char *buffer, size_t len)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (buffer[i] && i < len)
	{
		copy[i] = buffer[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	strlen_until(const char *str, int avoid)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != avoid)
		i++;
	return (i);
}

char	*previous_and_current(char *prev, const char *current)
{
	size_t	prev_len;
	size_t	curr_len;
	char	*sum;

	prev_len = 0;
	curr_len = 0;
	if (prev)
		prev_len = strlen_until(prev, '\0');
	curr_len = strlen_until(current, '\0');
	sum = (char *)malloc(prev_len + curr_len + 1);
	if (!sum)
		return (NULL);
	if (prev)
		ft_memcpy(sum, prev, prev_len);
	ft_memcpy(sum + prev_len, current, curr_len);
	sum[prev_len + curr_len] = '\0';
	if (prev)
		free(prev);
	return (sum);
}
