#pragma once

#include "config.h"
#ifdef USE_OPENCL

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <string>
 
class OpenCL {
public:
  static OpenCL& get();

  void init();
  void update_cells(CELL_TYPE* cell_ptr);

private:
  void print_gpu_info(cl::Device&);

  static std::string m_clkernel;

  int m_default_platform_id;
  int m_default_device_id;

  cl::Platform m_platform;
  cl::Device   m_device;
  cl::Context  m_context;
  cl::Program  m_program;
  cl::Kernel   m_iterator_cl;

  cl::CommandQueue m_commandqueue;
  cl::Buffer buffer_cell;
  cl::Buffer buffer_cell_next;

  size_t m_cl_buffer_size;
};

#endif
