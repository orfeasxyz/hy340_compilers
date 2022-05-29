#include "structs.h"
#include "target.h"

void generate(void){
    for(unsigned i = 0; i < total; i++) (*generators[quads[i].op])(quads + i);
}

