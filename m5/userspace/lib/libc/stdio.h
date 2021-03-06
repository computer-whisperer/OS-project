/*
  Milestone 3 userspace/lib/libc/stdio.h
  Group 3-C
  David Mehl, Christian Balcom, and Alexander Hirschfeld
 */

#ifndef _LIB_STDIO
#define _LIB_STDIO

void puts(char * str);
void gets(char * str);
void getDirList(char * fname, char * buff);
void exec(char * fname, int shouldWait);
void exit();
void kill(int proc);
void fread(char * fname, char * buf);
void fwrite(char * fname, char * buf);
void fdel(char * fname);
int __mkargv(int a, int b, int c, int d);
#endif
