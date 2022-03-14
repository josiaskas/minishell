/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:28:14 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 23:41:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# include "minishell.h"

char	*make_prompt(int code, bool with_bar, char *path, char *git);

#endif
