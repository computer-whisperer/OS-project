/*
  Milestone 4 userspace/src/shell.c
  Group 3-C
  David Mehl, Christian Balcom, and Alexander Hirschfeld
 */

#include <stdio.h>
#include <string.h>

#define HARDCODE 1

int main() {
  char cmdBuff[256], pathBuff[512], fileBuff[13000], temp[256];
  int i, j, k, equals, ind = 0;
  int  c, len, place = 0;
  for(i = 0; i < 256; i++) {
    cmdBuff[i] = 0;
  }
  cmdBuff[0] = 0;
  pathBuff[0] = 0;
  fileBuff[0] = 0;
  puts("# ");
  gets(cmdBuff);
  removeLinefeed(cmdBuff);
      
  if (HARDCODE) {
    if (!strncmp("type", cmdBuff, 4)) {
      if (cmdBuff[5] == '\0') {
	puts("Invalid arguments to type command\n");
	exit();
      }
      fread(&cmdBuff[5], fileBuff);
      puts(fileBuff);
      exit();
    } else if(!strncmp("execute", cmdBuff, 7)) {
      exec(cmdBuff);
      /*interrupt(0x21, 4, cmdBuff, 0x2000, 0);*/
      
    } else if (!strncmp("delete", cmdBuff, 6)) {
      if (cmdBuff[8] == '\0') {
	puts("Invalid arguments to delete command\n");
	exit();
      }
      fdel(&cmdBuff[8]);
    } else if (!strncmp("copy", cmdBuff, 4)) {
      if(cmdBuff[6] == '\n') {
	puts("Invalid inputs to copy command\n");
	exit();
      }
      
      fread(&cmdBuff[6], fileBuff);
      c = 6;
      while(1) {
	if(cmdBuff[c] == ' ')
	  break;
	if(cmdBuff[c] == '\0') {
	  puts("Invalid output file\n");
	  exit();
	}
	c++;
      }
      c++;
      if(cmdBuff[c] == '\0') {
	puts("Invalid output file\n");
	exit();
      }
      fwrite(&cmdBuff[c], fileBuff);
      
    } else if (!strncmp("dir", cmdBuff, 3)) {
      if (cmdBuff[4] == '\0') {
	puts("Invalid arguments to dir command\n");
	exit();
      }
      getDirList(&cmdBuff[4], fileBuff);
    } else if (!strncmp("create", cmdBuff, 6)) {
      if (cmdBuff[8] == '\0') {
	puts("Invalid arguments to create command\n");
	exit();
      }
      while(1) {
	gets(temp);
	len = strlen(temp);
	if (temp[0] == 'e') {
	  fwrite(&cmdBuff[7], fileBuff);
	  exit();
	} else {
	  for(i = 0; i < len; i++) {
	    fileBuff[place++] = temp[i];
	  }
	}
      }
    } else {
      puts("Unknown command: ");
      puts(cmdBuff);
      puts("\n\r");
      exit();
    }
  } else {
    getDirList("/bin", pathBuff);
    for (i = 0; i < 16; i++) {
      equals = 1;
      for (j = 0; j < 6; j++) {
	if (cmdBuff[j] != pathBuff[i*6 + j]){
	  equals = 0;
	  break;
	}
      }
      if (equals) {
	char cmd[16], args[16];
	memset(cmd, 0, 16);
	    memset(args, 0, 16);
	    strcat(cmd, "/bin/");
	    memcpy(cmd+5, cmdBuff, 6);
	    memcpy(args, cmdBuff+6);
	    puts(args);
	    exec(cmd);
      }
    }
    puts("Unknown command: ");
    puts(cmdBuff);
	puts("\n\r");
	exit();
  }
}
