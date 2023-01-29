/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:12:33 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/29 16:45:58 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define EM_DEL				" :: "
# define EM_INTERNAL		"an internal error occurred"
# define EM_PARSER			"parser exception"
# define EM_FILE_ERROR		"could not open file"
# define MEPARSE_NAN		"expected numeric value"
# define MEPARSE_NOEXIST	"unrecognized token"
# define MEPARSE_VAL_RANGE	"value out of range"
# define MEPARSE_MATP		"material not instantiated"
# define MEPARSE_BADCONTEXT	"argument not in valid context"
# define MEPARSE_ARGC		"invalid amount of arguments"

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
	size_t	line_num;
	size_t	word_num;
	t_mat	*default_matp;
}	t_parser;

typedef int	(*t_attr_dispatch)(t_parser *, t_tuple);

int		token_try_obj(char *word, t_parser *p);
int		token_try_light(char *word, t_parser *p);
int		token_try_attr(char *word, t_parser *p);
int		token_try_material(char *word, t_parser *p);
int		token_try_meta(char *word, t_parser *p);

int		set_attr(char *word, t_parser *p);

int		parser_exception(t_parser *p, char *word, const char *msg);

void	scene_apply(t_scene *ctx, t_parser *p);

#endif
