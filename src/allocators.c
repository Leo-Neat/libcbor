#include "cbor.h"

_cbor_malloc_t _cbor_malloc = malloc;
_cbor_realloc_t _cbor_realloc = realloc;
_cbor_free_t _cbor_free = free;

void cbor_set_allocs(_cbor_malloc_t custom_malloc, _cbor_realloc_t custom_realloc, _cbor_free_t custom_free)
{
	_cbor_malloc = custom_malloc;
	_cbor_realloc = custom_realloc;
	_cbor_free = custom_free;
}