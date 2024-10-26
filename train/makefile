CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = main
SRCS = main.cpp game.cpp agent.cpp
HEADERS = game.h agent.h macro.h
OBJDIR = ./obj
OBJS = $(patsubst %.cpp,$(OBJDIR)/%lo,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

.PHONY: all clean