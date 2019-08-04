#include<stdio.h>
#include<string.h>
#include<ctype.h>
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
    //first convert all to uppercase
    printf("\nString now is %s", strupr(hexVal));
    
      
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
    printf("\nDecimal value is %d \n", dec_val);
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



int main()
{
	char line[]="207a";
    int dec_val = 1000;
	unsigned int hex, dec_hex;
    dec_hex = decimal_to_hex(dec_val);
	hex=stringToHex(line);
	printf("%x\n",hex );
    printf("\nAnd the hex value of input %d is %x", dec_val, dec_hex);
}