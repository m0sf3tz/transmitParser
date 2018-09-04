#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"

FILE *ptr_myfile;
FILE *ptr_myfile2;


char temp[TRASMIT_BLOCK_SIZE*SECTORS_PER_SAMPLE];

typedef enum {START_SECTOR, START_BLOCK, END_BLOCK, END_SECTOR, NO_MAGIC_KEY} magicKey_t;
typedef enum {PROCESSING_START_BLOCK, PROCESSING_MIDDLE_BLOCK, PROCESSING_FINAL_BLOCK} currentBlock_t;

typedef struct 
{
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
}state_t;


typedef struct 
{
    currentBlock_t   currentBlockState; //which block of our statemachine are we currently at (start, middle, end?)
    uint32_t         uniqueId;      //the unique ID of a sector (will come in first block)
    int              blockIndex;  //used to keep track of which byte of a single block we are curently parsing
    state_t          shiftRegister; //will keep track of last 4 bytes which are shifted in
    bool             processingSector; //will be true once we start processing a secotr, will be set to false when we are done or we hit an error condition
    
    bool             validBlock0;
    bool             validBlock1;
    bool             validBlock2;
}validator_t;

validator_t validator;



   //uint64_t magicByte64  =  (uint64_t)0x10 << 32ull;
   
magicKey_t searchForMagicBytes()
{
    uint32_t magicByte32 =   validator.shiftRegister.b0 << 0u  |
                             validator.shiftRegister.b1 << 8u  |
                             validator.shiftRegister.b2 << 16u |
                             validator.shiftRegister.b3 << 24u;

    
 
    uint64_t magicByte64  =  magicByte32 | (uint64_t)validator.shiftRegister.b4<< 32ull;
    #if 0
    printf("first byte is : %x ! \n", validator.shiftRegister.b0);
    printf("second byte is: %x ! \n", validator.shiftRegister.b1);
    printf("third byte is : %x ! \n", validator.shiftRegister.b2);
    printf("fourth byte is: %x ! \n", validator.shiftRegister.b3);
    printf("fifth byte is : %x ! \n", validator.shiftRegister.b4);

    printf("\n");
    printf("\n");
    #endif 
        
   
        
    if(magicByte32 == 0xA00BC00D)
    {
        printf("Got a start sector magic number! \n");
        return START_SECTOR;
    }
    else if(magicByte32 == 0x1BB11BB1)
    {
        printf("Got a start block magic number! \n");
        return START_BLOCK;
    }
    
    //end magic numbers are 5bytes (why?)
    if(magicByte64 == 0xC22CC02CC2ull)
    {
        printf("Got an end block magic number! \n");
        return END_BLOCK;
    }
    else if(magicByte64 == 0xD33DD33DD3ull)
    {
        printf("Got a end sector magic number! \n");
        return END_SECTOR;
    }

    return NO_MAGIC_KEY;
    
}



//used to keep track of the last 5 byes we got
static void shiftIn(char in)
{
   validator.shiftRegister.b4 = validator.shiftRegister.b3;
   validator.shiftRegister.b3 = validator.shiftRegister.b2;
   validator.shiftRegister.b2 = validator.shiftRegister.b1;
   validator.shiftRegister.b1 = validator.shiftRegister.b0;
   validator.shiftRegister.b0 = in;
}

static void processIncomingData(char in)
{
    shiftIn(in);
    magicKey_t key = searchForMagicBytes();
 
    
    switch(validator.currentBlockState){
    
    case PROCESSING_START_BLOCK:
        //if we get the magic number saying we will be transmitting a new sector, reset our states
        if(START_SECTOR  == key)
        {
            validator.processingSector = true;
            validator.blockIndex = 0;
            break;
        }
        else if(END_BLOCK  == key)  
        {
            //got the first sector, go to next state 
            //printf("Processed the first block of a sector \n");
            validator.currentBlockState = PROCESSING_MIDDLE_BLOCK;
            validator.blockIndex = 0;
            break;
        }
        else if(START_BLOCK  == key)  
        {
            //error, we should not be getting here - expect only END_BLOCK
            validator.processingSector = false;
            validator.blockIndex = 0;
            break;
        }
        else if(END_SECTOR  == key)  
        {
            //error, we should not be getting here - expect only END_BLOCK
            validator.processingSector = false;
            validator.blockIndex = 0;
            break;
        }
        else
        {
            //we did not hit a magic key
            validator.blockIndex++;
        }
        if(validator.blockIndex > TRASMIT_BLOCK_SIZE)
        {
            //error, we should not be getting here - expect only END_BLOCK
            validator.processingSector = false;
            validator.blockIndex = 0;
            break;
        }
   }
}


int main()
{
    ptr_myfile=fopen("user.c","rb");
    fseek(ptr_myfile, 0, SEEK_END);
    long fsize = ftell(ptr_myfile);
    fseek(ptr_myfile, 0, SEEK_SET);  //same as rewind(f);
    
    
    printf("size is %d \n", fsize);
    
    char *string = malloc(fsize + 1);
    if(string == NULL)
    {
        printf("Failed to get buffer");
    }
    fread(string, fsize, 1, ptr_myfile);
    fclose(ptr_myfile);
    string[fsize] = 0;
        printf("size is %d \n", fsize);
    
    int counter = 0;

	ptr_myfile2=fopen("log.bin","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
    

#if 0    
    char fake [] = {0xDE , 0xAD, 0xDE, 0xAD, 0xDE};
    
    processIncomingData(fake[0]);



    processIncomingData(fake[1]);

    
    
    processIncomingData(fake[2]);

    
    
    processIncomingData(fake[3]);

    processIncomingData(fake[4]);

    
    return;
 #endif
 
    while(counter!=fsize)
    {
        
        char tmp = (unsigned char)string[counter++];
        processIncomingData(tmp);
        //printf("%d :  %1x \n",counter,(unsigned char)tmp);
        fwrite (&tmp , sizeof(char), 1, ptr_myfile2);
    }

}
