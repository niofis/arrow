#pragma once
#if defined(WIN32)
  #include <windows.h>
  #define THREAD DWORD __stdcall
  #define thread_run(f,p) CreateThread(NULL,0,f,p,0,NULL)
  #define thread_sleep(x) Sleep(x)
#else
  #include <pthread.h>
  //pthread_attr_t gomp_thread_attr;

  #define THREAD void*
  #define thread_run(fc,pc) {pthread_t  handle; pthread_create(&handle,0,fc,pc); pthread_detach( handle );}
  #define thread_sleep(x) usleep(x*1000)
#endif
