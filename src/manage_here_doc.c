/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:30:11 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/03 12:41:34 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	manage_here_doc(t_data *data)
{
	char *line;
	int pipefd[2];
    int len;

	if (pipe(pipefd) == -1)
		error("pipe failed\n", 1);
	while (1)
	{
		ft_putstr("here_doc>");
		line = get_next_line(STDIN);
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, data->limiter) == 0 || line == NULL)
		{
			free(line);
			break ;
		}
		line[len] = '\n';
		write(pipefd[WRITE], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN);
	close(pipefd[READ]);
}
