/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cryonayes <cryonayes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:16:04 by cryonayes         #+#    #+#             */
/*   Updated: 2021/11/09 21:59:44 by cryonayes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/header_parser.h"
#include "bsq/bsq_solver.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int				file_descriptor;

	file_descriptor = open("grid.txt", O_RDONLY);
	if (file_descriptor == -1)
	{
		write(2, "Error while opening file\n", 25);
	}
	solve_bsq(&file_descriptor);
	return (0);
}
