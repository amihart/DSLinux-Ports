#########################################################
#the configure file seems to incorectly replace "--host"
#  with "--build" leading to conflicts between the parent
#  configure file and the subconfigure files
#########################################################
./configure --host=arm-linux --prefix=/usr
files=$(grep -ri '\-\-build\=arm\-linux' `pwd` | cut -d':' -f1 | uniq)
for i in $files
do
	cat $i \
	| sed 's/--build=arm-linux/--host=arm-linux/g' \
	| sed 's/^[ \t]*LDFLAGS[ \t]*=[ \t]*$//g' \
	> .tmp && mv .tmp $i
done
#########################################################
#dwarf2dbg needs to be patched as it incorrectly sets a
# varible to global which should be static, leading to
# linking conflicts
#########################################################
cat gas/dwarf2dbg.c | \
sed 's/^bfd_boolean dwarf2_loc_mark_labels;$/static bfd_boolean dwarf2_loc_mark_labels;/' \
> .tmp
mv .tmp gas/dwarf2dbg.c
cat gas/dwarf2dbg.h | \
sed 's/^bfd_boolean dwarf2_loc_mark_labels;$/\/\/bfd_boolean dwarf2_loc_mark_labels;/' \
> .tmp
mv .tmp gas/dwarf2dbg.h
#########################################################
make
