#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int arg, char **argv){
float tar = atof(argv[1]);

int fl = *(int *)&tar;
int i = 0;
char binary[33], binary_rev[33], sign[2], exp_part[9], frac_part[24];
int n = sizeof(binary);

binary[32] = '\0';
binary_rev[32] = '\0';
sign[1] = '\0';
exp_part[8] = '\0';
frac_part[23] = '\0';

for(i = 0; i < 32; ++i){
  if((fl >> i & 1) == 0){
  	binary[i] = '0';
  }
  else{
  	binary[i] = '1';
  }
};

for(i = 0; i < n; ++i){
	binary_rev[n-2-i] = binary[i];	
}

for(i =0; i < n; ++i){
	if(i == 0){
		sign[0] = binary_rev[0];
	}
	else if(i > 0 & i <= 8){
		exp_part[i - 1] = binary_rev[i];
	}
	else{
		frac_part[i - 9] = binary_rev[i];
	}
}


printf("%s %s %s\n", sign, exp_part, frac_part);

}
