#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{

    /* source image info */
    char *src_image_fname;
    FILE *fptr_src_image;
    char image_buffer[MAX_IMAGE_BUF_SIZE];

    /* output file info */
    char *output_file_fname;
    FILE *fptr_output_file;

    /* Secret file info */
    int extn_size;
    char extn_name[MAX_FILE_SUFFIX];
    long file_size;


} DecodeInfo;

/* Decoding function prototypes */

/* Read and validate decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_files_for_decode(DecodeInfo *decInfo);

/* Encode function, which does the real encoding */
// Status decode_data_to_file(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo *encInfo);a

/* Fetch and validate Magic String */
Status decode_magic_string(char *magic_string, DecodeInfo *decInfo);

/*Decode Secret file extension size */
Status decode_size(int size, DecodeInfo *decInfo);

/* Decode a byte from LSB of image data array */
char decode_byte_from_lsb(char *image_buffer);

/* Decode secret file extension size */
int decode_size_from_lsb(char *image_buffer);

/* Decode secret file extenstion */
Status decode_secret_file_extn(const char *file_extn, DecodeInfo *encInfo);

/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Decode function to write in output file, which does the real encoding */
Status decode_data_to_file(DecodeInfo *decInfo);

#endif