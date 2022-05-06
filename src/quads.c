#include "quads.h"
#include <assert.h>

quad*		quads = NULL; // quad vector
unsigned	total = 0;
unsigned	currQuad = 0;

void expand (void) {
	assert(total == currQuad);
	quad *p = malloc(NEW_SIZE);
	if (quads) {
		memcpy(p, quads, CURR_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}

void emit (
		iopcode		op,
		expr*		arg1,
		expr*		arg2,
		expr*		result,
		unsigned	label,
		unsigned	line
		) {

	// If the vector of quad is full, expand length
	if (currQuad == total) {
		expand();
	}

	// Consturct new quad
	quad* p		= quads + currQuad++;
	p->arg1		= arg1;
	p->arg2		= arg2;
	p->result	= result;
	p->label	= label;
	p->line		= line;
}
