/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cryonayes <cryonayes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:15:52 by cryonayes         #+#    #+#             */
/*   Updated: 2021/11/10 18:16:18 by cryonayes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "str_utils.h"
#include "bsq/header_parser.h"

struct s_header	parse_header(int *fd)
{
	char			*buffer;
	unsigned int	counter;
	struct s_header	header;

	counter = 0;
	buffer = malloc(sizeof (char) * 16);
	while (counter < 16)
	{
		read(*fd, (char *)(buffer + sizeof (char) * counter), 1);
		if (buffer[counter] == '\n')
			break ;
		counter++;
	}
	header.fill_char = buffer[counter - 1];
	header.obstacle_char = buffer[counter - 2];
	header.empty_char = buffer[counter - 3];
	buffer[counter - 3] = '\0';
	header.map_size = str_to_int(buffer);
	if (header.map_size <= 0)
	{
		write(2, "map error\n", 10);
		exit(-1);
	}
	free(buffer);
	return (header);
}
