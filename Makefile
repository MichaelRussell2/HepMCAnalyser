TARGET = analysis
OBJS = $(TARGET).o histo.o
CC = g++ -O2
HEPMC = /Users/michael/Install
INCDIR = -I./include $(shell fastjet-config --cxxflags) -I${HEPMC}/include 
LIBDIR = $(shell fastjet-config --libs) -L$(HEPMC)/lib -lHepMC 
CXXFLAGS = ${INCDIR}
CXXLIBS = ${LIBDIR}

all: $(TARGET)

%.o: %.cc
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(CXXLIBS)

clean:
	rm -f $(TARGET) $(OBJS)
