/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:17 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/04 20:43:02 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_out(char *str)
{
	write(2, str, ft_strlen(str));
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		error_out(ERROR_ARG);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		error_out(ERROR_F1);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		close(fd1);
		error_out(ERROR_F2);
	}
	ft_pipex(fd1, fd2, argv, env);
	return (0);
}