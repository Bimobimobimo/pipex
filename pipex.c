/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:03:34 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/21 10:01:15 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc > 4)
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
		ft_putstr_fd("Argument error : rerun with <./pipex> <file> ", 2);
		ft_putstr_fd("<at least 2 commands> <new file>", 2);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
