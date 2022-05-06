#ifndef QUADS_H
#define QUADS_H

typedef enum expr_t {
	var_e,
	tableitem_e,

	programfunc_e,
	libraryfunc_e,

	arithmexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,

	constnum_e,
	constbool_e,
	conststring_e,

	nil_e
} expr_t;

typedef struct expr {
	expr_t			type;
	symbol*			sym;
	expr*			index;
	double			numCosnt;
	char*			strConst;
	unsigned char	boolConst;

	expr*			next;
} expr;

typedef struct quad {
	iopcode		op;
	expr*		result;
	expr*		arg1;
	expr*		arg2;
	unsigned	label;
	unsigned	line;
} quad;

extern quad*	quads;
extern unsigned	total;
extern unsigned	currQuad;

#define EXPAND_SIZE 1024
#define CURR_SIZE	(total*sizeof(quad))
#define NEW_SIZE	(EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

void expand();
void emit (
		iopcode		op,
		expr*		arg1,
		expr*		arg2,
		expr*		result,
		unsigned	label,
		unsigned	line
		);

#endif // QUADS_H
