CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		jellybrain.o

LIBS =

TARGET =	jellybrain

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
