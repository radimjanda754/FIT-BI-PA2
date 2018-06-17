#Semestral project - Unlimited precision calculator
#Author: Radim Janda, 2014s
BINARY=jandara2

CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
CXX=g++
LD=g++

DOXY=Doxyfile
SRCDIR=src
DOCDIR=doc

OBJECTS =\
	$(SRCDIR)/reader.o\
	$(SRCDIR)/classicinput.o\
	$(SRCDIR)/bigdouble.o\
	$(SRCDIR)/parser.o\
	$(SRCDIR)/readerwrite.o\
	$(SRCDIR)/main.o

# All
all: compile doc

# Compile - command
compile: $(BINARY)

# Compile into binary file
$(BINARY): $(OBJECTS)
	$(LD) -o $(BINARY) $(OBJECTS)

# Run
run:
	./$(BINARY)

# Make documentation
doc:
	doxygen $(DOXY)

# Clean
clean:
	rm -Rf $(BINARY) $(OBJECTS) $(DOCDIR)

# Object relations
$(SRCDIR)/bigdouble.o: $(SRCDIR)/bigdouble.cpp $(SRCDIR)/bigdouble.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/classicinput.o: $(SRCDIR)/classicinput.cpp $(SRCDIR)/classicinput.h $(SRCDIR)/reader.h \
 $(SRCDIR)/bigdouble.h $(SRCDIR)/readerwrite.h $(SRCDIR)/parser.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/classicinput.h $(SRCDIR)/reader.h $(SRCDIR)/bigdouble.h \
 $(SRCDIR)/readerwrite.h $(SRCDIR)/parser.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/parser.o: $(SRCDIR)/parser.cpp $(SRCDIR)/parser.h $(SRCDIR)/bigdouble.h $(SRCDIR)/reader.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/reader.o: $(SRCDIR)/reader.cpp $(SRCDIR)/reader.h $(SRCDIR)/bigdouble.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/readerwrite.o: $(SRCDIR)/readerwrite.cpp $(SRCDIR)/readerwrite.h $(SRCDIR)/reader.h \
 $(SRCDIR)/bigdouble.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

