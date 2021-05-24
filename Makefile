OS = $(shell uname -s)

ifeq ($(NAME),)
	NAME = 3D_LifeGame
endif

ifeq ($(COMP),)
	COMP=gcc
	CXX=g++
endif

ifeq ($(COMP),gcc)
	COMP=gcc
	CXX=g++
endif

ifeq ($(COMP),clang)
	COMP=clang
	CXX=clang++
endif

opencl = no
openmp = no
openmp_cpus = 4

ifeq ($(ACC), mp)
	openmp = yes
else ifeq ($(ACC), cl)
	opencl = yes
endif

ifeq ($(CPUS),)
	openmp_cpus = 4
else 
	openmp_cpus = $(CPUS)
endif

CXXFLAGS = -Wall -Wextra -O3 -std=c++11

ifeq ($(OS), Linux)
	LDFLAGS += -lGL -lGLU -lglut
else ifeq ($(OS), Darwin)
	LDFLAGS += -framework OpenGL -framework GLUT
endif

ifeq ($(openmp), yes)
	CXXFLAGS += -DUSE_OPENMP -DOPENMP_THREAD=$(openmp_cpus)
	LDFLAGS += -fopenmp
endif

ifeq ($(opencl), yes)
	CXXFLAGS += -DUSE_OPENCL
	ifeq ($(OS), Linux)
		LDFLAGS += -lOpenCL
	else ifeq ($(OS), Darwin)
		LDFLAGS += -framework OpenCL
	endif
endif

SRCS = src/3D_LifeGame.cpp src/opencl.cpp src/opengl.cpp
FLAGS = $(CXXFLAGS) $(LDFLAGS)

release:
	$(CXX) $(SRCS) -o $(NAME) $(FLAGS) -DNDEBUG

debug:
	$(CXX) $(SRCS) -o $(NAME) $(FLAGS) -g

clean:
	rm -r $(NAME)

help:
	@echo "make target [COMP=compiler] [ACC=accelerator] [CPUS=threads]"
	@echo ""
	@echo "target"
	@echo "  release, debug, clean"
	@echo ""
	@echo "options"
	@echo "  COMP  = gcc(default), clang"
	@echo "  ACC   = mp, cl"
	@echo "  CPUS  = 1, 2, 3, 4(default), ...."
