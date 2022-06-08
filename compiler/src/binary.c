#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary.h"
#include "target.h"

void create_binary(char* filename) {
  instruction inst;
  int i;
  char* str;
  double num;
  userfunc func;


  FILE* f = fopen(filename, "wb");
  if(!f) {
      printf("Error: Could not create file %s\n", filename);
      exit(1);
  }
  
  unsigned magic = 340200501u;
  fwrite(&magic, sizeof(magic), 1, f);
  
  //strings
  fwrite(&currStrConsts, sizeof(currStrConsts), 1, f);
  for(i = 0; i < currStrConsts; i++) {
    str = strConsts[i];
    fwrite(str, strlen(str) + 1, 1, f);
  }


  //numbers
  fwrite(&currNumConsts, sizeof(currNumConsts), 1, f);
  for(i = 0; i < currNumConsts; i++) {
    num = numConsts[i];
    fwrite(&num, sizeof(num), 1, f);
  }

  //functions
  fwrite(&currUserFuncs, sizeof(currUserFuncs), 1, f);
  for(i = 0; i < currUserFuncs; i++) {
    func = userFuncs[i];
    fwrite(&func.address, sizeof(func.address), 1, f);
    fwrite(&func.localSize, sizeof(func.localSize), 1, f);
    fwrite(func.id, strlen(func.id) + 1, 1, f);
  }

  //libfuncs
  fwrite(&currNameLibfuncs, sizeof(currNameLibfuncs), 1, f);
  for(i = 0; i < currNameLibfuncs; i++) {
    str = nameLibfuncs[i];
    fwrite(str, strlen(str) + 1, 1, f);
  }

  //instructions
  fwrite(&currInstruction, sizeof(currInstruction), 1, f);
  for(i = 0; i < currInstruction; i++) {
    inst = instructions[i];
    fwrite(&inst, sizeof(inst), 1, f);
  }

  fclose(f);
}