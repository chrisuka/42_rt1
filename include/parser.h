/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:12:33 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/12 13:57:04 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define EPARSE_OK				0
# define EPARSE_INTERNAL		1
# define EPARSE_TOKEN_INVALID	2
# define EPARSE_TOKEN_UNKNOWN	3
# define EPARSE_FILE_ERROR		10

# define MPRE_PARSE	"parser_exception "

#if 0
enum e_token_id {
	obj, light, material, meta_obj, meta_attr, null
}	t_tokenid;
#endif

typedef struct s_parser_data {
	t_list	*obj;
	t_list	*mat;
	t_list	*lights;
	void	*attrp;
	int		attr_val_req;
	int		errorid;
	size_t	obj_count;
	size_t	light_count;
	size_t	mat_count;
}	t_parser;

int		token_try_obj(char *word, t_parser *p);

int		parser_error_fatal(int ecode);
int		parser_exception(int ecode);

void	scene_apply(t_scene *ctx, t_parser *p);

#endif
