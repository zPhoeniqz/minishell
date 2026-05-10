/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:30:30 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/10 21:56:01 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

void	env(int ac, char **av, char **envp);
int		export(int ac, char **av, char ***envp);
void	pwd(int ac, char **av, char **envp);
int		unset(int ac, char **av, char ***envp);
int		echo(int ac, char **av, char **envp);
int		cd(int ac, char **av, char **envp);

// Utils
int		find_var(char **envp, char *varname);
bool	check_varname(const char *name);
#endif
