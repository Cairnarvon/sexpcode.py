#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

#include "sexpcode/sexpcode.h"
#include "sexpcode/html.h"

sexpcode_func *(*get_func)(char*);

static PyObject *SexpCodeException;

static PyObject*
sexpcode_sexpcode(PyObject *self, PyObject *args)
{
    const char *input, *output;
    char err[256];
    FILE *stderr_tmp = stderr;

    if (!PyArg_ParseTuple(args, "s", &input))
        return NULL;

    get_func = &html_get_func;
    stderr = tmpfile();
    output = sexpcode(input);

    if (output != NULL) {
        fclose(stderr);
        stderr = stderr_tmp;

        return Py_BuildValue("s", output);
    } else {
        int i;

        rewind(stderr);
        i = fread(err, 1, 255, stderr);
        err[i - 1] = 0;
        fclose(stderr);
        stderr = stderr_tmp;

        PyErr_SetString(SexpCodeException, err);
        return NULL;
    }
}

static PyMethodDef sexpcode_methods[] = {
    {"sexpcode", sexpcode_sexpcode, METH_VARARGS,
     "Converts SexpCode to HTML. Raises SexpCodeException on error."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initsexpcode(void)
{
    PyObject *m;

    m = Py_InitModule("sexpcode", sexpcode_methods);
    if (m == NULL)
        return;

    SexpCodeException = PyErr_NewException("sexpcode.SexpCodeException", NULL, NULL);
    Py_INCREF(SexpCodeException);
    PyModule_AddObject(m, "SexpCodeException", SexpCodeException);
}
