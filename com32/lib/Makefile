# Include configuration rules
include MCONFIG

LIBOBJS = \
	abort.o \
	atexit.o \
	atoi.o \
	atol.o \
	atoll.o \
	calloc.o \
	creat.o \
	ctypes.o \
	errno.o \
	fgetc.o \
	fgets.o \
	fopen.o \
	fprintf.o \
	fputc.o \
	fputs.o \
	fread2.o \
	fread.o \
	free.o \
	fwrite2.o \
	fwrite.o \
	getopt.o \
	lrand48.o \
	malloc.o \
	memccpy.o \
	memchr.o \
	memcmp.o \
	memcpy.o \
	memmem.o \
	memmove.o \
	memset.o \
	memswap.o \
	onexit.o \
	perror.o \
	printf.o \
	puts.o \
	qsort.o \
	realloc.o \
	seed48.o \
	snprintf.o \
	sprintf.o \
	srand48.o \
	sscanf.o \
	stack.o \
	strcasecmp.o \
	strcat.o \
	strchr.o \
	strcmp.o \
	strcpy.o \
	strdup.o \
	strerror.o \
	strlen.o \
	strncasecmp.o \
	strncat.o \
	strncmp.o \
	strncpy.o \
	strndup.o \
	strntoimax.o \
	strntoumax.o \
	strrchr.o \
	strsep.o \
	strspn.o \
	strstr.o \
	strtoimax.o \
	strtok.o \
	strtol.o \
	strtoll.o \
	strtoul.o \
	strtoull.o \
	strtoumax.o \
	vfprintf.o \
	vprintf.o \
	vsnprintf.o \
	vsprintf.o \
	vsscanf.o \
	sys/entry.o sys/exit.o \
	sys/fileinfo.o sys/opendev.o sys/read.o sys/write.o sys/close.o \
	sys/open.o sys/fileread.o sys/fileclose.o \
	sys/isatty.o sys/openconsole.o sys/line_input.o \
	sys/stdcon.o sys/stdcon_write.o sys/stdcon_read.o \
	sys/rawcon.o sys/rawcon_write.o sys/rawcon_read.o


all: libcom32.a

libcom32.a : $(LIBOBJS)
	rm -f $@
	$(AR) cq $@ $^
	$(RANLIB) $@

tidy:
	rm -f *.o .*.d */*.o */.*.d

clean: tidy
	rm -f *.a

spotless: clean
	rm -f *~ \#* */*~ */\#*

-include .*.d