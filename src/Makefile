# compiler

# libraries
# BOOST_PO = -l boost_program_options
# BOOST_FS = -l boost_filesystem
# LIBS = $(BOOST_PO) $(BOOST_FS)

# compiler flags
CXXFLAGS	= -std=c++17 -Ofast -march=native -g -Wall -fopenmp
OBJFILES 	= main.o utils/kmertools.o utils/networktools.o
TARGET   	= bin/distance_network

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -v $(TARGET) $(OBJFILES)
