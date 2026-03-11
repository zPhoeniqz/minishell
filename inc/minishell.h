/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/01/30 17:16:48 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex.h"
# include <stdbool.h>

# define DEL " \t\n\r\v\f"

typedef struct s_tl
{
	char		**tokens;
	int			ll;
}				t_tl;

typedef struct s_vl
{
	bool		dq;
	char		*key;
	char		*value;
	struct s_vl	*next;
}				t_vl;

typedef struct s_data
{
	t_vl		*vl;
	t_tl		*tl;
}				t_data;

int				check_legit_var(int ac, char **av);
void			gettokens(char *input, t_data *data);
int				is_paren(char c);
unsigned int	count_elts(const char *s);
int				check_quote(char *s, size_t *elen);
int				del_occ(char c);
size_t			token_len(const char *s);
char			**strarr_destruct(char **in, int n);
int				is_sep(char c);

char			*ft_strcdup(const char *s, char c);

void			save_var(char *s, t_vl **var_list);
char			*find_val(char *s, t_vl **vl);

void			free_token_list(t_tl *tl);
void			free_var_list(t_vl *var_list);
#endif
