#include <stdio.h>
#include <string.h>
#include <math.h>

char* toBinary(long decimal) {
	// variables
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
int binary(char* s)
{
    int result = 0,i,n;
    int p;

    // loop all chars and calculate decimal
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

int main() {
	long decimal;
	int choice;
	char *bin;
	printf("Input Type ? \n1. Decimal\n2. Binary\n3. Octal\n4. Hexadecimal");
	scanf("%d",&choice);
	switch (choice)
	{
        case 1: printf("Decimal = ");
                scanf("%ld", &decimal);
                bin = toBinary(decimal);
                printf("\nBinary = %s", bin);
                break;
        case 2: printf("Binary = ");
                scanf("%s",bin);
                if (!validBinaryString(bin)) {
                    printf("Invalid binary string\n");
                }
                printf("\nDecimal = %d", binary(bin));
                break;
        case 3:
        case 4:
        default:printf("Wrong Input !");
                main();
	}
	return 0;
}
