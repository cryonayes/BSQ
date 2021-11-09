/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cryonayes <cryonayes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:15:39 by cryonayes         #+#    #+#             */
/*   Updated: 2021/11/09 22:17:29 by cryonayes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/header_parser.h"
#include "bsq/bsq_solver.h"
#include "print_utils.h"
#include "str_utils.h"
#include "two_d_arrays.h"
#include "math_utils.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

char	**transform_map(char **map, int size, t_header header)
{
	int		i;
	int		j;
	char	**map_copy;

	i = -1;
	map_copy = two_d_array('\0', size + 1, size + 1);
	while (++i < size)
	{
		j = -1;
		while (j++ < size)
		{
			if ((i == 0 || j == 0) && map[i][j] == header.empty_char)
			{
				map_copy[i][j] = 1;
			}
			else if (map[i][j] == header.obstacle_char)
				map_copy[i][j] = 0;
			else
				map_copy[i][j] = map[i][j];
		}
	}
	return (map_copy);
}

t_bsq_info	calculate_bsq(char **map, int map_size)
{
	t_bsq_info	info;
	int			i;
	int			j;

	info.max_possible = 0;
	i = 0;
	while (++i < map_size)
	{
		j = 0;
		while (++j < map_size)
		{
			if (map[i][j] == 0)
				continue ;
			map[i][j] = min_of_three(map[i - 1][j - 1], map[i - 1][j],
					map[i][j - 1]
					) + 1;
			if (map[i][j] > info.max_possible)
			{
				info.i = i;
				info.j = j;
				info.max_possible = map[i][j];
			}
		}
	}
	return (info);
}

void	get_bsq_result(char **map_t, char **map_o, int map_size, int max)
{
	int	i;
	int	j;
	int	i_max;
	int	j_max;

	i = -1;
	while (++i < map_size)
	{
		j = -1;
		while (++j < map_size)
		{
			if (map_t[i][j] == max)
			{
				i_max = i - 1;
				j_max = j;
				while (--i > i_max - max)
				{
					j = j_max;
					while (j > j_max - max)
						map_o[i + 1][j--] = 'x';
				}
				return ;
			}
		}
	}
}

void	solve_bsq(int *fd)
{
	char				**map_o;
	char				**map_t;
	t_header			map_header;
	t_bsq_info			info;

	map_header = parse_header(fd);
	map_o = two_d_array_from_file(fd, map_header.map_size);
	map_t = transform_map(map_o, map_header.map_size, map_header);
	info = calculate_bsq(map_t, map_header.map_size);
	get_bsq_result(map_t, map_o, map_header.map_size, info.max_possible);
	io_print_2d_array(map_o, map_header.map_size);
	free(map_t);
	free(map_o);
}
