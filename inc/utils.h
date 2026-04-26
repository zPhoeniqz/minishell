/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:41:36 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/15 15:11:23 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>

void	*ft_realloc(void *ptr, size_t newsize);
void	arr_destroy(void **arr);
void	ft_env_destroy(char **envp);
void	ft_env_make_individual_alloc(char **envp);
int		find_env(const char **envp, const char *name);
int		ft_setenv(char **envp, const char *name, const char *value,
			bool rewrite);

#endif
