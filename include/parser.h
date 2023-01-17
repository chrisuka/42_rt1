/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:12:33 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/17 19:06:29 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define EPARSE_OK				0
# define EPARSE_INTERNAL		1
# define EPARSE_TOKEN_INVALID	2
# define EPARSE_TOKEN_UNKNOWN	3
# define EPARSE_TOKEN_NAN		4
# define EPARSE_FILE_ERROR		10

# define MPRE_PARSE	"parser_exception "

#if 1
enum e_token_id {
	tobj, tlight, tmaterial, tmeta, tnull
}	t_tokenid;
#endif

typedef struct s_attribute_data {
	int	type;
	int	val_req;
}	t_attr;

typedef struct s_parser_data {
	size_t	obj_count;
	size_t	light_count;
	size_t	mat_count;
	t_list	*obj;
	t_list	*mat;
	t_list	*lights;
	t_attr	attr;
	double	av[3];
	int		active_type;
	int		errorid;
	t_mat	*default_matp;
}	t_parser;

int		token_try_obj(char *word, t_parser *p);
int		token_try_light(char *word, t_parser *p);
int		token_try_attr(char *word, t_parser *p);

int		set_attr(char *word, t_parser *p);

int		parser_error_fatal(int ecode);
int		parser_exception(int ecode);

void	scene_apply(t_scene *ctx, t_parser *p);

#endif
