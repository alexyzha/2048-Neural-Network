CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = server
SRCS = server.cpp agent.cpp
HEADERS = agent.h macro.h
OBJDIR = ./obj
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

.PHONY: all clean