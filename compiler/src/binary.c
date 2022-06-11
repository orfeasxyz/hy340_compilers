#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/binary.h"
#include "../include/target.h"

void create_binary(FILE *fout) {
  instruction inst;
  int i;
  char* str;
  double num;
  userfunc func;

  assert(fout);
  
  unsigned magic = 340200501u;
  fwrite(&magic, sizeof(magic), 1, fout);
  
  //strings
  fwrite(&currStrConsts, sizeof(currStrConsts), 1, fout);
  for(i = 0; i < currStrConsts; i++) {
    str = strConsts[i];
    fwrite(str, strlen(str) + 1, 1, fout);
  }


  //numbers
  fwrite(&currNumConsts, sizeof(currNumConsts), 1, fout);
  for(i = 0; i < currNumConsts; i++) {
    num = numConsts[i];
    fwrite(&num, sizeof(num), 1, fout);
  }

  //functions
  fwrite(&currUserFuncs, sizeof(currUserFuncs), 1, fout);
  for(i = 0; i < currUserFuncs; i++) {
    func = userFuncs[i];
    fwrite(&func.address, sizeof(func.address), 1, fout);
    fwrite(&func.localSize, sizeof(func.localSize), 1, fout);
    fwrite(func.id, strlen(func.id) + 1, 1, fout);
  }

  //libfuncs
  fwrite(&currNameLibfuncs, sizeof(currNameLibfuncs), 1, fout);
  for(i = 0; i < currNameLibfuncs; i++) {
    str = nameLibfuncs[i];
    fwrite(str, strlen(str) + 1, 1, fout);
  }

  //instructions
  fwrite(&currInstruction, sizeof(currInstruction), 1, fout);
  for(i = 0; i < currInstruction; i++) {
    inst = instructions[i];
    fwrite(&inst, sizeof(inst), 1, fout);
  }

  fclose(fout);
}