/*
 * File:   ring_buffer.h
 * Author: oliver
 *
 * Created on 15. Dezember 2020, 11:06
 */

#ifndef RING_BUFFER_H
#define	RING_BUFFER_H

#include <stdint.h>
#include <stddef.h>

/* Ring buffer descriptor */
typedef unsigned int rbd_t;

/* User defined ring buffer attributes */
typedef struct {
    size_t s_elem;
    size_t n_elem;
    void *buffer;
} rb_attr_t;

/**
 * \brief Initialize a ring buffer
 * \param[out] rbd - pointer to a ring buffer descriptor
 * \param[in] attr - ring buffer attributes
 * \return 0 on success, -1 otherwise
 *
 * The attributes must contain a ring buffer which is sized
 * to an even power of 2. This should be reflected by the
 * attribute n_elem.
 */
int ring_buffer_init(rbd_t *rbd, rb_attr_t *attr);

/**
 * \brief Flush a ring buffer
 * \param[out] rbd - pointer to a ring buffer descriptor
 * \param[in] idx - ring buffer index
 * \return 0 on success, -1 otherwise
 */
int ring_buffer_flush(int idx, rbd_t *rbd);
/**
 * \brief Add an element to the ring buffer
 * \param[in] rbd - the ring buffer descriptor
 * \param[in] data - the data to add
 * \return 0 on success, -1 otherwise
 */
int ring_buffer_put(rbd_t rbd, const void *data);

/**
 * \brief Get (and remove) an element from the ring buffer
 * \param[in] rbd - the ring buffer descriptor
 * \param[in] data - pointer to store the data
 * \return 0 on success, -1 otherwise
 */
int ring_buffer_get(rbd_t rbd, void *data);

#endif	/* RING_BUFFER_H */

