/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/01/22 15:03:29 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex.h"

# define DEL " \t\n\r\v\f"

int				del_occ(char c);
int				check_quote(char *s, size_t *elen);
unsigned int	count_elts(const char *s);
size_t			token_len(const char *s);
char			*del_strchr(char *s);

#endif
