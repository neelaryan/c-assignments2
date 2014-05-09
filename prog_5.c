#include <stdio.h>
#include <string.h>
#include <math.h>

/* If we are compiling on Windows compile these functions and/or add these headers */
#ifdef _WIN32

#include <conio.h>

#else

#include <termios.h>
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) {
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) {
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void) {
    return getch_(1);
}

#endif

/**
 *	Takes a decimal number and converts it to a binary string
 */
char* toBinary(int decimal) {

	static char binary[1000];
	int k = 0, n = 0;
	int negative = 0;
	int remain;
	char temp[strlen(binary)];

	// take care of negative input
	if (decimal < 0) {
		decimal = -decimal;
		negative = 1;
	}

	while (decimal > 0) {
		remain = decimal % 2;
		decimal = decimal / 2;
		temp[k++] = remain + '0';
	}

	//using sign and magnitude
	if (negative)
		temp[k++] = '1';
	else
		temp[k++] = '0';

	// reverse the spelling
	while (k >= 0)
		binary[n++] = temp[--k];

	binary[n - 1] = 0;
	return binary;
}

/**
 *	Takes a binary string and converts it to a decimal number
 */
int toDecimal(char* s)
{
    int result = 0,i,n;
    int p;

    for (i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '1')
        {
            p = (n - (i+1));
            result += pow(2, p);
        }
    }

    return result;
}

/**
 * Check if the value is a valid binary string
 */
int validBinaryString(char* s)
{
    int r = 1,i,n;

    // Make sure all chars are either 0 or 1
    for (i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] != '0' && s[i] != '1')
        {
            r = 0;
        }
    }

    // Check first char is a 1
    if (s[0] != '1')
    {
        r = 0;
    }

    return r;
}

/**
 * Reverse string
 */
void strrev(char str[]){
    int i,j;
    char temp[100];
    for(i=strlen(str)-1,j=0; i+1!=0; --i,++j)
    {
        temp[j]=str[i];
    }
    temp[j]='\0';
    strcpy(str,temp);
}

/**
 * Converts Decimal to Hexadecimal.
 */
char* decimal_hex(int n, char hex[])
{
    int i=0,rem;
    while (n!=0)
    {
        rem=n%16;
        switch(rem)
        {
            case 10:
              hex[i]='A';
              break;
            case 11:
              hex[i]='B';
              break;
            case 12:
              hex[i]='C';
              break;
            case 13:
              hex[i]='D';
              break;
            case 14:
              hex[i]='E';
              break;
            case 15:
              hex[i]='F';
              break;
            default:
              hex[i]=rem+'0';
              break;
        }
        ++i;
        n/=16;
    }
    hex[i]='\0';
    strrev(hex);
    return hex;
}

/**
 * Convert Hexadecimal to Decimal.
 */
int hex_decimal(char hex[])
{
    int i, length, sum=0;
    for(length=0; hex[length]!='\0'; ++length);
    for(i=0; hex[i]!='\0'; ++i, --length)
    {
        if(hex[i]>='0' && hex[i]<='9')
            sum+=(hex[i]-'0')*pow(16,length-1);
        if(hex[i]>='A' && hex[i]<='F')
            sum+=(hex[i]-55)*pow(16,length-1);
        if(hex[i]>='a' && hex[i]<='f')
            sum+=(hex[i]-87)*pow(16,length-1);
    }
    return sum;
}

/**
 * Function to convert decimal to octal
 */
int decimal_octal(int n)
{
    int rem, i=1, octal=0;
    while (n!=0)
    {
        rem=n%8;
        n/=8;
        octal+=rem*i;
        i*=10;
    }
    return octal;
}

/**
 * Function to convert octal to decimal
 */
int octal_decimal(int n)
{
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(8,i);
        ++i;
    }
    return decimal;
}

int main() {
	int decimal,oct;
	unsigned int choice;
	char bin[100],hex[20],ch;
	do {
        printf(" Input Type ? \n1. Decimal\n2. Binary\n3. Octal\n4. Hexadecimal\n Choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1: printf("Decimal\t\t= ");
                    scanf("%d", &decimal);
                    printf("Binary\t\t= %s", toBinary(decimal));
                    printf("\nOctal\t\t= %d",decimal_octal(decimal));
                    printf("\nHexadecimal\t= %s", decimal_hex(decimal,hex));
                    break;
            case 2: printf("Binary\t\t= ");
                    scanf("%s",bin);
                    if (!validBinaryString(bin)) {
                        printf("Invalid binary string\n");
                    }
                    printf("Decimal\t\t= %d", toDecimal(bin));
                    printf("\nOctal\t\t= %o", toDecimal(bin));
                    printf("\nHexadecimal\t= %s", decimal_hex(toDecimal(bin),hex));
                    break;
            case 3: printf("Octal\t\t= ");
                    scanf("%o", &oct);
                    printf("Binary\t\t= %s",toBinary(oct));
                    printf("\nDecimal\t\t= %d", oct);
                    printf("\nHexadecimal\t= %x",oct);
                    break;
            case 4: printf("Hexadecimal\t= ");
                    scanf("%s", hex);
                    printf("Binary\t\t= %s", toBinary(hex_decimal(hex)));
                    printf("\nDecimal\t\t= %d", hex_decimal(hex));
                    printf("\nOctal\t\t= %o", hex_decimal(hex));
                    break;
            default:printf("Wrong Input !");
                    ch='y';
                    continue;
        }
        printf("\nConvert Again ? (y/n)");
        ch=getche();
        //scanf("%c", &ch);
    }while((ch=='y') || (ch=='Y'));
	return 0;
}
