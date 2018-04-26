#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	FILE *file;
	file = fopen("teste.txt","rb");
	compress(file);
	fclose(file);	
}