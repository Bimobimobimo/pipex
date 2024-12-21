/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:03:37 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/21 10:02:49 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "printf.h"

typedef struct	s_pipex
{
	int		fd_file;
	int		pipe_fd[2]; //un fd de lecture et un d'ecriture
	int		prev_fd;
	pid_t	pid;
	int		cmd_nb;
	char	**tab;
	char	**env;
	int		cmd_i;
}	t_pipex;

// ~ Parsing & fork ~

void	command_parsing(t_pipex *pipex, int argc, char **argv, char **env);
void	processus_creation(t_pipex *pipex, int cmd_n, char **env);
void	fork_success(t_pipex *pipex);

// ~ Path & execution ~

void	get_path_1(t_pipex *pipex, char **env);
void	get_path_2(t_pipex *pipex, char *path_env);
void	get_command_path(t_pipex *pipex, char **path_file, char *path);
void	execution(t_pipex *pipex, char **path_file, char *cmd_path, int j);

void	last_cmd(t_pipex *pipex, int argc, char **argv, char **env);
void	last_fork_success(t_pipex *pipex, int argc, char **argv);

// ~ Utils ~

void	error_exit(char *s);
void	free_tab(char **tab, int j);

#endif
