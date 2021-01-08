/* 
 * File:   dma.h
 * Author: oliver
 *
 * Created on 18. Dezember 2020, 20:03
 */

#ifndef DMA_H
#define	DMA_H

extern unsigned int dma_bufA[32]__attribute__((space(dma)));

void dmaInit(void);

#define SENSOR_1 dma_bufA[0]
#define SENSOR_2 dma_bufA[1]
#define SENSOR_3 dma_bufA[2]

#endif	/* DMA_H */

