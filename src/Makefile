# compiler

# libraries
# BOOST_PO = -l boost_program_options
# BOOST_FS = -l boost_filesystem
# LIBS = $(BOOST_PO) $(BOOST_FS)

# compiler flags
CXX 		= /usr/local/opt/llvm/bin/clang++
CXXFLAGS	= -std=c++17 -Ofast -march=native -g -Wall
LDFLAGS		= -fopenmp -L/usr/local/opt/libomp/lib/
OBJFILES 	= main.o utils/kmertools.o utils/networktools.o
TARGET   	= bin/distance_network

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -v $(TARGET) $(OBJFILES)
