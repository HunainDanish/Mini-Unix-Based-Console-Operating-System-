CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall
LDFLAGS = -lstdc++fs

# Core source files and target
SRC = main.cpp resources.cpp scheduler.cpp task_manager.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = os_sim

# Task files
TASK_DIR = tasks
TASKS = $(wildcard $(TASK_DIR)/*.cpp)
TASK_BINS = $(patsubst $(TASK_DIR)/%.cpp, $(TASK_DIR)/%, $(TASKS))

# Default target
all: $(EXEC) $(TASK_BINS)

# Link main executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile task apps
$(TASK_DIR)/%: $(TASK_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# Clean everything
clean:
	rm -f $(OBJ) $(EXEC) $(TASK_BINS)

