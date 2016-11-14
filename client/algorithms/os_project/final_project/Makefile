CROSS_COMPILE=
CC=${CROSS_COMPILE}gcc
CXX=${CROSS_COMPILE}g++
LD=${CROSS_COMPILE}ld
AR=${CROSS_COMPILE}ar
RANLIB=${CROSS_COMPILE}ranlib

BUILDDIR = build

#
# Check if we are in the build ($(BUILDDIR)) directory. If not, change to there
# and call the Makefile again. This allows us to easily put all the object
# files to a build directory without prefixing $(BUILDDIR)/ to every target.
#
# $CURDIR - the current directory path
# $MAKECMDGOALS - make target given on the command line
#
ifneq ($(notdir $(CURDIR)),$(BUILDDIR))

# clear all the build rules if not in the build directory
.SUFFIXES:

# change to the build directory while invoking this Makefile again, where
# $ORIGDIR is set to the current $CURDIR
.PHONY: $(BUILDDIR)
$(BUILDDIR):
	+@[ -d $@ ] || mkdir -p $@
	+@$(MAKE) --no-p -C $@ -f $(CURDIR)/Makefile\
 ORIGDIR=$(CURDIR) $(MAKECMDGOALS)

# do not rebuild any makefiles, this avoids entering an infinite loop due
# to the following catch-all rule
Makefile $(MAKEFILES) :: ;

# matches all rules and force them to rebuild in the build directory
% :: $(BUILDDIR) ;

# Main build settings and commands
else

ifndef ORIGDIR
ORIGDIR = $(CURDIR)
endif
DEPDIR = dep

SRC_DIR  = $(ORIGDIR)/src
INCL_C   = -I$(SRC_DIR)
INCL_CXX = -I$(SRC_DIR)

CFLAGS   = $(INCL_C) -O3 -Wall --std=c99
CXXFLAGS = $(INCL_CXX) -O3 -Wall --std=c++03

# source files for the executable targets
PRJ2_C  = prj2.c prj2_thread.c prj2_scheduling.c multicore_sim.c dispatch_func.c balance_func.c

# object files for the executable targets
PRJ2_OBJ=$(PRJ2_C:%.c=%.o)

# assembly files  
PRJ2_ASM=$(PRJ2_C:%.c=%.S)

# executable targets
PRJ2_EXE= $(ORIGDIR)/prj2

vpath %.c  $(SRC_DIR)
vpath %.cc $(SRC_DIR)

.PHONY: all
all: exe asm

.PHONY: show
show:
	@echo "targets: all exe asm"

.PHONY: exe
exe: $(PRJ2_EXE)

.PHONY: asm
asm: $(PRJ2_ASM)

-include $(PRJ2_C:%.c=$(DEPDIR)/%.d)

$(PRJ2_EXE): $(PRJ2_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -lrt

%.o : %.c dep
	touch $(DEPDIR)/$*.d
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

%.S : %.c dep
	touch $(DEPDIR)/$*.d
	$(CC) $(CFLAGS) -S $< -o $*.S

dep:
	@[ -d $(DEPDIR) ] || mkdir $(DEPDIR)

clean:
	cd ..; rm -rf $(BUILDDIR)/* $(PRJ2_EXE)

endif
