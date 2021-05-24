Compile_Clang:
	clang++ src/*.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut
Compile_Clang_MP:
	clang++ src/*.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -fopenmp -DUSE_OPENMP -DOPENMP_THREAD=4
Compile_Clang_CL:
	clang++ src/*.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -lOpenCL -DUSE_OPENCL
Compile_Gnugcc:
	g++ src/*.cpp-std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut
Compile_Gnugcc_MP:
	g++ src/*.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -fopenmp -DUSE_OPENMP -DOPENMP_THREAD=4
Compile_Gnugcc_CL:
	g++ src/*.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -lOpenCL -DUSE_OPENCL

