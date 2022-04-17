LIB_DIR = lib/
BIN_DIR = bin/
SRC_DIR = src/
INC_DIR = ../include/

MAJOR_VERSION = 0
MINOR_VERSION = 0
# BUILD_VERSION = 0			# - Not implementted yet

LIBRARIES = 

CXXFLAGS = `cat $(INC_DIR)Cflags`
SANFLAGS = `cat $(INC_DIR)SanitizeFlags`

CXXFLAGS += -Iinclude -I$(INC_DIR) 
LXXFLAGS = -L$(LIB_DIR) $(addprefix -l, $(LIBRARIES))

CXXFLAGS += -DMAJOR_VERSION=$(MAJOR_VERSION)
CXXFLAGS += -DMINOR_VERSION=$(MINOR_VERSION)
# CXXFLAGS += -DBUILD_VERSION=$(BUILD_VERSION)

CXXFLAGS += $(SANFLAGS)

SUBDIRS = ${shell find $(SRC_DIR) -type d -printf '%P '}

SOURCES =  $(foreach dir, $(SUBDIRS), $(addprefix $(dir)/, $(SOURCES_$(dir))))

SRC = $(shell find $(SRC_DIR) -name *.cpp -printf "%P ")

OBJ = $(SRC:.cpp=.o)

DEP = $(SRC:.cpp=.d)

TARGETS = main

main: $(addprefix $(BIN_DIR), $(OBJ))
	g++ $(CXXFLAGS) $^ $(LXXFLAGS) -o $@
.PHONY: lib
lib: $(BIN_DIR)MGKLogger.a
	cp $(BIN_DIR)MGKLogger.a $(LIB_DIR)MGKLogger.a
	mkdir $(INC_DIR)MGKLogger -p
	cp $(SRC_DIR)/MGKLogger.hpp $(INC_DIR)MGKLogger/

$(BIN_DIR)MGKLogger.a: $(addprefix $(BIN_DIR), $(filter-out main.o, $(OBJ)))
	ar crf $@ $^

.PHONY: init
init: 
	echo Inited

$(addprefix $(BIN_DIR), $(SUBDIRS)): % :
	mkdir -p $@

all: $(TARGETS)
	# ./increaseVersion.sh bld_version

$(BIN_DIR)%.o : $(SRC_DIR)%.cpp
	g++ -c $(CXXFLAGS) $(LXXFLAGS) -o $@ $<

.PHONY: deps
deps: $(addprefix $(BIN_DIR), $(DEP))
	echo "Deps builded"
	
$(BIN_DIR)%.d : $(SRC_DIR)%.cpp Makefile $(BIN_DIR)$(dir %)
	g++ -MM -MT $(@:.d=.o) $< -o $@

-include $(addprefix $(BIN_DIR), $(DEP))

.PHONY: clean
clean:
	rm -f $(addprefix $(BIN_DIR), $(OBJ) $(DEP))
	rm $(TARGETS)
