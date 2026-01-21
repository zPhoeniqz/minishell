/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/01/21 18:23:13 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	del_occ(char c)
{
	int	i;

	i = 0;
	while (DEL[i])
	{
		if (DEL[i] == c)
			return (1);
		++i;
	}
	return (0);
}

static char	*del_strchr(char *s)
{
	while (*s)
	{
		if (del_occ(*s))
			return (s);
		++s;
	}
	return (NULL);
}

static unsigned int	count_elts(const char *s)
{
	unsigned int	elcount;
	unsigned int	sw;

	sw = 0;
	elcount = 0;
	while (*s)
	{
		if (!del_occ(*s) && sw == 0)
		{
			sw = 1;
			elcount++;
		}
		else if (del_occ(*s))
			sw = 0;
		s++;
	}	
	return (elcount);
}

static char	*skip_separators(char *in)
{
	while (del_occ(*in))
		in++;
	return (in);
}

static char	**strarr_destruct(char **in, unsigned int n)
{
	while (n >= 0)
		free(in[n--]);
	free(in);
	return (NULL);
}

static int	check_quote(char *s)
{
	int	i;
	char c;

	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		c = s[i];
		while (s[++i])
		{
			if (s[i] == c)
				return (1);
		}
		return (0);
	}
	return (1);
}


//TODO Handle quotes
//TODO Parse VARS like $VAR
//TODO DEBLOWT
char	**gettokens(char *input)
{
	int		elcount;
	char	**out;
	int		i;
	size_t	elen;

	elcount = (int)count_elts(input);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < elcount)
	{
		input = skip_separators(input);
		if (del_strchr(input) == NULL)
			elen = ft_strchr(input, '\0') - input;
		else
			elen = del_strchr(input) - input;
		out[i] = ft_calloc(elen + (elen > 0), 1);
		if (!out[i])
			return (strarr_destruct(out, i));
		if	(check_quote(input))
		{
			ft_strlcpy(out[i], input, elen + (elen > 0));
			input += elen;
		}
		else
			break ;
	}
	out[i] = NULL;
	return (out);
}

//*
int	main(void)
{
	int		i;
	char	*input;
	char	**tokens;

	input = "ls 3123  \"aasd  \"asdsdasd -a \n | cat\t  $VAR";
	tokens = gettokens(input);
	i = 0;
	while (tokens[i])
		ft_printf("%s\n", tokens[i++]);
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
//*/
