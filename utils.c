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