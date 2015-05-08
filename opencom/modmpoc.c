/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 EcmaXp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "py/nlr.h"
#include "py/runtime.h"
#include "py/objtuple.h"

STATIC mp_obj_t mod_mpoc_pause(mp_obj_t self_in, mp_uint_t n_args, mp_uint_t n_kw, const mp_obj_t *args) {
#if MICROPY_ALLOW_PAUSE_VM
    return MP_OBJ_PAUSE_VM;
#else
    // TODO: raise exception
    nlr_raise(MP_OBJ_NULL);
    return mp_const_none;
#endif
    
}

typedef struct _mp_type_fun_special_t {
    mp_obj_base_t base;
} mp_type_fun_special_t;

const mp_obj_type_t mp_type_fun_special = {
    { &mp_type_type },
    .name = MP_QSTR_function,
    .call = mod_mpoc_pause,
};

STATIC const mp_type_fun_special_t mod_mpoc_pause_obj = {{&mp_type_fun_special}};


STATIC mp_obj_t mod_mpoc_test(mp_obj_t asdf) {
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_mpoc_test_obj, mod_mpoc_test);

/* STATIC mp_obj_t mod_mpoc_pause() {
    printf("hello BY\n");
    nlr_raise((mp_obj_t)&mp_const_VMPauseSignal_obj);
    return mp_const_none;
} */

// STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_mpoc_pause_obj, mod_mpoc_pause);

STATIC const mp_map_elem_t mp_module_mpoc_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_mpoc) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_test), (mp_obj_t)&mod_mpoc_test_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pause), (mp_obj_t)&mod_mpoc_pause_obj },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_mpoc_globals, mp_module_mpoc_globals_table);

const mp_obj_module_t mp_module_mpoc = {
    .base = { &mp_type_module },
    .name = MP_QSTR_mpoc,
    .globals = (mp_obj_dict_t*)&mp_module_mpoc_globals,
};