/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:26 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/25 15:36:42 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*  		==================(     INCLUDES     )==================		  */

# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>

/*  		==================(      MACROS      )==================		  */

# define ERROR_ARG "./pipex file1 cmd1 cmd2 file2"
# define ERROR_F1 "execve failed"
# define ERROR_F2 "execve failed"
# define ERROR_FORK "Il y a eu un problème lors du fork."

/*  		==================(    PROTOTYPES    )==================		  */

size_t	ft_strlen(char *str);
void	error_out(char *str);
char	**split_pipex(char *s, char c);
char	*get_path(char **env, char **command);
int		ft_pipex(int fd1, int fd2, char **av, char **env);
void	free_tab(char **tab);

#endif