//0 Ninguno, 1 &&, 2 ||, 3 &.
int whatsfirst(char* s)
{
    for(int i=0;i<strlen(s);i++){
    	if(s[i]=='&' && s[i+1]=='&'){
    		return 1;
    	}
    	if(s[i]=='|' && s[i+1]=='|'){
    		return 2;
    	}
    	if(s[i]=='&' && s[i+1]!='&'){
    		return 3;
    	}	
    }
    return 0;
}

int whatsfirsttwo(char* s)
{
    for(int i=0;i<strlen(s);i++){
    	if(s[i]=='I' && s[i+1]=='N'){
    		return 1;
    	}
    	if(s[i]=='O' && s[i+1]=='U'){
    		return 2;
    	}
    }
    return 0;
}


char* trimfile(char* s){
	char* file= malloc(1*sizeof(char));
	for(int i=0;i<strlen(s);i++){
    	if(s[i]=='I' && s[i+1]=='N'){
    		int size=(strlen(s)-(i+9));
    		file=malloc((size)*(sizeof(char)));
    		for(int j=0;j< size ;j++){
    			file[j]=s[i+j+10];
    		}
    		return file;
    	}
    	if(s[i]=='O' && s[i+1]=='U'){
    		int size=(strlen(s)-(i+10));
    		file=malloc((size)*(sizeof(char)));
    		for(int j=0;j< size ;j++){
    			file[j]=s[i+j+11];
    		}
    		return file;
    	}
    }
    return file;
}