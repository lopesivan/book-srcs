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
  PyObject *sys, *path;
  wchar_t *paths;
  jmp_buf jb;
  int i;

  if (argc != 3)
  {
    fprintf(stderr, "usage: call num1 num2.\n");
    return 1;
  }

  /* Inicializa Python. */
  Py_Initialize();
  if (!Py_IsInitialized())
  {
    fprintf(stderr, "Python was not initialized!\n");
    return 1;
  }

  /* Isto é necessário para adicionar o diretório atual na lista sys.path */
  sys = PyImport_ImportModule("sys");
  path = PyObject_GetAttrString(sys, "path");
  PyList_Append(path, PyString_FromString("."));

  /* Finaliza, em caso de erro. */
  if (setjmp(jb))
  {
    Py_Finalize();
    return 1;
  }

  /* Carrega o módulo... */
  if ((pModule = PyImport_ImportModule(MODULE_NAME)) != NULL)
  {
    /* Obtem objeto relativo à função */
    pFunc = PyObject_GetAttrString(pModule, FUNCTION_NAME);

    /* Não precisamos mais do módulo. */
    Py_DECREF(pModule);

    if (pFunc != NULL && PyCallable_Check(pFunc)) 
    {
      argv++;

      /* Argumentos de funções são passados em tuplas. */
      pArgs = PyTuple_New(--argc);
      i = 0;
      while (*argv) 
      {
        if ((pValue = PyInt_FromLong(atoi(*argv++))) == NULL)
        {
          Py_DECREF(pArgs);
          Py_DECREF(pFunc);
          fprintf(stderr, "Cannot convert argument\n");
          longjmp(jb, 1);
        }

        /* DUVIDA: Como fica a contagem de referência dentro do loop? */

        PyTuple_SetItem(pArgs, i++, pValue);
      }

      pValue = PyObject_CallObject(pFunc, pArgs);
      /* DUVIDA: É preciso incrementar a referência aqui? */

      /* Nâo precisamos mais dos argumentos ou da função. */
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
