#include <Python.h>
#include <iostream>
#include <string>
#include <windows.h>

void cpp_get_python_output() 
{
    SetConsoleOutputCP(65001);

    Py_Initialize();
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyRun_SimpleString("import sys");

    pModule = PyImport_ImportModule("get_saying");
    pFunc = PyObject_GetAttrString(pModule, "ISay");
    PyObject* pReturn = PyEval_CallObject(pFunc, NULL);

    char* iSay = NULL;
    PyArg_Parse(pReturn, "s", &iSay);


    std::cout << iSay << "\n";

    Py_Finalize();
}