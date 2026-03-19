/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:41:36 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/17 20:55:17 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

void	*ft_realloc(void *ptr, size_t newsize);
void	arr_destroy(void **arr);
void	ft_env_destroy(char **envp);
void	ft_env_make_individual_alloc(char **envp);

#endif
