CXX = g++

CXXFLAGS = -Ofast -ffast-math -flto -fomit-frame-pointer\
						-ftree-vectorize -funroll-loops -march=native -mavx2\
						-Wall -Wcast-align -Wcast-qual -Wconversion\
						-Wdisabled-optimization -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond\
						-Wextra -Wfloat-equal -Wformat=2 -Wlogical-op\
						-Wmisleading-indentation -Wmissing-include-dirs -Wnon-virtual-dtor -Wnull-dereference\
						-Wold-style-cast -Woverloaded-virtual -Wpedantic -Wpointer-arith\
						-Wshadow -Wsign-conversion -Wstrict-aliasing -Wstrict-overflow\
						-Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code\
						-Wunused -Wuseless-cast -Wvla\

# INCLUDES = -Iextern

SOURCES = $(wildcard *.cpp)

# pattern substitution on all cpp files with .o object output name scheme
OBJECTS = $(patsubst %.cpp, build/%.o, $(SOURCES))

# check OS
ifeq ($(OS),Windows_NT)
        EXECUTABLE = a.exe
else
        EXECUTABLE = a.out
endif

all: clean $(EXECUTABLE)
# @./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJECTS)

build/%.o: %.cpp
	@mkdir -p build
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


# don't -rf the build directory, just the files in it
clean:
	@rm -f build/*.o $(EXECUTABLE)