#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int arg, char **argv){
int tar, by1, by2, by3, by4;

tar = atoi(argv[1]);

by1 = (tar << 24) & 0xff000000;
by2 = (tar << 8) & 0xff0000;
by3 = (tar >> 8) & 0xff00;
by4 = (tar >> 24) & 0xff;

printf("%i\n", by1|by2|by3|by4);

return 0;
}
