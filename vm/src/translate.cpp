#include "../include/translate.h"
#include "../include/environment.h"
#include <cassert>
#include <cstring>

avm_memcell* avm_translate_operand (vmarg *arg, avm_memcell *reg) {
	switch (arg->type) {
		case global_a:	return &stack[AVM_STACKSIZE-1-arg->val];
		case local_a:	return &stack[bp-arg->val];
		case formal_a:	return &stack[bp+AVM_STACKENV_SIZE+1+arg->val];
		case retval_a:	return &retval;
		case number_a:	{
			reg->type = number_m;
			reg->data.numVal = numConsts.at(arg->val);
			return reg;
		}
		case string_a:	{
			reg->type = string_m;
			reg->data.strVal = strdup(strConsts.at(arg->val).c_str());
			return reg;
		}
		case bool_a:	{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}
		case nil_a:		{
			reg->type = nil_m;
			return reg;
		}
		case userFunc_a:	{
			reg->type = userFunc_m;
			reg->data.userFuncVal = arg->val;
			return reg;
		}
		case libFunc_a:	{
			reg->type = libFunc_m;
			reg->data.libFuncVal = strdup(libFuncs.at(arg->val).c_str());
			return reg;
		}
		default:		assert(0);
	}
	return NULL;
}
