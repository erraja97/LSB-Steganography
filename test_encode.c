#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "string.h"
#include "decode.h"

int main(int argc, char **argv)
{
    // check operations
    if (check_operation_type(argv) == e_encode)
    {
        EncodeInfo encInfo;
        printf("Selected Encoding\n");
        if (read_and_validate_encode_args(argv, &encInfo) == e_success)
        {
            printf("Encoding | Read and Validate argument is successful\n");

            if (do_encoding(&encInfo) == e_success)
            {

                printf("Completed Encoding\n");
            }
            else
            {
                printf("Failure: Encoding not done\n");
            }
        }
        else
        {
            printf("Failure: Encoding | Read and Valid arguments\n");
        }
    }
    else if (check_operation_type(argv) == e_decode)
    {
        DecodeInfo decInfo;
        printf("Selected Decoding\n");
        if (read_and_validate_decode_args(argv, &decInfo) == e_success)
        {
            printf("Decoding | Read and Validate argument is successful\n");
            if (do_decoding(&decInfo) == e_success)
            {

                printf("Completed Decoding\n");
            }
            else
            {
                printf("Failure: Decoding not done\n");
            }
        }
        else
        {
            printf("Failure: Decoding | Read and Valid arguments\n");
        }
    }
    else
    {
        printf("Invalid Option\n");
        printf("Usage:\nEncoding: ./a.out -e beautiful.bmp secret.txt\n");
        printf("Decoding: ./aout -d stego.bmp");
    }

    return 0;
}

// function definitions
OperationType check_operation_type(char *argv[])
{
    if (strcmp(argv[1], "-e") == 0)
    {
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}
