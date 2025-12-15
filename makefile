CXX      := g++
CXXFLAGS := -std=c++20 -O2 -march=native -Iinclude -Iexternal
LDFLAGS  := -Lexternal/GLAD/build
LDLIBS   := -lopengl32 -lgdi32 -lglad

TARGET   := build/main.exe
OBJDIR   := build

SRCS := \
	main.cpp \
	src/EngineCore/Buffer.cpp \
	src/Pipeline/Loader.cpp \
	src/EngineCore/Shader.cpp \
	src/EngineCore/Input.cpp \
	src/Pipeline/Renderer.cpp \
	src/Pipeline/Camera.cpp \
	src/EngineCore/TextureManager.cpp

OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

# -------------------------

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean
