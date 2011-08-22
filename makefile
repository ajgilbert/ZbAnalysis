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
OBJ_EXT=o

SRCS=$(wildcard $(BASEDIR)/src/*.cc)
EXES=$(wildcard $(BASEDIR)/src/*.cpp)
OBJS=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(SRCS)))

# deduce the targets:
#TARGETS=$(subst .C,,$(subst $(MACRODIR),$(EXEDIR),$(EXES)))
#TARGETS=$(subst .cpp,,$(subst $(SRCDIR),$(EXEDIR),$(SRC)))


#all:  $(OBJS) lib  $(EXEDIR)/selection $(EXEDIR)/selectionTable $(EXEDIR)/qcd $(EXEDIR)/treeLoop $(EXEDIR)/treePlots $(EXEDIR)/fillHistosFromTree $(EXEDIR)/triggerEfficiency $(EXEDIR)/genLevelInfo $(EXEDIR)/skimTrees
#all:  $(OBJS) lib $(EXES) $(EXEDIR)/fillZbbHistosFromTree $(EXEDIR)/selection $(EXEDIR)/selectionTable $(EXEDIR)/skimTrees $(EXEDIR)/selectionTableJES 
all:  lib 
#$(EXEDIR)/fillInclusiveJetHistos

#all:  $(OBJS) lib $(EXEDIR)/fillInclusiveJetHistos $(EXEDIR)/printEvents


#$(EXEDIR)/fillHistosFromTree $(EXEDIR)/skimTrees $(EXEDIR)/selection $(EXEDIR)/selectionTable $(EXEDIR)/jetTriggerEfficiency


$(OBJDIR)/%.$(OBJ_EXT): $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $<  -o $@

#$(EXEDIR)/selection:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/selection.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

#$(EXEDIR)/selectionTable:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/selectionTable.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

#$(EXEDIR)/qcd:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/qcd.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

#$(EXEDIR)/treeLoop:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/treeLoop.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

#$(EXEDIR)/treePlots:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/treePlots.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

#$(EXEDIR)/fillHistosFromTree:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/fillHistosFromTree.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)


#$(EXEDIR)/test:$(OBJS) $(LIBDIR)/lib$(PROGNAME).so
#	$(CXX) -o  $@ $(CXXFLAGS) $(MACRODIR)/test.cpp $(LIBS) -L $(LIBDIR)  -l$(PROGNAME)

$(LIBDIR)/lib$(LIBNAME).so:$(OBJS)
	mkdir -p $(LIBDIR)
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
	rm -f $(OBJS) $(LIBDIR)/lib$(LIBNAME).so


