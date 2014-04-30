%feature("autodoc", "1");
%include "typemaps.i"
%include "carrays.i"
%include "cstring.i"
%include "stdint.i"

%module(docstring="Interface for libsdisp") sdisp
%{
#include "sdisp.h"
%}

%include "sdisp_config.h"
%include "sdisp.h"


//map for 
//int8_t sdisp_display__buffer_set_pixels(sdisp_t *ctx,uint16_t start, uint16_t len, uint8_t* color)
%typemap(in) (uint16_t len, uint8_t* color) {
	if (PyList_Check($input)) {
		int i=0;
		$1=PyList_Size($input);
		$2 = (uint8_t*) malloc(($1+1)*sizeof(uint8_t));
		//printf("creating uint16_t with size %i -> %i\n",$1,($1*sizeof(uint16_t)));
		for (i=0; i<$1;i++) {
			PyObject *o = PyList_GetItem($input,i);
			if (PyInt_Check(o)) {
				//printf("1\n");
				$2[i]=(uint8_t)PyInt_AsLong(PyList_GetItem($input,i));
			} else {
				PyErr_SetString(PyExc_TypeError,"list must contain integers");
				free($2);
				return NULL;
			}
			//printf("2\n");
		}
		//printf("3\n");
	} else {
		PyErr_SetString(PyExc_TypeError,"not a list");
		return NULL;
	}
	//printf("done...\n");
}
