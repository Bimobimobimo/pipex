/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:03:34 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/20 15:50:22 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
