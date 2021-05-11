#include <mulib/common.h>
#include <mulib/macros.h>

#include "reader.h"
#include <assert.h>

int
vec_push_char_in_str(vec_str_t *s, vec_char_t *c)
{
	if (vec_push(c, 0) != 0)
	{
		return -1;
	}

	if (vec_reserve(s, s->capacity + 1) != 0)
	{
		return -1;
	}

	s->data[s->length] = (char *)malloc(c->length);

	if (s->data[s->length] == NULL)
	{
		return -1;
	}

	strcpy(s->data[s->length], c->data);
	s->length++;

	UNUSED(vec_pop(c));

	return 0;
}

int
push_buffer_if_not_empty(vec_str_t *s, vec_char_t *c)
{
	if (c->length > 0)
	{
		if (vec_push_char_in_str(s, c) != 0)
		{
			return -1;
		}

		vec_clear(c);
	}

	return 0;
}

void
free_token_vec(vec_str_t *tokens)
{
	char *t;
	int i;

	vec_foreach(tokens, t, i) { free(t); }
}

vec_str_t
tokenize(const char *content)
{
	vec_str_t tokens;
	vec_char_t buffer;
	size_t i;

	vec_init(&tokens);
	vec_init(&buffer);

	for (i = 0; i < strlen(content); i++)
	{

		switch (content[i])
		{

			case '\r':
			case '\t':
			case '\f':
			case '\v':
			case '\n':
			case ' ':
			{
				assert(push_buffer_if_not_empty(&tokens, &buffer) == 0);
				break;
			}

			case '\'':
			case '#':
			{
				assert(push_buffer_if_not_empty(&tokens, &buffer) == 0);
				assert(vec_push(&buffer, content[i]) == 0);

				if (content[i + 1] == '(')
				{
					assert(vec_push(&buffer, '(') == 0);
					assert(vec_push_char_in_str(&tokens, &buffer) == 0);

					vec_clear(&buffer);
					i++;
				}

				break;
			}

			case ')':
			case '(':
			{
				assert(push_buffer_if_not_empty(&tokens, &buffer) == 0);
				assert(vec_push(&buffer, content[i]) == 0);
				assert(vec_push_char_in_str(&tokens, &buffer) == 0);

				vec_clear(&buffer);
				break;
			}

			case ';':
			{

				assert(vec_push(&buffer, content[i]) == 0);

				while (content[i++] != '\0' && content[i] != '\n')
				{
					assert(vec_push(&buffer, content[i]) == 0);
				}

				assert(vec_push_char_in_str(&tokens, &buffer) == 0);
				break;
			}
			default:
			{
				assert(vec_push(&buffer, content[i]) == 0);
				break;
			}
		}
	}

	vec_deinit(&buffer);
	return tokens;
}
