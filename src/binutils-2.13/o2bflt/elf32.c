#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ELF32_SECTION_TEXT 0
#define ELF32_SECTION_DATA 1
#define ELF32_SECTION_RODATA 2
#define ELF32_SECTION_BSS 3
#define ELF32_SECTION_SYMTAB 4
#define ELF32_SECTION_STRTAB 5

typedef struct
{
    uint8_t ei_mag[4];
    uint8_t ei_class;
    uint8_t ei_data;
    uint8_t ei_version;
    uint8_t ei_osabi;
    uint8_t ei_abiversion;
    uint8_t ei_pad[7];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} elf32_t;

typedef struct
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint32_t sh_flags;
    uint32_t sh_addr;
    uint32_t sh_offset;
    uint32_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint32_t sh_addralign;
    uint32_t sh_entsize;
} elf32_section_t;

typedef struct
{
    uint32_t st_name;
    uint32_t st_addr;
    uint32_t st_size;
    uint8_t st_info;
    uint8_t st_other;
    uint16_t st_shndx;
} elf32_symbol_t;

typedef struct
{
    uint32_t addr;
    uint8_t section;
} elf32_quicksymbol_t;

typedef struct
{
    uint8_t index;
    size_t addr;
    size_t size;
    uint8_t found;
} elf32_quicksection_t;

typedef struct
{
    FILE* file;
    elf32_quicksection_t* sections;
    elf32_quicksymbol_t* symbols;
    size_t symbols_count;
} elf32_info_t;


uint8_t elf32_strcmp(char* a, char* b)
{
    size_t i = 0;
    while (a[i] != 0 && b[i] != 0)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
        i++;
    }
    if (a[i] != b[i])
    {
        return 0;
    }
    return 1;
}

char* elf32_fgets(FILE* f, size_t offset, size_t* len)
{
    int c;
    char* str = malloc(0);
    size_t strp = 0;
    fseek(f, offset, SEEK_SET);
    while ( (c = fgetc(f)) != EOF )
    {
        str = realloc(str, strp + 1);
        str[strp++] = c;
        if (c == 0) break;
    }
    if (c == EOF)
    {
        str = realloc(str, strp + 1);
        str[strp++] = 0;
    }
    if (len != NULL)
    {
        *len = strp - 1;
    }
    return str;
}

void elf32_reverse(uint8_t* addr, size_t size)
{
    uint8_t* retaddr = malloc(size);
    for (size_t i = 0; i < size; i++)
    {
        retaddr[i] = addr[size - i - 1];
    }
    for (size_t i = 0; i < size; i++)
    {
        addr[i] = retaddr[i];
    }
    free(retaddr);
}

elf32_quicksymbol_t* elf32_get_symbols(FILE* f, elf32_quicksection_t* qsects, size_t* qsyms_count)
{
    elf32_symbol_t* symbol = malloc(sizeof(elf32_symbol_t));
    elf32_quicksymbol_t* qsyms = malloc(0);
    size_t qsymsc = 0;

    for (uint32_t i = 0; i < qsects[ELF32_SECTION_SYMTAB].size / sizeof(elf32_symbol_t); i++)
    {
        uint32_t addr = (uint32_t)(qsects[ELF32_SECTION_SYMTAB].addr) + sizeof(elf32_symbol_t) * i;
        fseek(f, addr, SEEK_SET);
        fread(symbol, sizeof(elf32_symbol_t), 1, f);

        addr = (uint32_t)(qsects[ELF32_SECTION_STRTAB].addr) + (symbol->st_name);
        size_t len;
        char* name = elf32_fgets(f, addr, &len);
        if (len > 0)
        {
            uint8_t keep = 0;
            uint8_t keep_code = 0;
            if (qsects[ELF32_SECTION_DATA].found)
            {
                if (symbol->st_shndx == qsects[ELF32_SECTION_DATA].index)
                {
                    keep = 1;
                    keep_code = ELF32_SECTION_DATA;
                }
            }
            if (qsects[ELF32_SECTION_BSS].found)
            {
                if (symbol->st_shndx == qsects[ELF32_SECTION_BSS].index)
                {
                    keep = 1;
                    keep_code = ELF32_SECTION_BSS;
                }
            }
            if (qsects[ELF32_SECTION_RODATA].found)
            {
                if (symbol->st_shndx == qsects[ELF32_SECTION_RODATA].index)
                {
                    keep = 1;
                    keep_code = ELF32_SECTION_RODATA;
                }
            }
            if  (keep)
            {
                qsyms = realloc(qsyms, sizeof(elf32_quicksymbol_t) * (qsymsc + 1));
                qsyms[qsymsc].addr = symbol->st_addr;
                qsyms[qsymsc].section = keep_code;
                qsymsc++;
            }
        }
        free(name);
    }
    free(symbol);

    if (qsyms_count != NULL)
    {
        *qsyms_count = qsymsc;
    }
    return qsyms;

}

void elf32_free(elf32_info_t* e)
{
    fclose(e->file);
    free(e->sections);
    free(e->symbols);
    free(e);
}

elf32_quicksymbol_t* elf32_order_symbols(elf32_quicksection_t* sections, elf32_quicksymbol_t* symbols, size_t count)
{
    elf32_quicksymbol_t* ret = malloc(sizeof(elf32_quicksymbol_t) * count);
    size_t retc = 0;
    size_t counts[3] = { 0, 0, 0 };
    uint8_t section_order[] = { ELF32_SECTION_DATA, ELF32_SECTION_RODATA, ELF32_SECTION_BSS };
    uint32_t addr_offset = sections[ELF32_SECTION_TEXT].size + (count + 1) * sizeof(uint32_t);
    uint8_t* marked = malloc(count);
    for (size_t i = 0; i < count; i++)
    {
        for (uint8_t j = 0; j < sizeof(section_order); j++)
        {
            if (symbols[i].section == section_order[j])
            {
                counts[j]++;
            }
        }
        marked[i] = 0;
    }
    for (uint8_t s = 0; s < sizeof(section_order); s++)
    {
        for (size_t i = 0; i < counts[s]; i++)
        {
            uint32_t smallest_addr = 0xFFFFFFFF;
            uint32_t smallest_idx = 0xFFFFFFFF;
            for (size_t j = 0; j < count; j++)
            {
                if (symbols[j].section == section_order[s])
                {
                    if ((symbols[j].addr < smallest_addr) && !marked[j])
                    {
                        smallest_addr = symbols[j].addr;
                        smallest_idx = j;
                    }
                }
            }
            if (smallest_idx == 0xFFFFFFFF)
            {
                fprintf(stderr, "elf32_read: Data corruption error. Aborted.\n");
                free(ret);
                return NULL;
            }

            ret[retc].addr = symbols[smallest_idx].addr + addr_offset;
            ret[retc].section = symbols[smallest_idx].section;
            marked[smallest_idx] = 1;
            retc++;
        }
        addr_offset += sections[section_order[s]].size;
    }
    if (retc != count)
    {
        fprintf(stderr, "elf32_read: Data corruption error. Aborted.\n");
        free(ret);
        return NULL;
    }
    free(marked);
    free(symbols);
    return ret;
}

elf32_info_t* elf32_read(char* file)
{
    FILE* f = fopen(file, "r");
    if (!f)
    {
        fprintf(stderr, "elf32_read: Could not open file.\n");
        return NULL;
    }
    elf32_t* e32 = malloc(sizeof(elf32_t));
    fread(e32, sizeof(elf32_t), 1, f);

    if (e32->ei_mag[0] != 0x7F || e32->ei_mag[1] != 0x45 || e32->ei_mag[2] != 0x4C || e32->ei_mag[3] !=  0x46)
    {
        free(e32);
        fprintf(stderr, "elf32_read: Bad magic number.\n");
        fclose(f);
        return NULL;
    }

    if (e32->ei_class != 1) //not 32-bit
    {
        free(e32);
        fprintf(stderr, "elf32_read: Not a 32-bit ELF file.\n");
        fclose(f);
        return NULL;
    }

    if (e32->ei_data != 1) //not 32-bit
    {
        free(e32);
        fprintf(stderr, "elf32_read: Unexpected endianness.\n");
        fclose(f);
        return NULL;
    }

    if (e32->ei_version != 1)
    {
        free(e32);
        fprintf(stderr, "elf32_read: Unsupported ELF version.\n");
        fclose(f);
        return NULL;
    }

    if (e32->ei_osabi != 0x61) //DSLinux OSABI
    {
        fprintf(stderr, "elf32_read: Unexpected OS ABI. Continuing anyways.\n");
    }

    if (e32->ei_abiversion != 0x00) //DSLinux ABIVERSION
    {
        fprintf(stderr, "elf32_read: Unexpected ABI version. Continuing anyways.\n");
    }

    if (e32->e_version != 0x01) //Relocatable file
    {
        free(e32);
        fprintf(stderr, "elf32_read: Not a relocatable file.\n");
        fclose(f);
        return NULL;
    }

    if (e32->e_machine != 0x28) //ARM
    {
        fprintf(stderr, "elf32_read: Unexpected CPU architecture. Continuing anyways.\n");
    }

    if (e32->e_entry != 0)
    {
        free(e32);
        fprintf(stderr, "elf32_read: Entry point must be 0x00000000!\n");
        fclose(f);
        return NULL;
    }

    if (e32->e_shentsize != sizeof(elf32_section_t))
    {
        free(e32);
        fprintf(stderr, "elf32_read: Not a 32-bit ELF file.\n");
        fclose(f);
        return NULL;
    }

    elf32_section_t* nsect = malloc(sizeof(elf32_section_t));
    fseek(f, (e32->e_shoff) + sizeof(elf32_section_t) * (e32->e_shstrndx), SEEK_SET);
    fread(nsect, sizeof(elf32_section_t), 1, f);

    elf32_quicksection_t* qsects = malloc(sizeof(elf32_quicksection_t) * 6);
    for (uint8_t i = 0; i < 6; i++)
    {
        qsects[i].found = 0;
        qsects[i].size = 0;
    }

    for (size_t i = 0; i < (e32->e_shnum); i++)
    {
        elf32_section_t* sect = malloc(sizeof(elf32_section_t));
        fseek(f, (e32->e_shoff) + sizeof(elf32_section_t) * i, SEEK_SET);
        fread(sect, sizeof(elf32_section_t), 1, f);
        char* name = elf32_fgets(f, (nsect->sh_offset) + (sect->sh_name), NULL);

        if (elf32_strcmp(name, ".text"))
        {
            qsects[ELF32_SECTION_TEXT].index = i;
            qsects[ELF32_SECTION_TEXT].addr = sect->sh_offset;
            qsects[ELF32_SECTION_TEXT].size = sect->sh_size;
            qsects[ELF32_SECTION_TEXT].found = 1;
        }
        else if (elf32_strcmp(name, ".data"))
        {
            qsects[ELF32_SECTION_DATA].index = i;
            qsects[ELF32_SECTION_DATA].addr = sect->sh_offset;
            qsects[ELF32_SECTION_DATA].size = sect->sh_size;
            qsects[ELF32_SECTION_DATA].found = 1;
        }
        else if (elf32_strcmp(name, ".bss"))
        {
            qsects[ELF32_SECTION_BSS].index = i;
            qsects[ELF32_SECTION_BSS].addr = sect->sh_offset;
            qsects[ELF32_SECTION_BSS].size = sect->sh_size;
            qsects[ELF32_SECTION_BSS].found = 1;
        }
        else if (elf32_strcmp(name, ".rodata"))
        {
            qsects[ELF32_SECTION_RODATA].index = i;
            qsects[ELF32_SECTION_RODATA].addr = sect->sh_offset;
            qsects[ELF32_SECTION_RODATA].size = sect->sh_size;
            qsects[ELF32_SECTION_RODATA].found = 1;
        }
        else if (elf32_strcmp(name, ".symtab"))
        {
            qsects[ELF32_SECTION_SYMTAB].index = i;
            qsects[ELF32_SECTION_SYMTAB].addr = sect->sh_offset;
            qsects[ELF32_SECTION_SYMTAB].size = sect->sh_size;
            qsects[ELF32_SECTION_SYMTAB].found = 1;
        }
        else if (elf32_strcmp(name, ".strtab"))
        {
            qsects[ELF32_SECTION_STRTAB].index = i;
            qsects[ELF32_SECTION_STRTAB].addr = sect->sh_offset;
            qsects[ELF32_SECTION_STRTAB].size = sect->sh_size;
            qsects[ELF32_SECTION_STRTAB].found = 1;
        }
        free(name);
        free(sect);
    }
    free(nsect);
    free(e32);

    elf32_info_t* info = malloc(sizeof(elf32_info_t));
    info->file = f;
    info->sections = qsects;
    info->symbols = elf32_get_symbols(f, qsects, &(info->symbols_count));

    info->symbols = elf32_order_symbols(info->sections, info->symbols, info->symbols_count);
    if (info->symbols == NULL)
    {
        elf32_free(info);
        return NULL;
    }
    if (!(info->sections[ELF32_SECTION_TEXT].found))
    {
        fprintf(stderr, "elf32_read: Text section not found!\n");
        elf32_free(info);
        return NULL;
    }
    return info;
}

