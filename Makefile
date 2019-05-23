CXX = g++
CFLAGS = -Wall -std=c++11
TARGET = App
SRCDIR = ./Analyze/
OBJDIR := obj
INCLUDE := -I.

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
# INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJS := $(patsubst %cpp,%o,$(SOURCES))

#$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
%.o:$(SRCDIR)%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
	# @echo "Compiled "$<" successfully!"

# $(BINDIR)/$(TARGET): $(OBJECTS)
#$(TARGET): $(OBJECTS)
#    $(CXX) $@ $(CFLAGS) $(OBJECTS)
    #@echo "Linking complete!"

.PHONY: clean
clean:
	rm *.o -rf

