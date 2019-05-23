CXX = g++
CFLAGS= -Wall -std=c++11
TARGET=App
SRCDIR := Anlayze
OBJDIR := obj
INCLUDE := -I./Anlayze

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


all:$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
    $(CXX) $(CFLAGS) -c $< -o $@
    @echo "Compiled "$<" successfully!"

# $(BINDIR)/$(TARGET): $(OBJECTS)
$(TARGET): $(OBJECTS)
    $(CXX) $@ $(CFLAGS) $(OBJECTS)
    @echo "Linking complete!"

clean:
	rm $(SRCDIR)/*.o -rf

