/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:27:07 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/03 12:38:56 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    manage_infile(t_data *data, int *pipefd)
{
    int fd;

    close(pipefd[READ]);
    dup2(pipefd[WRITE], STDOUT);
    close(pipefd[WRITE]);
    if (data->here_doc == NULL)
    {
        fd = open(data->here_doc, O_RDONLY);
        if (fd == -1)
            return (error("here_doc error\n", 1));
        dup2(fd, STDIN);
        close(fd);
    }
}

void    manage_outfile(t_data *data, int *pipefd)
{
    int fd;
    
    close(pipefd[READ]);
    close(pipefd[WRITE]);
    if (data->here_doc)
    {
        fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    else
    {
        fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    dup2(fd, STDOUT);
    close(fd);
}