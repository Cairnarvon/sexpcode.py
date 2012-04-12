#include <Python.h>
#include <stdlib.h>

#include "sexpcode/sexpcode.h"
#include "sexpcode/html.h"

sexpcode_func *(*get_func)(char*);

static PyObject*
sexpcode_sexpcode(PyObject *self, PyObject *args)
{
    const char *input, *output;

    if (!PyArg_ParseTuple(args, "s", &input))
        return NULL;

    get_func = &html_get_func;
    output = sexpcode(input);

    if (output != NULL)
        return Py_BuildValue("s", output);
    else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}

static PyMethodDef sexpcode_methods[] = {
    {"sexpcode", sexpcode_sexpcode, METH_VARARGS,
     "Converts SexpCode to HTML. Returns None on error."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initsexpcode(void)
{
        (void)Py_InitModule("sexpcode", sexpcode_methods);
}
