#include <Python.h>
#include <iostream>
#include <string>
#include <windows.h>

void UTF8ToGBK(const char* strUTF8, char* iNeed)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    strcpy(iNeed, szGBK);

	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;

}

void cpp_get_python_output( char* iSay ) 
{
    Py_Initialize();
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyRun_SimpleString("import sys");

    pModule = PyImport_ImportModule("get_saying");
    pFunc = PyObject_GetAttrString(pModule, "ISay");
    PyObject* pReturn = PyObject_CallObject(pFunc, NULL);

    char *ss = NULL;
    PyArg_Parse(pReturn, "s", &ss);

    UTF8ToGBK(ss, iSay);
    Py_Finalize();
}
