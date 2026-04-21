/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:51:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/21 19:40:46 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.h"
#include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_parsed_item	t_parsed_item;

typedef struct s_command
{
	int							argc;
	char						**argv;
	t_parsed_item				*input;
	t_parsed_item				*output;
}								t_command;

typedef enum e_cmdtype
{
	Command,
	File,
}								t_cmdtype;

typedef union u_parsed_content
{
	char						*path;
	t_command					*command;
}								t_parsed_content;

/*
 * parsed item is either a fully parsed command (variables expanded,
	quotes removed etc),
 * or a file used in a redirection.*/
typedef struct s_parsed_item
{
	t_cmdtype					type;
	t_parsed_content			content;
}								t_parsed_item;

static void	seterr(char *problematic_cmd)
{
	errno = EINVAL;
	perror(problematic_cmd);
}

static bool	ft_isspace(char c)
{
	return (ft_strchr(" \f\n\r\t\v", c) != NULL);
}

static bool						add_arg(t_command *target, char *start,
									char *end);

static bool	expand(char **s)
{
	char	*cursor;

	while (1)
	{
		cursor = ft_strchr(*s, '<');
		if (!cursor)
			cursor = ft_strchr(*s, '>');
		if (!cursor)
			cursor = ft_strchr(*s, '$');
		if (!cursor)
			break ;
	}
}

static t_command	*parse_single(char *s, size_t size)
{
	t_command	*out;
	char		*cursor;
	char		*next;

	out = malloc(sizeof(t_command));
	if (!out)
		return (perror(NULL), NULL);
	out->argv = NULL;
	out->argc = 0;
	cursor = s - 1;
	while (++cursor < s + size)
	{
		if (ft_isspace(*cursor))
			continue ;
		else if (*cursor == '"' || *cursor == '\'')
		{
			next = ft_strchr(cursor + 1, *cursor);
			if (!next)
				return (free(out), seterr(cursor), NULL);
			if (!add_arg(out, cursor + 1, next - 1))
				return (free(out), NULL);
			if (*cursor == '"' && !expand(out->argv + out->argc - 1))
				return (free(out), NULL);
			cursor = next;
			continue ;
		}
		next = cursor;
		while (*next != '"' && *next != '\'' && !ft_isspace(*next) && next < s
			+ size)
			next++;
		if (!add_arg(out, cursor, next - 1))
			return (free(out), NULL);
		if (!expand(out->argv + out->argc - 1))
			return (free(out), NULL);
		cursor = next - 1;
	}
	return (out);
}

static t_command	**cmd_append(t_command **arr, char *s, size_t strsize)
{
	size_t		arrsize;
	t_command	**narr;

	arrsize = 0;
	while (arr[arrsize])
		arrsize++;
	narr = ft_realloc(arr, (arrsize + 2) * sizeof(t_command *));
	if (!arr)
		return (free(arr), perror(NULL), NULL);
	arr = narr;
	arr[arrsize + 1] = NULL;
	arr[arrsize] = parse_single(s, strsize);
	if (arr[arrsize])
		return (free(arr), NULL);
	return (arr);
}

/*
 * Parses the given string s.
 * If successful: Returns a list of t_command, terminated by a NULL.
 * If not successful: Prints error to stderr, returns NULL.
 * */
t_command	**parse(char *s, char **infile, char **outfile)
{
	t_command	**out;
	int			i;
	bool		quotes;
	int			cmd_start;
	int			cmd_count;

	cmd_count = 0;
	cmd_start = 0;
	quotes = false;
	out = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			quotes = !quotes;
		else if (s[i] == '|' && !quotes)
		{
			out = cmd_append(out, s + cmd_start, i);
			if (!out)
				return (NULL);
			cmd_start = i + 1;
			cmd_count++;
		}
		i++;
	}
	if (quotes)
		return (free(out), seterr(s + cmd_start), NULL);
	out = cmd_append(out, s + cmd_start, ft_strlen(s + cmd_start));
	if (!out)
		return (NULL);
	return (out);
}
