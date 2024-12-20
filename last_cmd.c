/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:37:40 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/20 18:35:24 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_cmd(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (pipe(pipex->pipe_fd) == -1)
		error_exit("Pipe creation error\n");
	pipex->pid = fork();
	if (pipex->pid == -1)
		error_exit("Fork error\n");
	if (pipex->pid == 0)
	{
		last_fork_success(pipex, argc, argv);
		get_path_1(pipex, env);
	}
	close(pipex->pipe_fd[1]); // fermeture fd d'ecriture, inutile dans pid parent
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
}

void	last_fork_success(t_pipex *pipex, int argc, char **argv)
{
	int	new_file_fd;
	
	if (pipex->prev_fd != -1)
	{
		if (dup2(pipex->prev_fd, STDIN_FILENO) == -1)
			error_exit("Dup2 error\n");
		close(pipex->prev_fd);
	}
	new_file_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644); //TRUNC met le contenu du fichier a zero s'il existe deja. 0644 accorde lecture et ecriture au proprietaire et lecture seule pour les autres utilisateurs
	if (new_file_fd == -1)
		error_exit("File creation error\n");
	if (dup2(pipex->pipe_fd[1], new_file_fd) == -1)
		error_exit("Dup2 redirecting to new_file error\n");
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(new_file_fd); //TODO verifier si au bon endroit
	if (!pipex->tab) //TODO : est-ce que tab[i] ?
		error_exit("Command parsing error\n");
}
