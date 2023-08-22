CXX      := -g++
CXXFLAGS := -Wall -Wextra -Werror
#CXXFLAGS := -Wall -Wextra -Werror -std=c++17 -fsanitize=address, undefined -fno-omit-frame-pointer -g -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts
#CXXFLAGS := -Wall -Wextra -Werror -std=c++17 -fsanitize=address,undefined -fno-omit-frame-pointer -g
LDFLAGS  := -lstdc++
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/
DATA_SET := ./dataset
TARGET   := app
INCLUDE  := -Iinclude/
SRC      :=  $(wildcard src/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(DATA_SET)/*.gm

run:
	./$(BUILD)/$(TARGET)