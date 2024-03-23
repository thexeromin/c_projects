#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <setjmp.h>
#include "jpeglib.h"

char get_character_for_gray_scale(unsigned char grayScale);
int print_ascii_art(char *filename);

struct my_error_mgr
{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr *my_error_ptr;
static char *grayRamp = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`\\'. ";

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Argument missing. Please provide a jpeg file\n");
        exit(22);
    }

    (void)print_ascii_art(argv[1]);

    return 0;
}

char get_character_for_gray_scale(unsigned char grayScale)
{
    int rampLength = strlen(grayRamp);
    return grayRamp[(int)ceil((rampLength - 1) * grayScale / 255)];
}

METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
    my_error_ptr myerr = (my_error_ptr)cinfo->err;

    (*cinfo->err->output_message)(cinfo);

    longjmp(myerr->setjmp_buffer, 1);
}

unsigned char
to_gray_scale(unsigned char r, unsigned char g, unsigned char b)
{
    return 0.21 * r + 0.72 * g + 0.07 * b;
}

int print_ascii_art(char *filename)
{
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    FILE *infile;
    JSAMPARRAY buffer;
    int row_stride;

    if ((infile = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", filename);
        return 0;
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);

    (void)jpeg_read_header(&cinfo, TRUE);
    (void)jpeg_start_decompress(&cinfo);

    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height)
    {
        (void)jpeg_read_scanlines(&cinfo, buffer, 1);
        JSAMPROW ptr = buffer[0];

        for (JDIMENSION i = 0; i < cinfo.output_width; i++)
        {
            unsigned char r, g, b;
            r = *ptr++; // Red
            g = *ptr++; // Green
            b = *ptr++; // Blue

            unsigned char val = to_gray_scale(r, g, b);
            // printf("Pixel %d, %d: grayscale: %d\n", cinfo.output_scanline, i, val);
            char ch = get_character_for_gray_scale(val);
            printf("%c", ch);
        }
        printf("\n");
    }

    (void)jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return 1;
}