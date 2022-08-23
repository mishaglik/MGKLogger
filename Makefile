LIB_DIR = lib/
BIN_DIR = bin/
SRC_DIR = src/
INC_DIR = ../include/

PROJECT_NAME = "MGKLogger"

MAJOR_VERSION = 0
MINOR_VERSION = 0
BUILD_VERSION = `cat .bld_version`

LIBRARIES = 

CXXFLAGS = `cat $(INC_DIR)Cflags`
SANFLAGS = `cat $(INC_DIR)SanitizeFlags`

CXXFLAGS += -Iinclude -I$(INC_DIR) 
LXXFLAGS = -L$(LIB_DIR) $(addprefix -l, $(LIBRARIES))

CXXFLAGS += -DMAJOR_VERSION=$(MAJOR_VERSION)
CXXFLAGS += -DMINOR_VERSION=$(MINOR_VERSION)
CXXFLAGS += -DBUILD_VERSION=$(BUILD_VERSION)

CXXFLAGS += $(SANFLAGS)

SUBDIRS = ${shell find $(SRC_DIR) -type d -printf '%P '}

SRC = $(shell find $(SRC_DIR) -name *.cpp -printf "%P ")

OBJ = $(SRC:.cpp=.o)

DEP = $(SRC:.cpp=.d)

# Custom part of makefile: targets definiton

TARGETS = main lib

main: $(addprefix $(BIN_DIR), $(OBJ))
	g++ $(CXXFLAGS) $^ $(LXXFLAGS) -o $@\

.PHONY: lib
lib: $(LIB_DIR)MGKLogger.so
	echo "Lib builded"

$(LIB_DIR)MGKLogger.so: $(BIN_DIR)MGKLogger.a
	mkdir $(LIB_DIR)MGKLogger -p
	g++ -shared -o $@ $<
	cp $(SRC_DIR)MGKLogger.hpp $(INC_DIR)MGKLogger/

$(BIN_DIR)MGKLogger.a: $(addprefix $(BIN_DIR), $(filter-out main.o, $(OBJ)))
	ar crf $@ $^

# Base part of makefile

.PHONY: init
init: $(addprefix $(BIN_DIR), $(SUBDIRS)) 
	echo "Inited project"

.PHONY: deps
deps: $(addprefix $(BIN_DIR), $(DEP))
	echo "Deps builded"

$(addprefix $(BIN_DIR), $(SUBDIRS)): % :
	mkdir -p $@

all: $(TARGETS)
	# ./increaseVersion.sh bld_version

$(BIN_DIR)%.o : $(SRC_DIR)%.cpp Makefile build_version
	g++ -c $(CXXFLAGS) -o $@ $<


$(BIN_DIR)%.d : $(SRC_DIR)%.cpp $(BIN_DIR)$(dir %)
	g++ -MM -MT $(@:.d=.o) $< -o $@

-include $(addprefix $(BIN_DIR), $(DEP))

.PHONY: clean
clean:
	rm -f $(addprefix $(BIN_DIR), $(OBJ) $(DEP))
	rm -f $(TARGETS)

.PHONY: build_version
build_version:
	echo $$(( $(BUILD_VERSION) + 1 )) > .bld_version