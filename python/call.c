#include <Python.h>
#include <stdio.h>
#include <wchar.h>
#include <setjmp.h>

#define MODULE_NAME "mymodule"
#define FUNCTION_NAME "multiply"

int main(int argc, char *argv[])
{
  PyObject *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  wchar_t *paths;
  jmp_buf jb;
  int i;

  if (argc != 3)
  {
    fprintf(stderr, "usage: call param1 param2.\n");
    return 1;
  }

  Py_Initialize();
  if (!Py_IsInitialized())
  {
    fprintf(stderr, "Python was not initialized!\n");
    return 1;
  }

  paths = Py_GetPath();
  wprintf(L"Path: %s\n", paths);

  /* Finaliza, em caso de erro. */
  if (setjmp(jb))
  {
    Py_Finalize();
    return 1;
  }

  if ((pModule = PyImport_ImportModule(MODULE_NAME)) != NULL)
  {
    pFunc = PyObject_GetAttrString(pModule, FUNCTION_NAME);
    Py_DECREF(pModule);

    if (pFunc && PyCallable_Check(pFunc)) 
    {
      argv++;
      argc--;

      pArgs = PyTuple_New(argc);
      for (i = 0; i < argc; i++) 
      {
        if ((pValue = PyInt_FromLong(atoi(*argv++))) != NULL)
        {
          Py_DECREF(pArgs);
          Py_DECREF(pFunc);
          fprintf(stderr, "Cannot convert argument\n");
          longjmp(jb, 1);
        }

        /* pValue reference stolen here: */
        PyTuple_SetItem(pArgs, i, pValue);
      }

      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      Py_DECREF(pFunc);

      if (pValue != NULL) 
      {
        printf("Result of call: %ld\n", PyInt_AsLong(pValue));
        Py_DECREF(pValue);
      }
      else 
      {
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        longjmp(jb, 1);
      }
    }
    else 
    {
      if (PyErr_Occurred())
        PyErr_Print();

      fprintf(stderr, "Cannot find function \"" FUNCTION_NAME "\"\n");
    }

    Py_DECREF(pModule);
  }
  else 
  {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"" MODULE_NAME "\"\n");
    longjmp(jb, 1);
  }
  
  Py_Finalize();

  return 0;
}
