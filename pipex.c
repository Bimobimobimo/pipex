/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:03:34 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/20 10:58:07 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_cmd(t_pipex *pipex, int argc, char **argv)
{
	//TODO creer processus enfant
	//TODO rediriger entree standard vers pipe precedent
	//TODO executer commande
}

void	error_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	command_parsing(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->tab = ft_split(argv + 2, " ");
	pipex->cmd_nb = argc - 3; // - nom programme, - nom fichier entree et - nom fichier sortie
	processus_creation(pipex, pipex->cmd_nb, pipex->tab, env);
	last_cmd(pipex, pipex->cmd_nb, pipex->tab);
	free_tab(pipex->tab, pipex->cmd_nb);
}

void	execution(t_pipex *pipex, int i, char **env)
{
	// obtenir PATH des commandes (dans terminal : echo $PATH/commande ? -> split ":")
	char	*path_env; //= getenv("PATH"); //TODO
	char	*path;
	char	**path_file;
	
	if (!path_env)
		error_exit("Path not found\n");
	path = ft_strdup(path_env);
	if (!path)
		error_exit("Malloc error\n");
	path_file = ft_split(path, ":");
	// utiliser fontion access
	
	execve(PATH, pipex->tab[i], env);
}

void	fork_succes(t_pipex *pipex)
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
	if (!pipex->tab)
		error_exit("Command parsing error\n");
}

void	processus_creation(t_pipex *pipex, int cmd_n, char **tab, char **env)
{
	int	i; //pour aller de commande en commande : tab[i]
	
	pipex->prev_fd = -1; // initialise a -1 car a l'appel de processus_creation, il n'y a pas de pipe precedent
	i = 0;
	while (i < cmd_n - 1) // jusqu'a l'avant-derniere commande
	{
		if (pipe(pipex->pipe_fd) == -1) // creation pipe : la fn pipe remplit le tableau pipe_fd[2] de pipe_fd[0] pour la lecture et pipe_fd[1] pour l'ecriture. La fn pipe retourne 0 en cas de succes et -1 en cas d'echec
			error_exit("Pipe creation error\n");
		pipex->pid = fork(); // creation processus enfant
		if (pipex->pid == -1)
			error_exit("Fork error\n");
		if (pipex->pid == 0) // si on est dans le processus enfant
		{
			fork_success(pipex);
			execution(pipex, i, env);
		}
		close(pipex->pipe_fd[1]); // fermer fd d'ecriture inutile dans parent (c'est les processus enfants qui ecrivent)
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd); // fermer fd de lecture precedent
		pipex->prev_fd = pipex->pipe_fd[0]; // stocker fd de lecture pour le prochain processus
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc >= 4)
	{
		pipex.fd_file = open(argv[1], O_RDONLY);
		if (pipex.fd_file == -1)
		{
			perror("Error when opening file\n");
			exit(EXIT_FAILURE);
		}
		command_parsing(&pipex, argc, argv, env);
		close(pipex.fd_file);
	}
	else
	{
		perror("Argument error : rerun with <./pipex> <file> ");
		perror("<at least 2 commands> <new file>");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
