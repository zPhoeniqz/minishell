/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/01/26 17:05:21 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex.h"

# define DEL " \t\n\r\v\f"

char			**gettokens(char *input);
int				is_paren(char c);
unsigned int	count_elts(const char *s);
int				check_quote(char *s, size_t *elen);
int				del_occ(char c);
size_t			token_len(const char *s);
char			**strarr_destruct(char **in, int n);
int				is_sep(char c);

char	*ft_strcdup(const char *s, char c);

#endif
