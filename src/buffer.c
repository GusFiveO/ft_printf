/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:14:51 by alorain           #+#    #+#             */
/*   Updated: 2021/12/09 15:34:24 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static void	flush_buff(char *buffer, size_t *n)
{
	write(1, buffer, *n);
	buffer[0] = '\0';	
	*n = 0;
}

static size_t	concat_buff(char *buffer, char *str, size_t n, size_t idx)
{
	size_t	i;
	size_t	j;

	i = idx;
	j = 0;
	/* while (buffer[i])
		i++; */
	while ( j < n && (i + j) < BUFFER_SIZE + 1)
	{
		buffer[i + j] = str[j];
		j++;
	}
	buffer[i + j] = '\0';
	return (j);
}

size_t	manage_buff(char *str, size_t n)
{
	static char		buffer[BUFFER_SIZE + 1];
	static size_t	idx = 0;
	static size_t	printed_char = 0;
	size_t			bytes_added;
	size_t			temp;
	size_t			new_n;

	/* printf("str in buff : %s\n", str);
	printf("     n buff : %ld\n", n); */
	if (!n && !str)
	{
		flush_buff(buffer, &idx);
		temp = printed_char;
		printed_char = 0;
		return (temp);
	}
	else
	{
		bytes_added = concat_buff(buffer, str, n, idx);
		new_n = n - bytes_added;
		idx += bytes_added;
		if (n + idx > BUFFER_SIZE)
		{
			flush_buff(buffer, &idx);
			manage_buff(&str[bytes_added], new_n);
		}
		printed_char += n;
		return (printed_char);
	}
}

void	write_buff(char *str, size_t n)
{
	manage_buff(str, n);
}