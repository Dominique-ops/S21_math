#ifndef S21_MATH_H
#define S21_MATH_H

#include <ctype.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_PI 3.14159265358979323846264338327950288L
#define S21_EXP 2.7182818284590452353602874713526624L
#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_EPS 1e-6
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

long double s21_sqrt(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double a, double b);
long double s21_fact(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_atan(double x);
long double s21_acos(double x);
long double s21_asin(double x);
int s21_abs(int x);
long double s21_fabs(double x);

#endif