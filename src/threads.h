#pragma once
#if defined(WIN32)
  #include <windows.h>
  #define THREAD DWORD __stdcall
  #define thread HANDLE
  #define thread_run(handle, f, p) *handle = CreateThread(NULL,0,f,p,0,NULL)
  #define thread_sleep(x) Sleep(x)
  #define thread_join(thrd) WaitForSingleObject(thrd, INFINITE)
#else
  #include <pthread.h>
  //pthread_attr_t gomp_thread_attr;

  #define THREAD void*
  #define thread pthread_t
  #define thread_run(handle, f, p) pthread_create(handle,0,f,p);
  #define thread_sleep(x) usleep(x*1000)
  #define thread_join(thrd) pthread_join(thrd, NULL)
#endif
//Example:
//thread yep;
//thread_run(&yep, func, params);
//thread_join(yep);