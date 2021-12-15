/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cryonayes <cryonayes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:16:04 by cryonayes         #+#    #+#             */
/*   Updated: 2021/11/09 23:06:46 by cryonayes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/header_parser.h"
#include "bsq/bsq_solver.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		arg_iterator;
	int		file_descriptor;

	if (argc == 1)
	{
		file_descriptor = 1;
		solve_bsq(&file_descriptor);
		return (0);
	}
	arg_iterator = 1;
	while (arg_iterator < argc)
	{
		file_descriptor = open(argv[arg_iterator], O_RDONLY);
		if (file_descriptor == -1)
		{
			write(2, "Error opening file\n", 20);
			continue ;
		}
		solve_bsq(&file_descriptor);
		close(file_descriptor);
		arg_iterator++;
	}
}
