#include <stdlib.h>
#include <string.h>
#include "Type.h"

Type Int(int n){
	int * new=(int *)malloc(sizeof(int));
	*new=n;
	return (Type)new;
}

Type Float(float f){
	float * new=(float *)malloc(sizeof(float));
	*new=f;
	return (Type)new;
}

Type Char(char c){
	char * new=(char *)malloc(sizeof(char));
	*new=c;
	return (Type)new;
}

Type String(const char *s){
	char * new=strdup(s);
	return (Type)new;
}
