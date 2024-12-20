/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:45:54 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/20 18:18:03 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_parsing(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->tab = ft_split(argv + 2, " ");
	pipex->cmd_nb = argc - 3; // - nom programme, - nom fichier entree et - nom fichier sortie
	processus_creation(pipex, pipex->cmd_nb, pipex->tab, env);
	last_cmd(pipex, pipex->cmd_nb, pipex->tab, env);
	free_tab(pipex->tab, pipex->cmd_nb);
}

void	processus_creation(t_pipex *pipex, int cmd_n, char **tab, char **env)
{
	pipex->prev_fd = -1; // initialise a -1 car a l'appel de processus_creation, il n'y a pas de pipe precedent
	pipex->cmd_i = 0;
	while (pipex->cmd_i < cmd_n - 1) // jusqu'a l'avant-derniere commande
	{
		if (pipe(pipex->pipe_fd) == -1) // creation pipe : la fn pipe remplit le tableau pipe_fd[2] de pipe_fd[0] pour la lecture et pipe_fd[1] pour l'ecriture. La fn pipe retourne 0 en cas de succes et -1 en cas d'echec
			error_exit("Pipe creation error\n");
		pipex->pid = fork(); // creation processus enfant
		if (pipex->pid == -1)
			error_exit("Fork error\n");
		if (pipex->pid == 0) // si on est dans le processus enfant
		{
			fork_success(pipex);
			get_path_1(pipex, env);
		}
		close(pipex->pipe_fd[1]); // fermer fd d'ecriture inutile dans parent (c'est les processus enfants qui ecrivent)
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd); // fermer fd de lecture precedent
		pipex->prev_fd = pipex->pipe_fd[0]; // stocker fd de lecture pour le prochain processus
		pipex->cmd_i++;
	}
}

void	fork_success(t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
	{
		if (dup2(pipex->prev_fd, STDIN_FILENO) == -1) // l'entree STDIN devient prev_fd
			error_exit("Dup2 STDIN error\n");
		close(pipex->prev_fd);
	}
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1) // la sortie STDOUT devient pipe_fd
		error_exit("Dup2 STDOUT error\n");
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (!pipex->tab) //TODO : est-ce que tab[i] ?
		error_exit("Command parsing error\n");
}
