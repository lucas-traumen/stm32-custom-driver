/*
 * ecg.h
 *
 *  Created on: Jul 10, 2026
 *      Author: lucas
 */

#ifndef _ECG_H_
#define _ECG_H_

#include "arm_math.h"
#include <stdbool.h>
#include <stdint.h>

#define ECG_FS_HZ      360U
#define ECG_SIGNAL_LEN 512U
#define DFT_N       ECG_SIGNAL_LEN
#define DFT_BINS    ((DFT_N / 2U) + 1U)
#define TWO_PI_F 6.28318530717958647692f
/*
 * Real ECG excerpt:
 * Dataset : MIT-BIH Arrhythmia Database
 * Record  : 100
 * Channel : MLII
 * Samples : first 512 samples
 * Unit    : mV
 * Duration: 1.422222 seconds
 *
 * Intended for DSP learning and algorithm testing, not clinical use.
 */



extern float32_t ecg_signal[ECG_SIGNAL_LEN];
bool dft_real_one_sided_f32(const float32_t *pSrc,uint32_t src_len,float32_t *pReal,float32_t *pImag,float32_t *pMagnitude,uint32_t output_capacity);




#endif /* DAY2_ECG_H_ */
