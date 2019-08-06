# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <conio.h>

// add a hex conversion function
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
    //first convert all to uppercase
    // printf("\nString now is %s", strupr(hexVal));
    
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 

      


        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 

        

        else if ((hexVal[i]>='A' && hexVal[i]<='F') || (hexVal[i]>='a' && hexVal[i]<='f'))
        { 
            dec_val += (toupper(hexVal[i]) - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
    // printf("\nDecimal value is %d \n", dec_val);
    return dec_val; 
} 
unsigned int stringToHex(char line[])
{
	unsigned int hex=0x0;
	int n;
	n=hexadecimalToDecimal(line);
	hex=n;
	return hex;
}

// need a decimal to hex functionality
unsigned int decimal_to_hex(int dec){
    char hexadecimal[100];
    long quotient, remainder;
    quotient = dec;
    int j = 0;
    while(quotient != 0){
        remainder = quotient % 16;
        if(remainder < 10)
            hexadecimal[j++] = 48 + remainder;
        else
        {
            hexadecimal[j++] = 55 + remainder;
        }
        quotient = quotient / 16;
        
    }
    unsigned int hex = stringToHex(hexadecimal);
    return hex;
}

void hex_pass_one(){

    char opcode[10],operand[10],label1[10],label[10],code[10][10],ch,c; char mnemonic[30][10]={"START","LDA","ADD","MUL","SUB","STA","STL", "JSUB", "COMP","JEQ", "J", "LDL", "LDX", "TD", "RD", "STCH", "TIX", "JLT", "STX", "WD","RSUB","END"};
	int locctr,start,len,i=0,j=0,address;
	// create the hex counter
	unsigned int hex_ctr, hex_len;
	char start_val[10];
	FILE *fp1,*fp2,*fp3,*fp4, *length_file;
	//clrscr();
 	fp1=fopen("full_input_program.txt","r");
 	fp2=fopen("SYMTAB.txt","w");
	fp3=fopen("full_output.txt","w");
	fp4=fopen("OPTAB.txt", "r");
	fprintf(fp3,"-\t");
 	fscanf(fp1,"%s%s%s",label,opcode,operand);
	 if(strcmp(opcode,"START")==0)
  	{
		start=atoi(operand);
		strcpy(start_val, operand);
 		locctr=start;
		hex_ctr = stringToHex(start_val);
		fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	}
	else
		{	
			locctr=0;
			hex_ctr = decimal_to_hex(locctr);
		}

	while(strcmp(opcode,"END")!=0)
	{	
		// hex_ctr = decimal_to_hex(locctr);
		fprintf(fp3,"%x", hex_ctr);
	
	/*	fp4=fopen("SYMTAB.txt","w");
		fscanf(fp4,"%d%s",address,label1);
		c=fgetc(fp4);
		while(c!=EOF)
		{	
			if(strcmp(label,label1)==0)
			{	printf("Invalid Entry");
				exit(0);
			}
			fscanf(fp4,"%s%s",label1,address);
			c=fgetc(fp4);
		}
		fclose(fp4);
	*/
		if(strcmp(label,"-")!=0){
			// hex_ctr = decimal_to_hex(locctr);
			fprintf(fp2,"%x\t%s\n", hex_ctr, label);
		}
		// fscanf(fp4, "%s\t/%s", mnemonic[i], code[i]);
		//strcpy(code[i],mnemonic[j]);
		j=0;
		while(strcmp(mnemonic[j],"END")!=0)
		{
			if(strcmp(opcode,mnemonic[j])==0)
			{
				// locctr+=3;
				// hex_ctr = decimal_to_hex(locctr);
				hex_ctr += 3;
				break;
			}
			//strcpy(code[i],mnemonic[j]);
			// fscanf(fp4, "%s\t%s", mnemonic[j], code[j]);
			j++;
		}
  		if(strcmp(opcode,"WORD")==0){
			// locctr+=3;
			// hex_ctr = decimal_to_hex(locctr);
			hex_ctr += 3;
		}
		else if(strcmp(opcode,"RESW")==0){
			// locctr+=(3*(atoi(operand)));
			// hex_ctr = decimal_to_hex(locctr);
			hex_ctr += 3;
		}
		else if(strcmp(opcode,"RESB")==0){
			// locctr+=(atoi(operand));
			// hex_ctr = decimal_to_hex(locctr);
			hex_ctr += 3;
		}
		else if(strcmp(opcode,"BYTE")==0){
			// ++locctr;
			// hex_ctr = decimal_to_hex(locctr);
			/*		len=strlen(operand);
					for(i=2;i<len;i++)
					{
						printf("%x",operand[i]);
					} */
			len = strlen(operand);
			char hex_str[5];
			if(operand[0] == 'X'){
				// for(i = 2; i < len; i++){
				// 	hex_str[i - 2] = operand[i];
				// }
				// unsigned int hex_up = stringToHex(hex_str);
				// hex_ctr += hex_up;
				hex_ctr += 1;
			}
			else if(operand[0] == 'C'){
				hex_ctr += 3;
			}
		}
		
		fprintf(fp3,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
		
	}
	// hex_ctr = decimal_to_hex(locctr);
	fprintf(fp3,"%x\t%s\t%s\t%s\n", hex_ctr,label,opcode,operand);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("\n\nThe contents of Input Table :\n\n");
	fp1=fopen("full_input_program.txt","r");
	ch=fgetc(fp1);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp1);
	}
	printf("\n\nThe contents of Output Table :\n\n");
	fp3=fopen("full_output.txt","r");
	ch=fgetc(fp3);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp3);
	}
	// len=locctr-start;
	hex_len = hex_ctr - stringToHex(start_val);
	printf("\nThe length of the program is %x.\n\n", hex_len);
	// finding the length and saving it into a file
	length_file = fopen("length.txt", "w");
	fprintf(length_file, "%x", hex_len);
	fclose(length_file);

	printf("\n\nThe contents of Symbol Table :\n\n");
	fp2=fopen("SYMTAB.txt","r");
 	ch=fgetc(fp2);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp2);
	}


	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
    printf("\n");
}
void hex_pass_two(){

    FILE *fint,*ftab,*flen,*fsym;
	int op1[10],txtlen,txtlen1,i,j=0,len;
	char add[5],symadd[5],op[5],start[10],temp[30],line[20],label[20],mne[10],operand[10],symtab[10],opmne[10];

    unsigned int hex_len;
	//clrscr();
	fint=fopen("full_output.txt","r");
	flen=fopen("length.txt","r");
	ftab=fopen("OPTAB.txt","r");
	fsym=fopen("SYMTAB.txt","r");
	fscanf(fint,"%s%s%s%s",add,label,mne,operand);
	if(strcmp(mne,"START")==0)
	{
		strcpy(start,operand);
		fscanf(flen,"%x",&hex_len);
	}
		printf("H^%s^%s^000%x\nT^00%s^",label,start,hex_len,start);
		fscanf(fint,"%s%s%s%s",add,label,mne,operand);
		while(strcmp(mne,"END")!=0)
		{
			fscanf(ftab,"%s%s",opmne,op);
			while(!feof(ftab))
			{
				if(strcmp(mne,opmne)==0)
				{
					fclose(ftab);
					fscanf(fsym,"%s%s",symadd,symtab);
					while(!feof(fsym))
					{
						if(strcmp(operand,symtab)==0)
						{
							printf("%s%s^",op,symadd);
							break;
						}
						else
							fscanf(fsym,"%s%s",symadd,symtab);
					}
					break;
				}
				else
				fscanf(ftab,"%s%s",opmne,op);
			}
			if((strcmp(mne,"BYTE")==0)||(strcmp(mne,"WORD")==0))
			{
				if(strcmp(mne,"WORD")==0)
					printf("0000%s^",operand);
				else if(strcmp(mne, "BYTE") == 0)
				{
					len=strlen(operand);
					for(i=2;i<len;i++)
					{
						printf("%x",operand[i]);
					}
					printf("^");
				}
			}
			fscanf(fint,"%s%s%s%s",add,label,mne,operand);
			ftab=fopen("optab.txt","r");
			fseek(ftab,SEEK_SET,0);
		}
		printf("\nE^00%s",start);
		fclose(fint);
		fclose(ftab);
		fclose(fsym);
		fclose(flen);
		//fclose(fout);
		getch();
}
int main(){
    hex_pass_one();
    hex_pass_two();
    return 0;
}