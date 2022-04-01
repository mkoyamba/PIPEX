/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:26 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/01 17:43:53 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*  		==================(     INCLUDES     )==================		  */

# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>

/*  		==================(      MACROS      )==================		  */

# define ERROR_ARG "./pipex file1 cmd1 cmd2 file2"
# define ERROR_F1 "Le premier file descriptor est mauvais."
# define ERROR_F2 "Le deuxième file descriptor est mauvais."

/*  		==================(    PROTOTYPES    )==================		  */

size_t	ft_strlen(char *str);
void	error_out(char *str);
void	ft_pipex(int fd1, int fd2, char **av);

#endif