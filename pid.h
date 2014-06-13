#ifndef PID_H_
#define PID_H_

typedef struct pid_filter_s pid_filter_t;

/** Allocates the memory for a PID filter. */
pid_filter_t *pid_create(void);

/** Frees the memory used by a PID filter. */
void pid_delete(pid_filter_t *pid);

/** Sets the gains of the given PID. */
void pid_set_gains(pid_filter_t *pid, float kp, float ki, float kd);

/** Returns the proportional gain of the controller. */
float pid_get_kp(const pid_filter_t *pid);

/** Returns the integral gain of the controller. */
float pid_get_ki(const pid_filter_t *pid);

/** Returns the derivative gain of the controller. */
float pid_get_kd(const pid_filter_t *pid);

/** Returns the value of the PID integrator. */
float pid_get_integral(const pid_filter_t *pid);

/** Process one step if the PID algorithm. */
float pid_process(pid_filter_t *pid, float value);

#endif
