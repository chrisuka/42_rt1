/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:12:33 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/21 17:20:14 by ikarjala         ###   ########.fr       */
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
# define EPARSE_MATERIAL_INDEX	11

# define MPRE_PARSE	"parser_exception "

# define ATTRIX_POSITION	0
# define ATTRIX_ROTATION	1
# define ATTRIX_RADIUS		2
# define ATTRIX_MATERIALP	3
# define ATTRIX_INTENSITY	4
# define ATTRIX_COLOR		5
# define ATTRIX_GLOSS		6
# define ATTRIX_SPECULAR	7
# define ATTRIX_AMBIENT		8

enum e_token_id {
	tnull = -1,
	tobj = 0,
	tlight = 1,
	tmaterial = 2,
	tmeta = 3,
}	t_tokenid;

typedef union u_tuple {
	t_vec	v3;
	t_rgbf	rgb;
}	t_tuple;

typedef struct s_attribute_data {
	int	type;
	int	val_req;
}	t_attr;

typedef struct s_parser_data {
	t_cam	cam;
	double	ambient;
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

typedef int (*t_attr_dispatch)(t_parser *, t_tuple);

int		token_try_obj(char *word, t_parser *p);
int		token_try_light(char *word, t_parser *p);
int		token_try_attr(char *word, t_parser *p);
int		token_try_material(char *word, t_parser *p);
int		token_try_meta(char *word, t_parser *p);

int		set_attr(char *word, t_parser *p);

int		parser_error_fatal(int ecode);
int		parser_exception(int ecode);

void	scene_apply(t_scene *ctx, t_parser *p);

#endif
