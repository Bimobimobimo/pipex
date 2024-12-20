/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:03:37 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/19 17:12:32 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define PATH

typedef struct	s_pipex
{
	int		fd_file;
	int		pipe_fd[2]; //un fd de lecture et un d'ecriture
	int		prev_fd;
	pid_t	pid;
	int		cmd_nb;
	char	**tab;
}	t_pipex;

void	processus_creation(t_pipex *pipex, int cmd_n, char **tab, char **env);
void	fork_succes(t_pipex *pipex);
void	execution(t_pipex *pipex, int i, char **env);
void	command_parsing(t_pipex *pipex, int argc, char **argv, char **env);
void	error_exit(char *s);
void	last_cmd(t_pipex *pipex, int argc, char **argv);

#endif
