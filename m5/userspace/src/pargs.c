/*
  userspace/src/shell.c
  Group 3-C
  David Mehl, Christian Balcom, and Alexander Hirschfeld
 */
#include <stdio.h>

int main(int a, char ** b) {
	
	while(a > 0) {
		puts(a[b]);
		a--;
	}
}