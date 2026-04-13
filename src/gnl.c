/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:08:53 by whuth             #+#    #+#             */
/*   Updated: 2026/04/08 14:07:41 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	ft_free(char **arr)
{
	if (*arr != NULL)
	{
		free(*arr);
		*arr = NULL;
	}
}

char	*ft_join(int nl_pos, char **buffer)
{
	char	*tmp;
	char	*str;

	if (nl_pos <= 0)
	{
		if (nl_pos < 0 || **buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		str = *buffer;
		*buffer = NULL;
		return (str);
	}
	str = *buffer;
	tmp = ft_substr(*buffer, nl_pos, BUFFER_SIZE);
	str[nl_pos] = 0;
	*buffer = tmp;
	return (str);
}

char	*ft_read(int fd, char **buffer, char *tmp_buf)
{
	char	*nl;
	char	*tmp;
	ssize_t	rc;

	rc = 0;
	tmp = NULL;
	nl = ft_strchr(*buffer, '\n');
	while (!nl)
	{
		rc = read(fd, tmp_buf, BUFFER_SIZE);
		if (rc <= 0)
			return (ft_join(rc, buffer));
		tmp_buf[rc] = 0;
		tmp = ft_strjoin(*buffer, tmp_buf);
		ft_free(buffer);
		*buffer = tmp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (ft_join(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	char		*tmp_buf;
	char		*return_arr;
	static char	*buffer[MAX_FD + 1];

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (fd < 0)
	{
		if (-(fd) - 1 <= MAX_FD)
			ft_free(&buffer[-(fd) - 1]);
		return (NULL);
	}
	if (MAX_FD < fd)
		return (NULL);
	tmp_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buf)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	return_arr = ft_read(fd, &buffer[fd], tmp_buf);
	ft_free(&tmp_buf);
	return (return_arr);
}
