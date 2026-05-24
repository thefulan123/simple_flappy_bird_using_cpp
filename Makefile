CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++11
LDFLAGS   := -lSDL2

SRCDIR    := src
BUILDDIR  := build
TARGET    := flappy_bird
TARGET_WIN:= flappy_bird.exe

SOURCES   := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS   := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Linux/Unix static build
CXXFLAGS_STATIC := -Wall -Wextra -std=c++11
LDFLAGS_STATIC  := -lSDL2 -static-libgcc -static-libstdc++

all: $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Static build (standalone Linux binary)
static: CXXFLAGS = $(CXXFLAGS_STATIC)
static: LDFLAGS = $(LDFLAGS_STATIC)
static: clean $(TARGET)

# Windows cross-compilation via MinGW
win: $(TARGET_WIN)

$(TARGET_WIN):
	@echo "Building for Windows... (requires MinGW-w64 + SDL2-MinGW)"
	@echo "See build_windows.bat for details or run: build_windows.bat"
	@echo ""
	@cmd.exe /c "build_windows.bat" 2>/dev/null && echo "OK" || echo "Not on Windows; use build_windows.bat manually"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TARGET_WIN)

.PHONY: all static win run clean
