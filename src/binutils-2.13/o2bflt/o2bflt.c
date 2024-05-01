//amihart's simple ELF (.o) to bFLT gotpic v4 converter
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "elf32.c"

typedef struct
{
    uint8_t magic[4];
    uint32_t version;
    uint32_t entry;
    uint32_t data_start;
    uint32_t data_end;
    uint32_t bss_end;
    uint32_t stack_size;
    uint32_t reloc_start;
    uint32_t reloc_count;
    uint32_t flags;
    uint32_t build_date;
    uint32_t filler[5];
} bflt_header_t;

uint32_t reverse(uint32_t i)
{
    uint32_t r = (i & 0xFF) << 24;
    r |= ((i >> 8) & 0xFF) << 16;
    r |= ((i >> 16) & 0xFF) << 8;
    r |= (i >> 24) & 0xFF;
    return r;
}

void usage()
{
    printf("usage: o2bflt [filename.o]\n");

}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage();
        return 1;
    }
    const char msg[] = "o2bflt: Expected `.o` file extension.\n";
    size_t fname_len = 0;
    for (size_t i = 0; argv[1][i] != 0; i++)
    {
        fname_len++;
    }
    if (fname_len <= 2)
    {
        fprintf(stderr, msg);
        return 1;
    }
    if (argv[1][fname_len - 2] != '.' || argv[1][fname_len - 1] != 'o')
    {
        fprintf(stderr, msg);
        return 1;
    }

    elf32_info_t* e_info = elf32_read(argv[1]);
    if (e_info == NULL) exit(1);

    argv[1][fname_len - 2] = 0;
    FILE* f = fopen(argv[1], "w");
    if (!f)
    {
        fprintf(stderr, "o2flt: Failed to open output file for writing.\n");
        elf32_free(e_info);
        exit(1);
    }
    size_t size_got = sizeof(uint32_t) * ((e_info->symbols_count) + 1);
    uint32_t data_end =
        sizeof(bflt_header_t)
        + size_got
        + e_info->sections[ELF32_SECTION_TEXT].size
        + e_info->sections[ELF32_SECTION_DATA].size
        + e_info->sections[ELF32_SECTION_RODATA].size
        + e_info->sections[ELF32_SECTION_BSS].size
    ;
    while (data_end % 16 != 0)
    {
        data_end += 1;
    }

    /* <HEADER> */
    bflt_header_t* hdr = malloc(sizeof(bflt_header_t));
    for (size_t i = 0; i < sizeof(bflt_header_t); i++) ((uint8_t*)hdr)[i] = 0;
    hdr->magic[0] = 'b';
    hdr->magic[1] = 'F';
    hdr->magic[2] = 'L';
    hdr->magic[3] = 'T';
    hdr->version = reverse(4);
    hdr->entry = reverse(sizeof(bflt_header_t));
    hdr->data_start = reverse(sizeof(bflt_header_t) + e_info->sections[ELF32_SECTION_TEXT].size);
    hdr->data_end = reverse(data_end);
    hdr->bss_end = hdr->data_end;
    hdr->stack_size = reverse(4096);
    hdr->reloc_start = hdr->data_end;
    hdr->reloc_count = 0;
    hdr->flags = reverse(2); //gotpic
    hdr->build_date = reverse((uint32_t)(time(NULL)));
    hdr->filler[0] = 0;
    hdr->filler[1] = 0;
    hdr->filler[2] = 0;
    hdr->filler[3] = 0;
    hdr->filler[4] = 0;
    fwrite(hdr, 1, sizeof(bflt_header_t), f);
    free(hdr);
    /* </HEADER> */

    /* <TEXT> */
    fseek(e_info->file, e_info->sections[ELF32_SECTION_TEXT].addr, SEEK_SET);
    for (size_t i = 0; i < e_info->sections[ELF32_SECTION_TEXT].size; i++)
    {
        fputc(fgetc(e_info->file), f);
    }
    /* </TEXT> */

    /* <GOT> */
    uint32_t wordout = 0;
    for (size_t i = 0; i < e_info->symbols_count; i++)
    {
        wordout = e_info->symbols[i].addr;
        fwrite(&wordout, sizeof(uint32_t), 1, f);
    }
    wordout = -1;
    fwrite(&wordout, sizeof(uint32_t), 1, f);
    /* </GOT> */

    /* <DATA> */
    uint8_t section_order[] = { ELF32_SECTION_DATA, ELF32_SECTION_RODATA, ELF32_SECTION_BSS };
    for (uint8_t s = 0; s < sizeof(section_order); s++)
    {
        if (e_info->sections[section_order[s]].found)
        {
            fseek(e_info->file, e_info->sections[section_order[s]].addr, SEEK_SET);
            for (size_t i = 0; i < e_info->sections[section_order[s]].size; i++)
            {
                fputc(fgetc(e_info->file), f);
            }
        }
    }
    /* </DATA> */

    while ((ftell(f) % 16) != 0)
    {
        fputc(0, f);
    }

    elf32_free(e_info);
    fclose(f);
    return 0;
}
