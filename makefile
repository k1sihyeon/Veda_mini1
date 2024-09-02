DEPEND_FILE = depend_file

CC = g++
CXXFLAGS = -std=c++17 -Wall \
           -Isrc/customer \
           -Isrc/order \
           -Isrc/product \
           -Isrc/shopping \
           -Iheader

BUILD_DIR = build

SRCS = $(wildcard \
    src/customer/*.cpp \
    src/order/*.cpp \
    src/product/*.cpp \
    src/shopping/*.cpp \
    src/main.cpp)

OBJS = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = app.out

LIB_DIR = lib
LIBS = -L$(LIB_DIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c -o $@ $<

depend:
	$(CC) $(CXXFLAGS) -MM $(SRCS) > $(DEPEND_FILE)

clean:
	rm -f $(OBJS) $(TARGET) $(DEPEND_FILE)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(SRCS),)
-include $(DEPEND_FILE)
endif
endif
endif

