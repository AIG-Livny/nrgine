# Create Makefile according to example below and check/edit path to common.mk if required.
# OUT_FILE - name of out file. Name and extension defines type of file:
# 	executable:  		without extension
#	static library:		lib%.a
#	dynamic library:	%.dll or %.so
# To multithread building, run "make -j"

#----------------------------------------------------------------
#OUT_FILE        = bin/example.dll
#include common.mk
#----------------------------------------------------------------

# List of optional variables:
# GCC replaces СС:	 compiler
# SUBPROJECTS: list of subprojects:
#		SUBPROJECTS 	+= lib/somesub/bin/libsomesub.a
#	    Make will run building or cleaning for subprojects, but one level above(!):
#		make -c lib/somesub  
# LIB_DIRS: list of paths for searching libraries not recursively
# INC_DIRS: list of paths for searching includes not recursively
# SRC_DIRS: list of paths for searching sources (!) recursively
# OBJ_PATH: where will be placed object files 
# TESTS_DIR: path to testing sources
# SRC_EXTS: list of sources masks (*.cpp)
# LINK_FLAGS: 
# SOURCES: list of sources. After recursive search here will be full list
# 		but before search, you can add any other individual files
# AR_FLAGS: archiver flags
# EXCLUDESRC: list of sources exclusions 

#----------------------------------------------------------------

# Assert variable / set default value if not set
check_variable = $(if $(value $(1)),, $(error $(1) not defined))
default_variable = $(if $(value $(1)),, $(eval $(1) = $(2)))

# Recursive search
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Colorful text Win/Lin 
color_text = $(if $(filter Windows_NT, $(OS)),"[$(1)m$(2)[0m","\\033[$(1)m$(2)\\033[0m")


# Variables checking, setting defaults
$(call check_variable ,OUT_FILE)
$(call default_variable ,SRC_DIRS,src)
$(call default_variable ,INC_DIRS,. include)
$(call default_variable ,OBJ_PATH,obj)
$(call default_variable ,TESTS_DIR,test)
$(call default_variable ,SRC_EXTS,*.cpp)
$(call default_variable ,GCC,g++)
$(call default_variable ,AR,ar)
$(call default_variable ,LINK_FLAGS,-O3)
$(call default_variable ,CFLAGS,-std=c++17 -O3)
$(call default_variable ,AR_FLAGS,rcs)

SUBPROJECTS_DIRS = $(subst bin/,,$(dir $(SUBPROJECTS)))
LIB_DIRS := $(addprefix -L, $(LIB_DIRS))
INC_DIRS := $(addprefix -I, $(INC_DIRS))
LIBS := $(addprefix -l, $(LIBS))

# Project files
SOURCES += $(foreach dr, $(SRC_DIRS), $(foreach ext, $(SRC_EXTS),  $(call rwildcard,$(dr),$(ext))))
SOURCES := $(filter-out $(EXCLUDESRC),$(SOURCES))
OBJECTS = $(foreach src, $(SOURCES), $(OBJ_PATH)/$(basename $(src)).o)
DEPS    = $(OBJECTS:%.o=%.d)

# Tests files
TESTS_SOURCES += $(foreach ext,$(SRC_EXTS),$(call rwildcard,$(TESTS_DIR),$(ext)))
TESTS_OBJECTS = $(foreach src, $(TESTS_SOURCES), $(OBJ_PATH)/$(basename $(src)).o)
TESTS_DEPS    = $(TESTS_OBJECTS:%.o=%.d)

# Artificial targets
.PHONY: all app tests clean cleanall clean.withsubprojects cleanall.withsubprojects runtest run

all: app $(if $(strip $(TESTS_SOURCES)),tests,)
app: $(SUBPROJECTS) $(OUT_FILE)
tests: app $(TESTS_DIR)/bin/test
run: app
	@$(OUT_FILE)	
runtest: tests
	@$(TESTS_DIR)/bin/test


clean:
	@rm -rf ./$(OBJ_PATH)

cleanall: clean
	@rm -rf ./$(OUT_FILE)
	@rm -rf ./$(dir $(OUT_FILE))
	@rm -rf ./$(TESTS_DIR)/bin

# Cleaning with subprojects too
clean.withsubprojects: clean $(addprefix clean., $(SUBPROJECTS_DIRS))
cleanall.withsubprojects: cleanall $(addprefix cleanall., $(SUBPROJECTS_DIRS))
	
# Calls make for all subprojects
$(addprefix clean., $(SUBPROJECTS_DIRS)): clean.%:
	@$(MAKE) -C $* clean
$(addprefix cleanall., $(SUBPROJECTS_DIRS)): cleanall.%:
	@$(MAKE) -C $* cleanall

# Making subprojects
$(SUBPROJECTS):
	@$(MAKE) -C $(subst bin/,,$(dir $@))

# Making dependency files
$(OBJ_PATH)/%.d: %.c*
	@echo $(call color_text,95,Deps file): $@
	@mkdir -p $(dir $@)
	@$(GCC) -M -MMD -MT $(OBJ_PATH)/$*.o $(INC_DIRS) $(CFLAGS) $< -o $@

# Executable link
$(basename $(OUT_FILE)): $(DEPS) $(OBJECTS)
	@echo $(call color_text,32,Linking executable): $@
	@mkdir -p $(dir $@)
	@$(GCC) $(LIB_DIRS) $(LINK_FLAGS) $(OBJECTS) -o $@ $(LIBS)
	@size $@$(if $(filter Windows_NT, $(OS)),.exe,)

# Static lib link
lib%.a: $(DEPS) $(OBJECTS)
	@echo $(call color_text,33,Linking static): $@
	@mkdir -p $(dir $@)
	@$(AR) $(AR_FLAGS) $(LIB_DIRS) $@ $(OBJECTS) $(LIBS)
	@size $@

# Shared lib link
%.so %.dll:
	@echo $(call color_text,33,Linking shared): $@
	@mkdir -p $(dir $@)
	@$(GCC) -shared $(LIB_DIRS) $(LINK_FLAGS) $(OBJECTS) -o $@ $(LIBS)
	@size $@$(if $(filter Windows_NT, $(OS)),.dll,.so)

# Tests link: exe for each .cpp
#$(TESTS_DIR)/bin/%: %.c*
#	@echo $(call color_text,33,Linking test): $@
#	@mkdir -p $(dir $@)
#	@$(GCC) $(LIB_DIRS) $(LINK_FLAGS) $(OBJECTS:%main.o=) $* -o $@ $(LIBS)

# Tests link: all in one exe
$(TESTS_DIR)/bin/test: $(TESTS_DEPS) $(TESTS_OBJECTS) $(OBJECTS)
	@echo $(call color_text,33,Linking test): $@
	@mkdir -p $(dir $@)
	@$(GCC) $(LIB_DIRS) $(LINK_FLAGS) $(OBJECTS:%main.o=) $(TESTS_OBJECTS) -o $@ $(LIBS)

# Include all dependecy files for recompile on changing one of them
-include $(call rwildcard,$(OBJ_PATH),*.d)

# Special rule for tests building
$(OBJ_PATH)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c*
	@echo  $(call color_text,92,Building test): $@
	@mkdir -p $(dir $@)
	@$(GCC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

# Sources building
$(OBJ_PATH)/%.o: %.c*
	@echo  $(call color_text,94,Building): $@
	@mkdir -p $(dir $@)
	@$(GCC) $(CFLAGS) $(INC_DIRS) -c $< -o $@