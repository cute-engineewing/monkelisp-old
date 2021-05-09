#ifndef _MONKELISP_READER_H
#define _MONKELISP_READER_H

#include <mulib/vec.h>

int vec_push_char_in_str(vec_str_t *, vec_char_t *);
int push_buffer_if_not_empty(vec_str_t *, vec_char_t *);

void free_token_vec(vec_str_t *);
vec_str_t tokenize(const char *);

#endif /* !_MONKELISP_READER_H */