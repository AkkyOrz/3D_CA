KERNEL = $(shell uname -s)
ifeq ($(KERNEL),Linux)
	OS = $(shell uname -o)
endif

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
endif

CXXFLAGS = -Wall -Wextra -O3 -std=c++11
LDFLAGS = -lGL -lGLU -lglut

ifeq ($(OS), linux)
	LDFLAGS += -lGL -lGLU -lglut
else ifeq ($(OS), macos)
    LDFLAGS += -framework OpenGL -framework GLUT
endif

ifeq ($(openmp), yes)
	CXXFLAGS += -DUSE_OPENMP -DOPENMP_THREAD=$(openmp_cpus)
	LDFLAGS += -fopenmp
endif

ifeq ($(opencl), yes)
	CXXFLAGS += -DUSE_OPENCL
	ifeq ($(OS), linux)
    	LDFLAGS += -lOpenCL
	else
    	LDFLAGS += -framework OpenCL
	endif
endif

SRCS = src/3D_LifeGame.cpp src/OpenCL.cpp
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
