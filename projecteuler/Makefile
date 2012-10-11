CPPUTEST_HOME := cpputest
COMPONENT_NAME := projectEuler
CPPUTEST_WARNINGFLAGS =  -Wall
#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

SRC_DIRS = src
TEST_SRC_DIRS = tst
	
INCLUDE_DIRS =\
  .\
  include\
  $(SRC_DIRS)\
  $(CPPUTEST_HOME)/include
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

$(CPPUTEST_LIB) :
	make -C $(CPPUTEST_HOME) all extensions
