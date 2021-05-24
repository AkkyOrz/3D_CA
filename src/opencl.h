#ifndef _OPENCL_H_
#define _OPENCL_H_

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
  static void Init_OpenCL();
  static void print_gpu_info(cl::Device&);
  static void update_cells(CELL_TYPE* cell_ptr);
static std::string m_clkernel;
private:
  

  static int m_default_platform_id;
  static int m_default_device_id;
  static cl::Platform m_platform;
  static cl::Device   m_device;
  static cl::Context  m_context;
  static cl::Program  m_program;
  static cl::Kernel   m_iterator_cl;
  static cl::CommandQueue m_commandqueue;
  static cl::Buffer buffer_cell;
  static cl::Buffer buffer_cell_next;
  static size_t m_cl_buffer_size;

};


#endif
#endif
