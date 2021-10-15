#include "strto.h"

int strtoi(char *str, char **endstr, int base){
	int output = 0;

	int temp = 0;
	char *p = str;

	if(base > 32)
		goto here;

	while(*p){//kong ge
		if(*p >='0' && *p <='9' && *p < '0'+base)
			temp = *p - '0';	
		else if(*p >='a' && *p < 'a'+base-10)
			temp = *p -'a' + 10;
		else if(*p >='A' && *p < 'A'+base-10)
			temp = *p - 'A' + 10;
		else
			break;
		output *=base;
		output +=temp;
		p++;	
	}
here:
	if(endstr)
		*endstr = p;
	return output;
}
