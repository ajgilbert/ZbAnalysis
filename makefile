# name of the library
LIBNAME = ZbAnalysis

#USERINCLUDES += -I$(ROOTSYS)/include
#USERINCLUDES += -I$(ROOTSYS)/include/Reflex
#USERINCLUDES += -I $(CMSSW_BASE)/src/ -I $(CMSSW_RELEASE_BASE)/src/

#USERLIBS +=  -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lz -lGui -lReflex -lReflexDict -pthread -lm -ldl -rdynamic
#USERLIBS +=  -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lz -lGui -pthread -lm -ldl -rdynamic

#USERLIBS +=   -L $(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeHbbAnalysis  -lCondFormatsPhysicsToolsObjects -lRecoBTagPerformanceDB
#USERLIBS +=  -L $(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite -L /afs/cern.ch/cms/sw/slc5_ia32_gcc434/cms/cmssw/CMSSW_3_6_1/lib/$(SCRAM_ARCH) -lFWCoreFWLite

CXXFLAGS = -Wall -W -Wold-style-cast -O2
LDFLAGS = -shared -Wall -W 
# -ansi

CXX=g++
LD=g++

AR = ar

INCLUDE +=  -I $(BASEDIR)/interface
INCLUDE += $(USERINCLUDES)
CXXFLAGS += $(INCLUDE)

LIBS += $(USERLIBS)


# this is where you  would normaly have the lib, bin and source directories
BASEDIR = .
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
MACRODIR = $(BASEDIR)/src
SRCDIR = $(BASEDIR)/src
OBJDIR = $(BASEDIR)/obj
TESTDIR = $(BASEDIR)/test
OBJ_EXT=o
TEST_EXT=cpp

SRCS=$(wildcard $(BASEDIR)/src/*.cc)
EXES=$(wildcard $(BASEDIR)/test/*.cpp)
OBJS=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(SRCS)))
BINS=$(subst $(TESTDIR), $(EXEDIR),$(subst .$(TEST_EXT),,$(EXES)))

all:  $(BINS) 

$(EXEDIR)/%: $(TESTDIR)/%.cpp $(LIBDIR)/lib$(LIBNAME).so
	$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) -L$(LIBDIR) -l$(LIBNAME)

$(OBJDIR)/%.$(OBJ_EXT): $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $<  -o $@

$(LIBDIR)/lib$(LIBNAME).so:$(OBJS)
	$(LD) $(LDFLAGS) -o $(LIBDIR)/lib$(LIBNAME).so  $^
	
	#$(LD) $(LDFLAGS) -o $(LIBDIR)/lib$(LIBNAME).so  $^ $(LIBS)

lib: $(LIBDIR)/lib$(LIBNAME).so

vars:
	@echo "LIBS: " $(LIBS)
	@echo "CXXFLAGS: " $(CXXFLAGS)
	@echo "Source files: " $(SRCS) 
	@echo "Object files: " $(OBJS)
	@echo "Executables:  " $(TARGETS)

clean:
	rm -f $(OBJS) $(LIBDIR)/lib$(LIBNAME).so $(BINS)


