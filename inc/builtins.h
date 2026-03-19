/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:30:30 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/19 18:51:57 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

void	env(char **envp);
bool	export(char *varname, char *value);
void	pwd(void);
bool	unset(char ***envp, char *envname);

#endif
