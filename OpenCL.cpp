#include "OpenCL.h"
#include "config.h"

#ifdef USE_OPENCL 
#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>

#define grid_circle(id, grid_size)     \
        if (id < 0) {                  \
          id += grid_size);            \
        } else if (id >= grid_size) {  \
          id -= grid_size);            \
        }

        
int OpenCL::m_default_platform_id;
int OpenCL::m_default_device_id;
cl::Platform OpenCL::m_platform;
cl::Device   OpenCL::m_device;
cl::Context  OpenCL::m_context;
cl::Program  OpenCL::m_program;
cl::Kernel   OpenCL::m_iterator_cl;
cl::CommandQueue OpenCL::m_commandqueue;
cl::Buffer OpenCL::buffer_cell;
cl::Buffer OpenCL::buffer_cell_next;
size_t OpenCL::m_cl_buffer_size;


std::string OpenCL::m_clkernel = R"(
  __kernel void iterator
  (
    __global char * cell,
    __global char * cell_next
  )
  { 
    const int x_shift = get_global_size(0);
    const int y_shift = get_global_size(1);
    const int z_shift = get_global_size(2);
    const int xy_plane_shift = x_shift * y_shift;
   
    const int x = get_global_id(0);
    const int y = get_global_id(1);
    const int z = get_global_id(2);
    const int vertex = x + y*x_shift + z*xy_plane_shift;
    __private const char cell_state = cell[vertex];
    
    const char survive[23] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
    __private const char birth     =  4;

    int n = 0;
    int m = 0;
    int dx, dy, dz;
    for (dz = z-1; dz <= z+1; ++dz) {
      for (dy = y-1; dy <= y+1; ++dy) {
        for (dx = x-1; dx <= x+1; ++dx) {
          int ddx = dx;
          int ddy = dy;
          int ddz = dz;
          if (ddx < 0) {                  
            ddx += x_shift;         
          } else if (ddx >= x_shift) {
            ddx -= x_shift;            
          }
          if (ddy < 0) {                  
            ddy += y_shift;           
          } else if (ddy >= y_shift) {
            ddy -= y_shift;            
          }
          if (ddz < 0) {                  
            ddz += z_shift;           
          } else if (ddz >= z_shift) {
            ddz -= z_shift;            
          }
          
          const int dd_vertex = ddx + ddy*x_shift + ddz*xy_plane_shift;
          
          if (dd_vertex == vertex) {
            continue;
          }
          const char dd_cell_state = cell[dd_vertex];
          if (cell_state == 0) {
            if (dd_cell_state >= birth) {
              n++;
            }
          } else {
            if (dd_cell_state == (cell_state-1)) {
              n++;
            }
            if(dd_cell_state == cell_state) {
              m++;
            } 
          }
        }
      }
    }
    
    bool survive_bool = false;
    bool birth_bool   = false;
    int id;
    
    if (cell_state > 0) {
      for (id = 0; id < 23; ++id) {
        if (n == survive[id] || m == survive[id]) {
          survive_bool = true;
          break;
        }
      }
    } else if (cell_state == 0) {
      if (n == birth) {
        birth_bool = true;
      }
    }

    if (survive_bool) {
      cell_next[vertex] = cell_state - 1;
    } else if (birth_bool) {
      cell_next[vertex] = birth;
    } else {
      cell_next[vertex] = 0;
    }
    
  }

)";

void OpenCL::Init_OpenCL() {


  assert(sizeof(char) == sizeof(CELL_TYPE));
  assert(sizeof(survive)/sizeof(CELL_TYPE) == 23);
  assert(sizeof(birth)/sizeof(birth) == 1);
  assert(birth[0] == 4);
  assert(N_STATE == 5);

  m_default_platform_id = 0;
  m_default_device_id   = 0;
  std::vector<cl::Platform> platforms;
  std::vector<cl::Device>   devices;

  auto status = cl::Platform::get(&platforms);
  if (status != CL_SUCCESS) {
    printf("No OpenCL Platforms! \n");
    exit(0);
  }

  cl::Platform platform = platforms[m_default_platform_id];
  status = platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
  
  if (status != CL_SUCCESS) {
    printf("No OpenCL Devices at default platform! \n");
    exit(0);
  }

  m_platform = platform;
  m_device   = devices[m_default_device_id];
  print_gpu_info(m_device);
 
  m_context = cl::Context(m_device);
  m_program = cl::Program(m_context, m_clkernel);
  
  if (m_program.build({m_device}) != CL_SUCCESS){
    printf("Building fail! \n");
    exit(0);
  }

  m_iterator_cl  = cl::Kernel(m_program, "iterator");
  m_commandqueue = cl::CommandQueue(m_context, m_device);

  m_cl_buffer_size = GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z *sizeof(CELL_TYPE);
  buffer_cell= cl::Buffer(m_context, CL_MEM_READ_WRITE, m_cl_buffer_size);
  buffer_cell_next = cl::Buffer(m_context, CL_MEM_READ_WRITE, m_cl_buffer_size);

  m_iterator_cl.setArg(0, buffer_cell);
  m_iterator_cl.setArg(1, buffer_cell_next);
}

void OpenCL::update_cells(CELL_TYPE* cell_ptr) {
    
	m_commandqueue.enqueueWriteBuffer(buffer_cell, CL_FALSE, 0, m_cl_buffer_size, cell_ptr);
	
	m_commandqueue.enqueueNDRangeKernel(m_iterator_cl, cl::NullRange,
                                   cl::NDRange(GRID_SIZE_X, GRID_SIZE_Y, GRID_SIZE_Z),
                                   cl::NullRange);
	m_commandqueue.enqueueReadBuffer(buffer_cell_next, CL_FALSE, 0, m_cl_buffer_size, cell_ptr);
}

void OpenCL::print_gpu_info(cl::Device& device){
  int id = m_default_device_id;
  printf("Device ID:     %d\n", id);
  printf("Device name:   %s\n",
             device.getInfo<CL_DEVICE_NAME>().c_str());
  printf("Device vendor: %s\n",
              device.getInfo<CL_DEVICE_VENDOR>().c_str());
  printf("Device driver: %s\n",
              device.getInfo<CL_DRIVER_VERSION>().c_str());
  printf("Device speed:  %u MHz\n",
              device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>());
  printf("Device cores:  %u CU\n",
              device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>());
}


#endif
