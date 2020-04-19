Compile_Clang : 3D_LifeGame.cpp
	clang++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut
Compile_Clang_MP : 3D_LifeGame.cpp
	clang++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -fopenmp -DUSE_OPENMP -DOPENMP_THREAD=4
Compile_Clang_CL : 3D_LifeGame.cpp
	clang++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -lOpenCL -DUSE_OPENCL
Compile_Gnugcc : 3D_LifeGame.cpp
	g++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut
Compile_Gnugcc_MP : 3D_LifeGame.cpp
	g++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -fopenmp -DUSE_OPENMP -DOPENMP_THREAD=4
Compile_Gnugcc_CL : 3D_LifeGame.cpp
	g++ 3D_LifeGame.cpp OpenCL.cpp -std=c++11 -o 3D_LifeGame -O3 -lGL -lGLU -lglut -lOpenCL -DUSE_OPENCL

