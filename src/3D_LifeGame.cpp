#include "config.h"
#include "opencl.h"
#include "opengl.h"

int main(int argc, char *argv[]){
  
#ifdef USE_OPENCL
  OpenCL::get().init();
#endif
  
  /* OpenGLの初期化 */
  init_GL(argc,argv);

  /* このプログラム特有の初期化 */
  init();

  /* コールバック関数の登録 */
  set_callback_functions();

  /* メインループ */
  glutMainLoop();

  return 0;
}

