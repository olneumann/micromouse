/*
 * File:   ring_buffer.c
 * Author: oliver
 *
 * Created on 15. Dezember 2020, 11:06
 */

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "ring_buffer.h"

#define RING_BUFFER_MAX  1

struct ring_buffer
{
    size_t s_elem;
    size_t n_elem;
    uint8_t *buf;
    volatile size_t head;
    volatile size_t tail;
};

static struct ring_buffer _rb[RING_BUFFER_MAX];

static int _ring_buffer_full(struct ring_buffer *rb);
static int _ring_buffer_empty(struct ring_buffer *rb);

int ring_buffer_init(rbd_t *rbd, rb_attr_t *attr)
{
    static int idx = 0;
    int err = -1;

    if ((idx < RING_BUFFER_MAX) && (rbd != NULL) && (attr != NULL)) {
        if ((attr->buffer != NULL) && (attr->s_elem > 0)) {
            /* Check that the size of the ring buffer is a power of 2 */
            if (((attr->n_elem - 1) & attr->n_elem) == 0) {
                /* Initialize the ring buffer internal variables */
                _rb[idx].head = 0;
                _rb[idx].tail = 0;
                _rb[idx].buf = attr->buffer;
                _rb[idx].s_elem = attr->s_elem;
                _rb[idx].n_elem = attr->n_elem;

                *rbd = idx++;
                err = 0;
            } 
        }
    }

    return err;
}

int ring_buffer_flush(int idx, rbd_t *rbd)
{
    int err = -1;

    if ((idx < RING_BUFFER_MAX) && (rbd != NULL)) {
        /* Reset the ring buffer internal variables */
        _rb[idx].head = 0;
        _rb[idx].tail = 0;

        err = 0;
    }

    return err;
}

int ring_buffer_put(rbd_t rbd, const void *data)
{
    int err = 0;

    if ((rbd < RING_BUFFER_MAX) && (_ring_buffer_full(&_rb[rbd]) == 0)) {
        const size_t offset = (_rb[rbd].head & (_rb[rbd].n_elem - 1)) * _rb[rbd].s_elem;
        memcpy(&(_rb[rbd].buf[offset]), data, _rb[rbd].s_elem);
        _rb[rbd].head++;
    } else {
        err = -1;
    }

    return err;
}

int ring_buffer_get(rbd_t rbd, void *data)
{
    int err = 0;

    if ((rbd < RING_BUFFER_MAX) && (_ring_buffer_empty(&_rb[rbd]) == 0)) {
        const size_t offset = (_rb[rbd].tail & (_rb[rbd].n_elem - 1)) * _rb[rbd].s_elem;
        memcpy(data, &(_rb[rbd].buf[offset]), _rb[rbd].s_elem);
        _rb[rbd].tail++;
    } else {
        err = -1;
    }

    return err;
}

static int _ring_buffer_full(struct ring_buffer *rb)
{
    return ((rb->head - rb->tail) == rb->n_elem) ? 1 : 0;
}

static int _ring_buffer_empty(struct ring_buffer *rb)
{
    return ((rb->head - rb->tail) == 0U) ? 1 : 0;
}
