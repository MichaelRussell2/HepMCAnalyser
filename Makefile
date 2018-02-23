TARGET = analysis
####################################
CC = $(shell root-config --cxx)
OBJS = $(TARGET).o histo.o
######### DEPENDENCIES #####################
homedir	   = /remote/bigmem03/russell
HEPMC      = ${homedir}/Install
######### ROOT #####################
CXXFLAGS   = -I/remote/bigmem03/russell/Install/include	
######### HEPMC ####################
HepMCdir = ${HEPMC}
HepMClib = -L$(HepMCdir)/lib -lHepMC
######### FASTJET ##################
FASTJETLIB  = -L${FASTJET}/lib -lfastjet -Wl,-rpath=/remote/bigmem03/russell/Install/lib #-lNsubjettiness
#FASTJETLIB  = $(shell fastjet-config --libs) #-lNsubjettiness
#-------- INCLUDE -----------------#
INCLUDE=./include
INCLUDES = -I${INCLUDE}
INCLUDES += -I${HepMCdir}/include 
INCLUDES += -I${FASTJET}/include 
INCLUDES += -I./
#########  FLAGS, LIBS  ############
CXXFLAGS += ${INCLUDES}
CXXLIBS = ${HepMClib} ${FASTJETLIB}
#########################################################

all: $(TARGET)

%.o: %.cc
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(CXXLIBS)

# analysis: $(OBJS)
# 	$(CC) $(CXXFLAGS)  $(OBJS) $(CXXLIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJS)

test:
	@echo $(FASTJET)
