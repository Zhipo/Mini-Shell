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

char* getinput(char* s){
	char* file= malloc(1*sizeof(char));
	char c=' ';
	int cont=10;
	int pos;
	int sizefile=0;
	for(int i=0;i<strlen(s);i++){
    	if(s[i]=='I' && s[i+1]=='N'){
    		c=s[i+cont];
    		sizefile=0;
    		pos=i;
    		while(c!=' ' && c!='\0'){
    			sizefile++;
    			file=realloc(file, sizefile*sizeof(char));
    			file[sizefile-1]=c;
    			cont++;
    			i++;
    			c=s[pos+cont];
    		}
    		return file;
    	}
    }
    return NULL;	
}

char* getoutput(char* s){
	char* file= malloc(1*sizeof(char));
	char c=' ';
	int cont=11;
	int pos;
	int sizefile=0;
	for(int i=0;i<strlen(s);i++){
    	if(s[i]=='O' && s[i+1]=='U'){
    		c=s[i+cont];
    		sizefile=0;
    		pos=i;
    		while(c!=' ' && c!='\0'){
    			sizefile++;
    			file=realloc(file, sizefile*sizeof(char));
    			file[sizefile-1]=c;
    			cont++;
    			i++;
    			c=s[pos+cont];
    		}
    		return file;
    	}
    }
    return NULL;	
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