#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL Java_HelloWorld_showMessage(JNIEnv *env, jclass obj)
{
  puts("Hello, World!\n");
}

