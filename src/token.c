/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:59:12 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/12 12:58:18 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static t_ttype	get_heredoc_type(char *cur)
{
	int	i;

	i = -1;
	while (cur[++i])
	{
		if (ft_isspace(cur[i]))
			continue ;
		else if (cur[i] == '"' || cur[i] == '\'')
			return (Heredoc);
		else
			return (HeredocExpand);
	}
	return (HeredocExpand);
}

static t_ttype	determine_ttype(char **cursor)
{
	char	*cur;
	t_ttype	out;

	cur = *cursor;
	out = Argument;
	if (cur[0] == '<' && cur[1] == '<')
	{
		out = get_heredoc_type(cur + 2);
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

static int	find_quotes(char **cur, int *qstate)
{
	int		i;
	bool	dquoted;
	bool	squoted;

	dquoted = **cur == '"';
	squoted = **cur == '\'' && !dquoted;
	*qstate = (dquoted || squoted);
	*cur += squoted || dquoted;
	i = 0;
	while ((*cur)[i] && !(ft_isdelim((*cur)[i]) && !dquoted && !squoted))
	{
		if ((*cur)[i] == '"' && !squoted)
			dquoted = false;
		if ((*cur)[i] == '\'' && !dquoted)
		{
			squoted = false;
			*qstate = 2;
		}
		if (((*cur)[i] == '"' && !squoted) || ((*cur)[i] == '\'' && !dquoted))
			break ;
		i++;
	}
	if (dquoted || squoted)
		return (syntaxerr('"' * !squoted * dquoted + '\'' * squoted), -1);
	return (i);
}

static bool	gnt_init(char **cursor, char **cur, t_ttype *type)
{
	while (ft_isspace(**cursor))
		(*cursor)++;
	if (!**cursor)
		return (false);
	*type = determine_ttype(cursor);
	*cur = *cursor;
	while (ft_isspace(**cur))
		(*cur)++;
	return (true);
}

t_token	*get_next_token(char **envp, char **cursor, int lexit)
{
	t_ttype	type;
	char	*cur;
	int		qstate;
	int		i;
	t_token	*out;

	if (!gnt_init(cursor, &cur, &type))
		return (NULL);
	if (type == Pipe)
		return (token_init(Pipe, ft_strdup("|"), NULL));
	i = find_quotes(&cur, &qstate);
	if (i == -1)
		return (NULL);
	if (i == 0 && qstate == 0)
		return (syntaxerr('>' * (type == OutFile || type == OutFileAppend) + '<'
				* (type == InFile || type == Heredoc)), NULL);
	out = token_init(type, ft_substr(cur, 0, i), NULL);
	if (out->type != Heredoc && out->type != HeredocExpand && qstate < 2
		&& !expand_str(envp, &out->token, lexit))
		return (free(out), NULL);
	*cursor = cur + i + (qstate > 0);
	if (qstate == 0 && ft_strlen(out->token) == 1 && ft_isspace(*out->token))
		return (token_destroy(out), get_next_token(envp, cursor, lexit));
	errno = EMORETOREAD * (*cursor && !ft_isdelim(**cursor));
	return (out);
}
