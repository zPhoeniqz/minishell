/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:51:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/04 15:44:09 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool	ft_isdelim(char c)
{
	return (ft_isspace(c) || c == '|' || c == '<' || c == '>' || c == '"'
		|| c == '\'' || c == '\0');
}

bool	expand_str(char **envp, char **s)
{
	bool	squoted;
	char	*out;
	int		i;
	int		end;
	char	c;
	char	*value;
	size_t	nsize;

	squoted = false;
	out = NULL;
	if (!*s)
		return (false);
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			squoted = !squoted;
		if (!squoted && (*s)[i] == '$')
		{
			end = i + 1;
			while (!ft_isdelim((*s)[end]))
				end++;
			c = (*s)[end];
			(*s)[end] = 0;
			value = ft_getenv(envp, *s + i + 1);
			if (!value)
				value = " ";
			(*s)[end] = c;
			nsize = i + ft_strlen(value) + ft_strlen(*s + end) + 1;
			out = ft_calloc(nsize, 1);
			if (!out)
				return (free(*s), false);
			ft_memcpy(out, *s, i);
			ft_strlcat(out, value, nsize);
			ft_strlcat(out, *s + end, nsize);
			free(*s);
			*s = out;
		}
		i++;
	}
	return (true);
}

static t_ttype	determine_ttype(char **cursor)
{
	char	*cur;
	t_ttype	out;

	cur = *cursor;
	out = Argument;
	if (cur[0] == '<' && cur[1] == '<')
	{
		out = Heredoc;
		cur++;
	}
	else if (cur[0] == '<')
		out = InFile;
	else if (cur[0] == '>' && cur[1] == '>')
	{
		out = OutFileAppend;
		cur++;
	}
	else if (cur[0] == '>')
		out = OutFile;
	else if (cur[0] == '|')
		out = Pipe;
	cur += out != Argument;
	*cursor = cur;
	return (out);
}

static t_token	*token_init(t_ttype type, const char *str, t_token *next)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->token = ft_strdup(str);
	if (!tok->token)
		return (free(tok), NULL);
	tok->type = type;
	tok->next_token = next;
	return (tok);
}

static t_token	*get_next_token(char **envp, char **cursor)
{
	t_ttype	type;
	char	*cur;
	bool	dquoted;
	bool	squoted;
	int		i;
	char	c;
	t_token	*out;

	while (ft_isspace(**cursor))
		(*cursor)++;
	if (!**cursor)
		return (NULL);
	type = determine_ttype(cursor);
	if (type == Pipe)
		return (token_init(Pipe, "|", NULL));
	cur = *cursor;
	while (ft_isspace(*cur))
		cur++;
	dquoted = *cur == '"';
	squoted = *cur == '\'';
	cur += squoted || dquoted;
	i = 0;
	while (cur[i])
	{
		if (ft_isdelim(cur[i]) && !dquoted && !squoted)
			break ;
		if (cur[i] == '"' && !squoted)
		{
			dquoted = false;
			break ;
		}
		if (cur[i] == '\'' && !dquoted)
		{
			squoted = false;
			break ;
		}
		i++;
	}
	if (squoted || dquoted || i == 0)
		return (NULL);
	c = cur[i];
	cur[i] = 0;
	out = token_init(type, cur, NULL);
	if (out->type != Heredoc && !expand_str(envp, &out->token))
		return (free(out), NULL);
	cur[i] = c;
	*cursor = cur + i + (cur[i] == '"' || cur[i] == '\'');
	return (out);
}

t_tl	*parse(char **envp, char *src)
{
	char	**cursor;
	t_tl	*out;
	t_token	*cur_token;

	cursor = &src;
	out = malloc(sizeof(t_tl));
	if (!out)
		return (NULL);
	out->ll = 0;
	out->tokens = get_next_token(envp, cursor);
	cur_token = out->tokens;
	while (cur_token)
	{
		out->ll++;
		cur_token->next_token = get_next_token(envp, cursor);
		cur_token = cur_token->next_token;
	}
	return (out);
}
