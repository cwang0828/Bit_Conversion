# include <stdio.h>
# include <string.h>
# include <math.h>
# define SIZE  8

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #1
    NetID: 1260340
*/

/** These are the methods/ functions that 
are implements below */
void enterCharacterParity();
void enterCheckSum();
void RecBinary(unsigned int, int);
void AddBinary(unsigned int);  
int binary2Decimal();

/** This is the sum of the 8 bits binary */
int binarySum = 0; 

/** This is the sum of the four
8 bits binary */
int totalSum = 0; 


/** This is the main method that
asked whether the user would like to choose
1 (character parity) or 2 (integer checksum). 
Also, the process would keep going until the 
user press 'q' */
int main(void) {
    int integer1; 
    char option;
    option = 'r';
    while (option != 'q') {
    	printf("What type of display do you want?\n"); 
    	printf("Enter 1 for character parity, 2 for integer checksum: ");
    	scanf(" %d", &integer1); 
        
    	if(integer1 == 1) {
    	    // character parity 
    	    enterCharacterParity(); 
    	} else if (integer1 == 2) {
    	    // integer checksum
    	    enterCheckSum();
    	}
        
        printf("\nEnter r to repeat, q to quit: ");
        scanf(" %s", &option);
    }
    return 0;
}

/** This method processes 8 bits each time 
and sum up the four 8 bit values. */
void AddBinary(unsigned int input) {
    // Isolate 8 bits by '&'ing 
    // the input integer value with eight 1s. 
    int num1 = 0;
    num1 = (input & 255); 
    int num2 = 0;
    num2 = (input>>8 & 255); 
    int num3 = 0;
    num3 = (input>>16 & 255); 
    int num4 = 0;
    num4 = (input>>24 & 255);
    
    totalSum =0;
    
    // Since there are 32 bits, 
    // the 8 bits values are handled four times. 
    binarySum = 0;
    RecBinary(num4, SIZE); 
    printf("%c", ' ');
    totalSum = binary2Decimal(); 
    
    binarySum = 0;
    RecBinary(num3, SIZE); 
    printf("%c", ' ');
    totalSum += binary2Decimal();
    
    binarySum = 0;
    RecBinary(num2, SIZE); 
    printf("%c", ' ');
    totalSum += binary2Decimal(); 
    
    binarySum = 0;
    RecBinary(num1, SIZE); 
    totalSum += binary2Decimal(); 
}

/** This method turns an 8 bits value
to a decimal value. */
int binary2Decimal() {
    int sum = 0; 
    int digit = 0;
    int count = 0; 

    while(count < 8) {
         digit = binarySum % 10;
         binarySum /= 10; 
         sum += digit * pow(2, count); 
         count++;
    }
    return sum; 
}

/** This method does a recusive call to print 
out all the 1s and 0s in a proper order. Then, it 
fills the rest of the 8 bits with 0s.*/
void RecBinary(unsigned int input, int sizeCount) {
        unsigned int toPrint = 0; 
        if (sizeCount != 0) {
            if (input != 0) {
                toPrint = input % 2; 
                input /= 2; 
                sizeCount--; 
                RecBinary(input, sizeCount); 
                
                printf("%d", toPrint); 
                binarySum = binarySum * 10 + toPrint; 
            } else {
                int zero = 0;
                printf("%d", zero); 
                sizeCount--; 
                RecBinary(input, sizeCount); 
            }
        }
}

/** This is the checkSum method*/
void enterCheckSum() {
    int bitRep; 
    int inputChar = 0; 
    unsigned int ascii = 0; 
    int sumVal = 0;
    printf("Enter an integer for checksum calculation: ");
    scanf(" %d", &inputChar);
    ascii = inputChar; 

    printf("Integer: %d, Bit representation: ", inputChar);
    AddBinary(ascii);
    printf("\nSum of the number is: %d\n", totalSum);
     
    int Checksum = totalSum;
    int remainder = 0; 
    remainder = Checksum % 255;
    printf("Checksum of the number is: %d, Bit representation: ", remainder);
    RecBinary(remainder, SIZE); 
    printf("%c", '\n');
}

/** This is the character parity method */
void enterCharacterParity() {
    char inputChar; 
    int ascii = 0; 
    printf("Enter a character for parity calculation: ");
    scanf(" %c", &inputChar);
    ascii = inputChar; 

    printf("Character: %c, Bit representation: ", inputChar); 
    binarySum = 0;
    RecBinary(ascii, SIZE); 
    printf("%c\n", ' ');

    // Count number of ones from the bit representation
    int tempBinarySum = 0, count = 0, sign = 0, digit = 0; 
    tempBinarySum = binarySum;
    while(tempBinarySum > 0) {
        digit = tempBinarySum %10;
        tempBinarySum /= 10;
        if(digit == 1) {
            count++; 
        } 
    }
    // If the number of ones is odd, 
    // change the front most digit to 1s. 
    if(count % 2 == 1) {
        sign = 1; 
    }
    printf("Number of ones: %d\n", count);
    printf("Even 1 parity for the character is: %d%d\n",sign,binarySum);
}
