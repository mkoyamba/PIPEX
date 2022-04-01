/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:17 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/01 17:42:22 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		error_out(ERROR_ARG);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		error_out(ERROR_F1);
	fd2 = open(argv[3], O_RDONLY);
	if (fd2 < 0)
	{
		close(fd1);
		error_out(ERROR_F2);
	}
	ft_pipex(fd1, fd2, argv);
	return (0);
}