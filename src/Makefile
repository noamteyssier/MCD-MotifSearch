# compiler
CC=g++

# libraries
# BOOST_PO = -l boost_program_options
# BOOST_FS = -l boost_filesystem
# LIBS = $(BOOST_PO) $(BOOST_FS)

# compiler flags
CFLAGS= -g -Wall -Ofast -march=native -fopenmp #-I /usr/include/boost

BINARY = bin/distance_network
MAIN = main.cpp
UTILS = utils/*.hpp

all: $(BINARY)

$(BINARY): $(MAIN)
	$(CC) $(CFLAGS) $(UTILS) $(MAIN) -o $(BINARY)

clean:
	rm -v $(BINARY)
