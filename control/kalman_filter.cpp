
#include "stdAfx.h"

#include <stdint.h>
#include "kalman_filter.h"

float Qingjiao = 0, Qingjiao_Pre, Acc_Qingjiao = 0, Gyro_Qingjiao = 0, Gyro_out = 0;
int32_t Gyro_out_SC = 0; int16_t Acc_Qingjiao_SC, Qingjiao_SC;
float Acc_x = 0, Acc_z = 0, Gyro = 0;

float P[2][2] =
{
	{ 1, 0 },
	{ 0, 1 }
};

char  C_0 = 1;
float E;
float q_bias;
float Angle_err;
float PCt_0, PCt_1;
float K_0, K_1;
float t_0, t_1;
float Pdot[4] = { 0, 0, 0, 0 };

float Q_angle = 0.060, Q_gyro = 0.006, R_angle = 3, dt = 0.0180; //dt��ȡֵΪkalman�˲�������ʱ��;

float KalmanFilterMPU(float angle_m, float gyro_m)
{
	Qingjiao += gyro_m;    //�������
	//���¾�Ϊ�������㷨����	
	Pdot[0] = Q_angle - P[0][1] - P[1][0];// Pk-' ����������Э�����΢��
	Pdot[1] = -P[1][1];
	Pdot[2] = -P[1][1];
	Pdot[3] = Q_gyro;

	P[0][0] += Pdot[0] * dt;        // Pk- ����������Э����΢�ֵĻ��� = ����������Э����
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;

	Angle_err = angle_m - Qingjiao;    //zk-�������	

	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];

	E = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / E;                //Kk
	K_1 = PCt_1 / E;

	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];

	P[0][0] -= K_0 * t_0;           //����������Э����
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;

	Qingjiao += K_0 * Angle_err;       //�������	    //�˴�Ϊ�Ƕ�ֵ
	q_bias += K_1 * Angle_err;       //�������       //���˾������λ�þ�����ƫ��ĵط�
	Gyro_out = gyro_m - q_bias;      //���ֵ��������ƣ���΢�� = ���ٶ�   //�˴�Ϊ���ٶ�ֵ
	return Qingjiao;

}

/*
* @brief
*   Init fields of structure @kalman1_state.
*   I make some defaults in this init function:
*     A = 1;
*     H = 1;
*   and @q,@r are valued after prior tests.
*
*   NOTES: Please change A,H,q,r according to your application.
*
* @inputs
*   state - Klaman filter structure
*   init_x - initial x state value
*   init_p - initial estimated error convariance
* @outputs
* @retval
*/
void kalman1_init(kalman1_state *state, float init_x, float init_p)
{
	state->x = init_x;
	state->p = init_p;
	state->A = 1;
	state->H = 1;
	state->q = 2e2;//10e-6;  /* predict noise convariance */
	state->r = 5e2;//10e-5;  /* measure error convariance */
}

/*
* @brief
*   1 Dimension Kalman filter
* @inputs
*   state - Klaman filter structure
*   z_measure - Measure value
* @outputs
* @retval
*   Estimated result
*/
float kalman1_filter(kalman1_state *state, float z_measure)
{
	/* Predict */
	state->x = state->A * state->x;
	state->p = state->A * state->A * state->p + state->q;  /* p(n|n-1)=A^2*p(n-1|n-1)+q */

	/* Measurement */
	state->gain = state->p * state->H / (state->p * state->H * state->H + state->r);
	state->x = state->x + state->gain * (z_measure - state->H * state->x);
	state->p = (1 - state->gain * state->H) * state->p;

	return state->x;
}

/*
* @brief
*   Init fields of structure @kalman1_state.
*   I make some defaults in this init function:
*     A = {{1, 0.1}, {0, 1}};
*     H = {1,0};
*   and @q,@r are valued after prior tests.
*
*   NOTES: Please change A,H,q,r according to your application.
*
* @inputs
* @outputs
* @retval
*/
void kalman2_init(kalman2_state *state, float *init_x, float(*init_p)[2])
{
	state->x[0] = init_x[0];
	state->x[1] = init_x[1];
	state->p[0][0] = init_p[0][0];
	state->p[0][1] = init_p[0][1];
	state->p[1][0] = init_p[1][0];
	state->p[1][1] = init_p[1][1];
	//state->A       = {{1, 0.1}, {0, 1}};
	state->A[0][0] = 1;
	state->A[0][1] = 0.1;
	state->A[1][0] = 0;
	state->A[1][1] = 1;
	//state->H       = {1,0};
	state->H[0] = 1;
	state->H[1] = 0;
	//state->q       = {{10e-6,0}, {0,10e-6}};  /* measure noise convariance */
	state->q[0] = 10e-7;
	state->q[1] = 10e-7;
	state->r = 10e-7;  /* estimated error convariance */
}

/*
* @brief
*   2 Dimension kalman filter
* @inputs
*   state - Klaman filter structure
*   z_measure - Measure value
* @outputs
*   state->x[0] - Updated state value, Such as angle,velocity
*   state->x[1] - Updated state value, Such as diffrence angle, acceleration
*   state->p    - Updated estimated error convatiance matrix
* @retval
*   Return value is equals to state->x[0], so maybe angle or velocity.
*/
float kalman2_filter(kalman2_state *state, float z_measure)
{
	float temp0 = 0.0f;
	float temp1 = 0.0f;
	float temp = 0.0f;

	/* Step1: Predict */
	state->x[0] = state->A[0][0] * state->x[0] + state->A[0][1] * state->x[1];
	state->x[1] = state->A[1][0] * state->x[0] + state->A[1][1] * state->x[1];
	/* p(n|n-1)=A^2*p(n-1|n-1)+q */
	state->p[0][0] = state->A[0][0] * state->p[0][0] + state->A[0][1] * state->p[1][0] + state->q[0];
	state->p[0][1] = state->A[0][0] * state->p[0][1] + state->A[1][1] * state->p[1][1];
	state->p[1][0] = state->A[1][0] * state->p[0][0] + state->A[0][1] * state->p[1][0];
	state->p[1][1] = state->A[1][0] * state->p[0][1] + state->A[1][1] * state->p[1][1] + state->q[1];

	/* Step2: Measurement */
	/* gain = p * H^T * [r + H * p * H^T]^(-1), H^T means transpose. */
	temp0 = state->p[0][0] * state->H[0] + state->p[0][1] * state->H[1];
	temp1 = state->p[1][0] * state->H[0] + state->p[1][1] * state->H[1];
	temp = state->r + state->H[0] * temp0 + state->H[1] * temp1;
	state->gain[0] = temp0 / temp;
	state->gain[1] = temp1 / temp;
	/* x(n|n) = x(n|n-1) + gain(n) * [z_measure - H(n)*x(n|n-1)]*/
	temp = state->H[0] * state->x[0] + state->H[1] * state->x[1];
	state->x[0] = state->x[0] + state->gain[0] * (z_measure - temp);
	state->x[1] = state->x[1] + state->gain[1] * (z_measure - temp);

	/* Update @p: p(n|n) = [I - gain * H] * p(n|n-1) */
	state->p[0][0] = (1 - state->gain[0] * state->H[0]) * state->p[0][0];
	state->p[0][1] = (1 - state->gain[0] * state->H[1]) * state->p[0][1];
	state->p[1][0] = (1 - state->gain[1] * state->H[0]) * state->p[1][0];
	state->p[1][1] = (1 - state->gain[1] * state->H[1]) * state->p[1][1];

	return state->x[0];
}