#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include "webp/render.h"
#include "examples/unicode.h"
#include "examples/example_util.h"
#include "data/data_holder.h"
#include "zstr.hpp"

std::string decompress(std::istream& inputFile) {
    zstr::istream zs(inputFile);
    return std::string(std::istreambuf_iterator<char>(zs), std::istreambuf_iterator<char>());
}

bool convert(const std::string& filePath, const std::string& output, bool is_tray) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr<<"Could not open file "<<filePath<<std::endl;
        return -1;
    }

    const std::string decompressed = decompress(inputFile);
    
    inputFile.close();

    return render(decompressed, output, is_tray);
}


int task(std::string input, std::string output, int wh, int m, float q, bool is_tray) {
    bool min_size = false;
    if (is_tray){
        wh = 96;
    }
    DataHolder data(q, m, min_size, wh, wh);
    return convert(input, output, is_tray);
}

static PyObject* tgs_convert(PyObject* self, PyObject *args) {
    const char *a, *b;
    int wh = 512, m = 0;
    float q = 0;
    bool is_tray = false;
    PyArg_ParseTuple(args, "ssiifb", &a, &b, &wh, &m, &q, &is_tray);
    return PyBool_FromLong(task(a, b, wh, m, q, is_tray));
};

static PyMethodDef tgs_methods[] = {
	{"convert", tgs_convert, METH_VARARGS, "Convert tgs to webp"},
	{nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef tgsmodule = {
    PyModuleDef_HEAD_INIT,
    "tgs",   /* name of module */
    nullptr, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    tgs_methods
};

PyMODINIT_FUNC PyInit_tgs(void)
{
    return PyModule_Create(&tgsmodule);
};
