SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
	DEPS=$(SOURCES:.cc=.d)
BINS=precedence_climb

CFLAGS+=-MMD
CXXFLAGS+=-MMD 
LDFLAGS+=-lstdc++

all: $(BINS)

precedence_climb: $(OBJECTS)

.PHONY: clean

clean:
	    $(RM) $(OBJECTS) $(DEPS) $(BINS)

-include $(DEPS)
