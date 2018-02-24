TARGET = analysis
####################################
CC = g++
OBJS = $(TARGET).o histo.o
homedir	   = /remote/bigmem03/russell
######### HEPMC ####################
HEPMC      = ${homedir}/Install
HepMCdir = ${HEPMC}
HepMClib = -L$(HepMCdir)/lib -lHepMC
######### FASTJET ##################
FASTJET	  = ${homedir}/Install
FASTJETLIB  = -L${FASTJET}/lib -lfastjet -Wl,-rpath=${FASTJET}/lib #-lNsubjettiness
#FASTJETLIB  = $(shell fastjet-config --libs) #-lNsubjettiness
#-------- INCLUDE -----------------#
INCLUDES=-I./include -I${HepMCdir}/include -I${FASTJET}/include 
#########  FLAGS, LIBS  ############
CXXFLAGS = ${INCLUDES}
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
