/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:55 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/04 15:46:09 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdbool.h>

char	*prompt_create(char **buf, const char *path);
void	prompt_run(char **envp);
int		readcommand(char ***target_buf, char *prompt);

#endif
