#include <stdio.h>
#include "decode.h"
#include "common.h"
#include "types.h"
#include "string.h"

/* Function definitions */

/* Read and validate decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (argv[2] != NULL && strcmp(strstr(argv[2], "."), ".bmp") == 0)
    {
        decInfo->src_image_fname = argv[2];
    }
    else
    {
        return e_failure;
    }

    if (argv[3] != NULL)
    {
        decInfo->output_file_fname = argv[3];
    }
    else
    {
        decInfo->output_file_fname = "ouput.txt";
    }

    return e_success;
}

/* Get File pointers for i/p and o/p files */
Status open_files_for_decode(DecodeInfo *decInfo)
{
    // src image file
    decInfo->fptr_src_image = fopen(decInfo->src_image_fname, "r");

    // Do Error handling
    if (decInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->src_image_fname);

        return e_failure;
    }


    // output file
    decInfo->fptr_output_file = fopen(decInfo->output_file_fname, "w");

    // Do Error handling
    if (decInfo->fptr_output_file == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->output_file_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}

/* Decode a byte from LSB of image data array */
char decode_byte_from_lsb(char *image_buffer)
{

    char data = 0;

    for (int i = 0; i < 8; i++)
    {
        data |= (image_buffer[i] & 1) << 7 - i;
    }

    return data;
}

/* Decode size from LSB of image data array */
int decode_size_from_lsb(char *image_buffer)
{

    int data = 0;

    for (int i = 0; i < 32; i++)
    {
        data |= (image_buffer[i] & 1) << 31 - i;
    }

    return data;
}

/* Fetch and validate Magic String */
Status decode_magic_string(char *magic_string, DecodeInfo *decInfo)
{
    char magicbuff[50];
    int i = 0;

    fseek(decInfo->fptr_src_image, 54, SEEK_SET);

    while (i < strlen(MAGIC_STRING))
    {
        fread(decInfo->image_buffer, 8, 1, decInfo->fptr_src_image);
        magicbuff[i] = decode_byte_from_lsb(decInfo->image_buffer);
        i++;
    }
    magicbuff[i] = '\0';

    printf("Magic String decoded Sucessfully\n");

    if (strcmp(magicbuff, magic_string) == 0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

/*Decode Secret file extension size */
Status decode_size(int size, DecodeInfo *decInfo)
{

    char ext_size_buff[32];

    fread(ext_size_buff, 32, 1, decInfo->fptr_src_image);
    decInfo->extn_size = decode_size_from_lsb(ext_size_buff);
    if (decInfo->extn_size == size)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

/* decode and validate secret file extn name */
Status decode_secret_file_extn(const char *file_extn, DecodeInfo *decInfo)
{
    file_extn = ".txt";//considering extension same as output file, currently it's hardcodeds
    char extn_buff[50];
    int i = 0;

    while (i < strlen(file_extn))
    {
        fread(decInfo->image_buffer, 8, 1, decInfo->fptr_src_image);
        extn_buff[i] = decode_byte_from_lsb(decInfo->image_buffer);
        i++;
    }
    extn_buff[i] = '\0';

    if (strcmp(extn_buff, file_extn) == 0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

/* decode secret file size to print store data to output.txt */
Status decode_secret_file_size(DecodeInfo *decInfo)
{

    char ext_size_buff[32];

    fread(ext_size_buff, 32, 1, decInfo->fptr_src_image);
    decInfo->file_size = decode_size_from_lsb(ext_size_buff);

    if (decInfo->file_size > 0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

/* write output to file */
Status decode_data_to_file(DecodeInfo *decInfo)
{

    char ch;

    for (int i = 0; i < decInfo->file_size; i++)
    {
        fread(decInfo->image_buffer, 8, 1, decInfo->fptr_src_image);
        ch = decode_byte_from_lsb(decInfo->image_buffer);
        fwrite(&ch, 1, 1, decInfo->fptr_output_file);
    }

    printf("INFO : Decoding file data done.\n");

    return e_success;
}

/* perform the decoding */
Status do_decoding(DecodeInfo *decInfo)
{

    if (open_files_for_decode(decInfo) == e_success)
    {
        printf("All files opened successfully\n");
        printf("Started Decoding.........\n");
        if (decode_magic_string(MAGIC_STRING, decInfo) == e_success)
        {
            printf("Source file is an encoded file\n");
            if (decode_size(strlen(".txt"), decInfo) == e_success)
            {
                printf("Decoded File extension size and validated successfully\n");
                if (decode_secret_file_extn(decInfo->extn_name, decInfo) == e_success)
                {
                    printf("Decoded File extension and validated successfully\n");
                    if (decode_secret_file_size(decInfo) == e_success)
                    {
                        printf("File size decoded successfully\n");
                        if (decode_data_to_file(decInfo) == e_success)
                        {
                            printf("Data decoded and stored successfully in output file\n");
                        }
                        else
                        {
                            printf("Failed to decode data and write output file\n");
                        }
                    }
                    else
                    {
                        printf("File size not decoded\n");
                    }
                }
                else
                {
                    printf("File extension is not valid\n");
                }
            }
            else
            {
                printf("File extension size is not valid\n");
                return e_failure;
            }
        }
        else
        {
            printf("Source file is not an encoded file\n");
            return e_failure;
        }
    }
    else
    {
        printf("Failed to open the required files\n");
        return e_failure;
    }
    // No failure return e_success
    return e_success;
}
