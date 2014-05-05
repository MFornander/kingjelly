CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
SOURCES =   jellybrain.cpp $(wildcard src/*.cpp)
OBJS =		$(SOURCES:.cpp=.o)
TARGET =	jellybrain

all:	$(SOURCES) $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@



