# name of the library
LIBNAME = ZbAnalysis

USERINCLUDES += $(shell root-config --cflags)
USERINCLUDES += -I$(ROOTSYS)/include
USERINCLUDES += -I$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.44.0-cms/include/
USERINCLUDES += -I $(CMSSW_BASE)/src/ -I $(CMSSW_RELEASE_BASE)/src/

USERLIBS += $(shell root-config --glibs) 
#USERLIBS +=  -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lz -lGui -pthread -lm -ldl -rdynamic

USERLIBS += -L$(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeHbbAnalysis
USERLIBS += -L$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.44.0-cms/lib/ -lboost_regex
USERLIBS += -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite

#-lCondFormatsPhysicsToolsObjects -lRecoBTagPerformanceDB
CXXFLAGS = -Wall -W -O2 
LDFLAGS = -shared -Wall -W 
# -ansi

CXX=clang++
LD=clang++

AR = ar

INCLUDE +=  -I $(BASEDIR)/interface
INCLUDE += $(USERINCLUDES)
CXXFLAGS += $(INCLUDE)

LIBS += $(USERLIBS)


# this is where you  would normaly have the lib, bin and source directories
BASEDIR = $(shell pwd)
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
MACRODIR = $(BASEDIR)/src
SRCDIR = $(BASEDIR)/src
OBJDIR = $(BASEDIR)/obj
TESTDIR = $(BASEDIR)/test
DOCDIR= $(BASEDIR)/docs
OBJ_EXT=o
TEST_EXT=cpp

SRCS=$(wildcard $(BASEDIR)/src/*.cc)
EXES=$(wildcard $(BASEDIR)/test/*.cpp)
OBJS=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(SRCS)))
BINS=$(subst $(TESTDIR), $(EXEDIR),$(subst .$(TEST_EXT),,$(EXES)))

all:  $(BINS)

docs: all
	doxygen Doxyfile
	$(MAKE) -C $(DOCDIR)/latex
	cp $(DOCDIR)/latex/refman.pdf $(DOCDIR)/$(LIBNAME)-CodeManual.pdf
	


$(EXEDIR)/%: $(TESTDIR)/%.cpp $(LIBDIR)/lib$(LIBNAME).so
	$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) -L$(LIBDIR) -l$(LIBNAME)

$(OBJDIR)/%.$(OBJ_EXT): $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -fPIC -c $<  -o $@

$(LIBDIR)/lib$(LIBNAME).so:$(OBJS)
	$(LD) $(LDFLAGS) -o $(LIBDIR)/lib$(LIBNAME).so  $^ $(LIBS)
	

lib: $(LIBDIR)/lib$(LIBNAME).so

vars:
	@echo "LIBS: " $(LIBS)
	@echo "CXXFLAGS: " $(CXXFLAGS)
	@echo "Source files: " $(SRCS) 
	@echo "Object files: " $(OBJS)
	@echo "Executables:  " $(TARGETS)

clean:
	rm -rf $(OBJS) $(LIBDIR)/lib$(LIBNAME).so $(EXEDIR)/* $(DOCDIR)/* 


