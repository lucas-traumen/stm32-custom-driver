#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include "arm_math.h"

#define HSI_CLOCK_MHZ 16_000_000
#define HSI_CLOCK_ms  1600

#define HZ_5_SIG_LEN		   301
#define _1kHz_15kHz_SIG_LEN    320
#define IMPULSE_RESPOND_LEN	   29

extern float32_t g_in_sig_sample;
extern float32_t g_in_convolution_signal;
extern float32_t _5hz_signal[HZ_5_SIG_LEN];
extern float32_t inputSignal_f32_1kHz_15kHz[_1kHz_15kHz_SIG_LEN];
extern float32_t impulse_response[IMPULSE_RESPOND_LEN];

void pesudo_delay(int delaytime);
void plot_input_signal(void);
void serial_plot_signals(const char *fmt, ...);
void mean_signals(float32_t *pSrc,uint32_t siglen,float32_t *pRes);
void variance_sample_signals(float32_t *pSrc,uint32_t siglen,float32_t *pRes);
void standard_deviation_sample_signals(float32_t *pSrc,uint32_t siglen,float32_t *pRes);
void convolution_signals(float32_t *pSrc, float32_t *impulse_respond,float32_t *pRes,uint32_t Src_len,uint32_t imRes_len);
void running_sum(float32_t *pSrc,uint32_t Src_len,float32_t *pRes);
void running_sum_average(float32_t *pSrc,uint32_t Src_len,float32_t *pRes);

#endif


