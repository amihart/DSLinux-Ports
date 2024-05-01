################################################################################################
# bFLT v4 loader for IDA
#
# Identifies and sets appropriate data segments.
# Patches relocation and GOT addresses so that string and data references are resolved properly.
#
# Craig Heffner
# Tactical Network Solutions
# 06-March-2011
################################################################################################

BFLT_VERSION          = 4
BFLT_MAGIC            = "bFLT"
BFLT_HEADER_SIZE      = 0x40
FLAGS_RAM             = 0x01
FLAGS_GOTPIC          = 0x02
FLAGS_GZIP            = 0x04
DEFAULT_CPU           = "ARM"
DEBUG                 = True


def accept_file(li, n):

	retval = 0

	if n == 0:
		li.seek(0)

		# Make sure this is a bFLT v4 file
		if li.read(4) == BFLT_MAGIC and struct.unpack(">I", li.read(4))[0] == BFLT_VERSION:
			retval = "%s v%d executable" % (BFLT_MAGIC, BFLT_VERSION)

	return retval


def load_file(li, neflags, format):

        # Read in the bFLT header fields
	li.seek(0)
	(magic, version, entry, data_start, data_end, bss_end, stack_size, reloc_start, reloc_count, flags) = struct.unpack(">IIIIIIIIII", li.read(4*10))

        # Check for the GZIP flag.
        # The loader doesn't de-compress GZIP'd files, as these can be easily decompressed with external tools prior to loading the file into IDA
        if (flags & FLAGS_GZIP) == FLAGS_GZIP:
                Warning("Code/data is GZIP compressed. You probably want to decompress the bFLT file with the flthdr or gunzip_bflt utilities before loading it into IDA.")

        # Load the file data (sans header) into IDA
	li.file2base(entry, entry, data_end, True)

        # Add the .text .data and .bss segments
	add_segm(0, entry, data_end, ".text", "CODE")
	add_segm(0, data_start, data_end, ".data", "DATA")
        add_segm(0, data_end, bss_end, ".bss", "BSS")

        if DEBUG:
                print "Created File Segments: "
                print "\t.text   0x%.8X - 0x%.8X" % (entry, data_start)
                print "\t.data   0x%.8X - 0x%.8X" % (data_start, data_end)
                print "\t.bss    0x%.8X - 0x%.8X" % (data_end, bss_end)
        
        # Entry point is at the beginning of the .text section
	add_entry(entry, entry, "_start", 1)

	# Set default processor
        set_processor_type(DEFAULT_CPU, SETPROC_ALL)

        # Explicitly set 32 bit addressing on .text segment
        set_segm_addressing(getseg(entry), 1)

        # Is there a global offset table?
        if (flags & FLAGS_GOTPIC) == FLAGS_GOTPIC:

                # Add a reptable comment and name the offset so that all references to GOT are obvious
                MakeRptCmt(data_start, "GLOBAL_OFFSET_TABLE")
                MakeName(data_start, "GOT")

                if DEBUG:
                        print "Global Offset Table detected, patching..."

                # GOT starts at the beginning of the data section; loop through the data section, patching up valid GOT entries.
                i = data_start
                while i < data_end:

                        # Get the next GOT entry
                        li.seek(i)
                        got_entry = struct.unpack("<I", li.read(4))[0]

                        # The last GOT entry is -1
                        if got_entry == 0xFFFFFFFF:
                                if DEBUG:
                                        print "Finished processing Global Offset Table."
                                break

                        # All other non-zero entries are valid GOT entries
                        elif got_entry > 0:

                                # The actual data is located at <original GOT entry> + <BFLT_HEADER_SIZE>
                                new_entry = got_entry + BFLT_HEADER_SIZE
                                
                                if DEBUG:
                                        print "Replacing GOT entry value 0x%.8X with 0x%.8X at offset 0x%.8X" % (got_entry, new_entry, i)

                                # In case this is a text reference, try to create a string at the data offset address.
                                # If that fails, just make it a DWORD.
                                if not Name(new_entry):
					if not MakeStr(new_entry, BADADDR):
                                        	MakeDword(new_entry)

                                # Patch the GOT entry with the correct pointer
                                PatchDword(i, new_entry)
                                
                        # Make each GOT entry a DWORD
                        MakeDword(i)

                        # Point i at the next GOT entry address
                        i = i + 4
                        
        # Patch relocation addresses
        for i in range(0, reloc_count):
                try:
                        # Get the next relocation entry.
                        # Relocation entry = <address of bytes to be patched> - <BFLT_HEADER_SIZE>
                        li.seek(reloc_start + (i * 4))
                        reloc_offset = struct.unpack(">I", li.read(4))[0] + BFLT_HEADER_SIZE

                        # Sanity check, make sure the relocation offset is in a defined segment
                        if reloc_offset < bss_end:
                        
                                try:
                                        # reloc_offset + base_offset == <pointer to actual data> - <BFLT_HEADER_SIZE>
                                        li.seek(reloc_offset)
                                        reloc_data_offset = struct.unpack(">I", li.read(4))[0] + BFLT_HEADER_SIZE

                                        if DEBUG:
                                                print "Patching reloc: (0x%.8X) == 0x%.8X" % (reloc_offset, reloc_data_offset)
                                        
                                        # In case this is a text reference, try to create a string at the data offset address.
                                        # If that fails, just make it a DWORD.
                                        if not Name(reloc_data_offset):
                                        	if not MakeStr(reloc_data_offset, BADADDR):
                                                	MakeDword(reloc_data_offset)
        
                                        # Replace pointer at reloc_offset with the address of the actual data
                                        PatchDword(reloc_offset, reloc_data_offset)
                                except Exception, e:
                                        print "Error patching relocation entry #%d: %s" % (i, str(e))
                        elif DEBUG:
                                print "Relocation entry #%d outside of defined file sections, skipping..." % i
                except Exception, e:
                        print "Error processing relocation entry #%d: %s" % (i, str(e))
                
	return 1
