/******************************************************************************
                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int uint8_t;
typedef unsigned int uint16_t;
typedef long uint32_t;
typedef unsigned long uint64_t;

uint8_t chunkSize = 1024;

struct test {
    int version;
    char name[32];
    char description[32];
    uint32_t textures;
};
struct fileData {
    int type;
    uint32_t chunks;
    char fname[32];
};
struct Chunk {
    char data[chunkSize];
} Chunk;

int main()
{
    FILE* infile;
    infile = fopen("person1.dat", "wb+");
    if (infile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    struct test write_struct = { 1, "Rohan", "test", 1 };
    // struct fileData fdat = malloc(sizeof(struct fileData) + 100 * sizeof(int));
    struct fileData fdat = {0, 1, "test.bin"}; // Type, Chunks, name
    Chunk testChunk = { "Hello world!" };
    struct test read_struct;
    struct fileData testRd;
    // writing to file
    
    // Write header
    fwrite(&write_struct, sizeof(write_struct), 1,
           infile);
    
    // Write file data header
    fwrite(&fdat, sizeof(fdat), 1,
           infile);
    
    // Write chunk data
    fwrite(&fdat, sizeof(fdat), 1,
           infile);
    
    rewind(infile);
    
    fread(&read_struct, sizeof(read_struct), 1, infile);
    
    for(int f=0; f<read_struct.textures; f++)
    {
        fread(&testRd, sizeof(testRd), 1, infile);
        for(int chunk=0; chunk<testRd.chunks; chunk++)
        {
            Chunk chnk;
            fread(&testRd, sizeof(chnk), 1, infile);
            printf("Chunk %d:%s", chunk, chnk.data);
        }
        printf("File name:%s\nData: %s\n", testRd.fname, testRd.data);
    }
    printf("Name: %s, Description: %s \nVersion: %d", read_struct.name,
           read_struct.description, read_struct.version);
  
    return 0;
}
