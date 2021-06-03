#include "m_pd.h"

t_class *memorex_class;

typedef struct memorex {
  t_object x_obj;
  t_inlet *in_replay, *in_size;
  t_outlet *out_series;
  int size, *array, index, count;
  int fifo, replay;
} t_memorex;

void memorex_freeArray (t_memorex *x) {
  if (x->size) {
    freebytes(x->array, x->size * sizeof(int));
    x->size = 0;
  }
}

void memorex_size (t_memorex *x, t_floatarg f) {
  memorex_freeArray(x);
  x->size = (int)f;
  if (x->size >= 0) x->fifo = 1;
  else {
    x->size = -x->size;
    x->fifo = 0;
  }
  if (x->size) x->array = (int *)getbytes(x->size * sizeof(int));
  x->index = -1;
  x->count = 0;
}

void memorex_number (t_memorex *x, t_floatarg f) {
  if (!x->size) return;
  if (x->replay) {
    if (!x->count) return;
    if (x->fifo) {
      if (++x->index == x->count) x->index = 0;
      outlet_float(x->out_series, (float)x->array[x->index]);
    }
    else {
      outlet_float(x->out_series, (float)x->array[x->index]);
      if (--x->index == -1) x->index = x->count - 1;
    }
  }
  else {
    outlet_float(x->out_series, (int)f);
    if (++x->index == x->size) x->index = 0;
    if (x->index == x->count && x->count < x->size) ++x->count;
    x->array[x->index] = (int)f;
  }
}

void memorex_replay (t_memorex *x, t_floatarg f) {
  if (f == 0) x->replay = 0;
  else x->replay = 1;
}

void *memorex_new (t_floatarg f) {
  t_memorex *x = (t_memorex *)pd_new(memorex_class);
  // leftmost inlet automatically created (and freed)
  x->in_replay = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("replay"));
  x->in_size = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("size"));
  x->out_series = outlet_new(&x->x_obj, &s_float);
  x->size = 0;
  memorex_size(x, f);
  x->replay = 0;
  return (void *)x;
}

void memorex_free(t_memorex *x) {
  memorex_freeArray(x);
  inlet_free(x->in_replay);
  inlet_free(x->in_size);
  outlet_free(x->out_series);
}

void memorex_setup(void) {
  memorex_class = class_new(gensym("memorex"), (t_newmethod)memorex_new, (t_method)memorex_free,
    sizeof(t_memorex), CLASS_DEFAULT, A_DEFFLOAT, 0);
  class_addfloat(memorex_class, (t_method)memorex_number);
  class_addmethod(memorex_class, (t_method)memorex_number, gensym("number"), A_DEFFLOAT, 0);
  class_addmethod(memorex_class, (t_method)memorex_replay, gensym("replay"), A_DEFFLOAT, 0);
  class_addmethod(memorex_class, (t_method)memorex_size, gensym("size"), A_DEFFLOAT, 0);
}
