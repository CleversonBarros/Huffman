#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./util/compress.h"


int main()
{
	FILE *file;
	file = fopen("teste.txt","rb");
	compress(file);
	fclose(file);	
}
