#include "s21_math.h"

long double s21_sqrt(double x) {
  long double left = 0, right = x + 1;
  if (is_nan(x)) {
    left = S21_NAN;
  } else if (is_inf(x)) {
    if (x > 0)
      left = S21_INF;
    else
      left = S21_NAN;
  } else if (x < 0) {
    left = S21_NAN;
  } else if (x == 0)
    ;
  else {
    for (int i = 0; i < 100; i++) {
      long double middle = (left + right) / 2;
      if (middle * middle < x) {
        left = middle;
      } else {
        right = middle;
      }
    }
  }
  return left;
}

long double s21_ceil(double x) {
  long long int intPart = (long long int)x;
  long double result = 0;
  if (x != DBL_MAX) {
    if (is_nan(x)) {
      result = S21_NAN;
    } else if (is_inf(x)) {
      if (x > 0)
        result = S21_INF;
      else
        result = -S21_INF;
    } else if (x == intPart) {
      result = intPart;
    } else if (x > 0) {
      result = intPart + 1;
    } else {
      result = intPart;
    }
  } else
    result = DBL_MAX;
  return result;
}

long double s21_floor(double x) {
  long long int intPart = (long long int)x;
  long double result = 0;
  if (is_nan(x)) {
    result = S21_NAN;
  } else if (is_inf(x)) {
    if (x > 0)
      result = S21_INF;
    else
      result = -S21_INF;
  } else if (x == intPart) {
    result = intPart;
  } else if (x < 0) {
    result = intPart - 1;
  } else {
    result = intPart;
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (is_nan(x) || is_nan(y)) {
    result = S21_NAN;
  } else if (x == 0 && y == 0) {
    result = S21_NAN;
  } else if (is_inf(x)) {
    result = S21_NAN;
  } else if (is_inf(y)) {
    result = x;
  } else if (x / y < 0) {
    result = (long double)x - (long double)y * s21_ceil(x / y);
  } else if (x / y > 0) {
    result = (long double)x - (long double)y * s21_floor(x / y);
  }
  return result;
}

long long int s21_abs_long_int(long long int x) { return x > 0 ? x : -x; }

long double s21_pow_helper(double x, double y) {
  int x_is_nan = is_nan(x);
  int x_is_fin = is_fin(x);
  int y_is_nan = is_nan(y);
  int y_is_fin = is_fin(y);
  int y_min = s21_fabs(y - s21_floor(y)) <= S21_EPS;
  long double result = 0;

  if (x_is_fin && !x_is_nan && x == +0 && x <= S21_EPS && y_min &&
      ((int)y) < 0 && ((int)y) % 2) {
    result = S21_INF;
  }

  else if (x_is_fin && !x_is_nan && x == -0 && x <= S21_EPS && y_min &&
           ((int)y) < 0 && ((int)y) % 2) {
    result = -S21_INF;
  }

  else if (x_is_fin && !x_is_nan && s21_fabs(x) < S21_EPS && y_is_fin &&
           ((y_min && !(((int)y) % 2)) || !y_min)) {
    if (x == 0 && y == 0) {
      result = 1;
    } else if (x == 0 && y > 0) {
      result = 0;
    } else
      result = S21_INF;
  }

  else if (x_is_fin && !x_is_nan && s21_fabs(x) < S21_EPS && !y_is_nan &&
           !y_is_fin && y < 0) {
    result = S21_INF;
  }

  else if (x_is_fin && !x_is_nan && x > 0 && x <= S21_EPS && y_min &&
           ((int)y) % 2) {
    result = +0;
  }

  else if (x_is_fin && !x_is_nan && x < 0 && x >= -S21_EPS && y_min &&
           ((int)y) % 2) {
    result = -0;
  }

  else if (x_is_fin && !x_is_nan && s21_fabs(x) < S21_EPS &&
           ((!y_min && s21_fabs(y) > S21_EPS) || (y_min && !(((int)y) % 2)))) {
    result = +0;
  }

  else if (x_is_fin && !x_is_nan && s21_fabs(x + 1) < S21_EPS && !y_is_fin &&
           !y_is_nan) {
    result = 1;
  }

  else if (x_is_fin && !x_is_nan && s21_fabs(x - 1) < S21_EPS) {
    result = 1;
  }

  else if (s21_fabs(y) < S21_EPS) {
    result = 1;
  }

  else if (x_is_fin && x < -S21_EPS && y_is_fin && !y_min) {
    result = S21_NAN;
  }

  else if (s21_fabs(x) - 1 < S21_EPS && !y_is_nan && !y_is_fin && y < 0) {
    result = S21_INF;
  }

  else if (s21_fabs(x) - 1 > S21_EPS && !y_is_nan && !y_is_fin && y < 0) {
    result = +0;
  }

  else if (s21_fabs(x) - 1 < S21_EPS && !y_is_nan && !y_is_fin && y > 0) {
    result = +0;
  }

  else if (s21_fabs(x) - 1 > S21_EPS && !y_is_nan && !y_is_fin && y > 0) {
    result = S21_INF;
  }

  else if (!x_is_nan && !x_is_fin && x < 0 && y_min && y < 0 && ((int)y) % 2) {
    result = -0;
  }

  else if (!x_is_nan && !x_is_fin && x < 0 &&
           ((!y_min && y < 0) || (y_min && y < 0 && !(((int)y) % 2)))) {
    result = +0;
  }

  else if (!x_is_nan && !x_is_fin && x < 0 &&
           (y_min && y > 0 && ((int)y) & 1)) {
    result = -S21_INF;
  }

  else if (!x_is_nan && !x_is_fin && x < 0 &&
           ((!y_min && y > 0) || (y_min && y > 0 && !(((int)y) % 2)))) {
    result = +S21_INF;
  }

  else if (!x_is_nan && !x_is_fin && x > 0 && y < -S21_EPS) {
    result = +0;
  }

  else if (!x_is_nan && !x_is_fin && x > 0 && y > S21_EPS) {
    result = +S21_INF;
  }

  else if (x_is_nan || y_is_nan) {
    result = S21_NAN;
  } else
    result = 111.111;
  return result;
}

long double s21_pow_int(long double x, long long int y_int) {
  long double res;
  if (y_int >= 0) {
    res = 1;
    while (y_int) {
      if (y_int & 1) {
        res *= x;
      }
      x *= x;
      y_int /= 2;
    }
  } else {
    res = 1 / s21_pow_int(x, -y_int);
  }
  return res;
}

long double s21_pow(double x, double y) {
  long double res;
  long double copy = x;
  long long int copy_y_int = (long long int)y;
  if (is_inf(y) && x == -1) {
    res = (long double)(-x);
  } else if (is_nan(y) && x == 1.) {
    res = 1;
  } else if (is_inf(y) && !is_fin(x)) {
    if (y < 0) {
      res = 0;
    } else {
      res = S21_INF;
    }
  } else if (s21_pow_helper(x, y) != 111.111) {
    res = s21_pow_helper(x, y);
  } else if (s21_fabs(y) - s21_abs_long_int(copy_y_int) < 1e-6) {
    res = s21_pow_int(copy, copy_y_int);
  } else if ((x < 0) && s21_fmod(y, 1) != 0) {
    res = S21_NAN;
  } else if (y == 0) {
    res = 1;
  } else if (x == 0 && y > 0) {
    res = 0;
  } else {
    if (copy < 0) {
      copy = -copy;
      res = s21_exp(y * s21_log(copy));
      if (s21_fmod(y, 2) != 0) {
        res = -res;
      }
    } else {
      res = s21_exp(y * s21_log(x));
    }
  }
  return res;
}

long double s21_fact(double x) {
  long double ret = 1;
  for (int i = 1; i <= x; i++) ret *= i;
  return ret;
}

long double s21_sin(double x) {
  long double y = 0;
  long double s = -1;
  if (is_nan(x)) {
    y = S21_NAN;
  } else if (is_inf(x)) {
    y = S21_NAN;
  } else {
    if (x > 2 * S21_PI) x = s21_fmod(x, 2 * S21_PI);
    if (x < -2 * S21_PI) x = s21_fmod(x, -2 * S21_PI);
    y += x;
    for (int i = 3; i <= 500; i += 2) {
      y += s * (s21_pow(x, i) / s21_fact(i));
      s *= -1;
    }
  }
  return y;
}
long double s21_cos(double x) {
  long double y = 1;
  long double s = -1;
  if (is_nan(x)) {
    y = S21_NAN;
  } else if (is_inf(x)) {
    y = S21_NAN;
  } else {
    if (x > 2 * S21_PI) x = s21_fmod(x, 2 * S21_PI);
    if (x < -2 * S21_PI) x = s21_fmod(x, -2 * S21_PI);
    for (int i = 2; i <= 500; i += 2) {
      y += s * (s21_pow(x, i) / s21_fact(i));
      s *= -1;
    }
  }
  return y;
}

long double s21_tan(double x) {
  long double y = 0;
  if (x == S21_PI / 2) {
    y = 16331239353195370L;
  } else if (x == -S21_PI / 2) {
    y = -16331239353195370L;
  } else
    y = (s21_sin(x) / s21_cos(x));
  return y;
}

long double s21_exp(double x) {
  long double res = 1;
  long double temp = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(res) > S21_EPS) {
    res *= x / i;
    i += 1;
    temp += res;
    if (temp > DBL_MAX) {
      temp = S21_INF;
      break;
    }
  }
  if (flag == 1) {
    if (temp > DBL_MAX) {
      temp = 0;
    } else {
      temp = 1. / temp;
    }
  }
  return temp;
}

long double s21_log(double x) {
  long double y = 0;
  if (is_nan(x)) {
    y = S21_NAN;
  } else if (x < 0) {
    y = S21_NAN;
  } else if (is_inf(x)) {
    y = S21_INF;
  } else if (x == 0) {
    y = -S21_INF;
  } else if (x == 1) {
    y = 0;
  } else {
    for (int i = 0; i < 357; i++) {
      y = y + 2 * ((x - s21_exp(y)) / (x + s21_exp(y)));
    }
  }
  return y;
}

long double s21_atan(double x) {
  long double s = 1;
  long double y = 0;
  long double a = 0;
  if (x == 1)
    y += S21_PI / 4;
  else if (x == -1)
    y += -S21_PI / 4;
  else if (x == S21_INF || x == -S21_INF) {
    if (x > 0)
      y = S21_PI / 2;
    else
      y = -S21_PI / 2;
  } else if (x > 1) {
    for (int i = 1; i <= 1000; i += 2) {
      a += s * (s21_pow(x, -i) / i);
      s *= -1;
    }
    y = S21_PI / 2 - a;
  } else if (x < -1) {
    for (int i = 1; i <= 1000; i += 2) {
      a += s * (s21_pow(x, -i) / i);
      s *= -1;
    }
    y = -S21_PI / 2 - a;
  } else {
    y += x;
    s *= -1;
    for (int i = 3; i <= 1000; i += 2) {
      y += s * (s21_pow(x, i) / i);
      s *= -1;
    }
  }
  return y;
}

long double s21_acos(double x) {
  long double y = 0;
  if (is_nan(x)) {
    y = S21_NAN;
  } else if (x > 1) {
    y = S21_NAN;
  } else if (x < -1) {
    y = -S21_NAN;
  } else if (x == (double)s21_sqrt(2) / 2) {
    y = S21_PI / 4;
  } else if (x == -(double)s21_sqrt(2) / 2) {
    y = 3 * S21_PI / 4;
  } else if (x > 0) {
    y = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
  } else if (x < 0) {
    y = S21_PI + s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
  } else {
    y = S21_PI / 2;
  }
  return y;
}

long double s21_asin(double x) {
  long double y = 0;
  if (is_nan(x)) {
    y = S21_NAN;
  } else if (is_inf(x)) {
    y = S21_NAN;
  } else if (x > 1) {
    y = S21_NAN;
  } else if (x < -1) {
    y = -S21_NAN;
  } else if (x == -(double)s21_sqrt(2) / 2) {
    y = -S21_PI / 4;
  } else if (x == (double)s21_sqrt(2) / 2) {
    y = S21_PI / 4;
  } else if (x == -(double)s21_sqrt(3) / 2) {
    y = -S21_PI / 3;
  } else if (x == 1)
    y = S21_PI / 2;
  else if (x == -1)
    y = -S21_PI / 2;
  else {
    y = s21_atan(x / s21_sqrt(1 - s21_pow(x, 2)));
  }
  return y;
}

int s21_abs(int x) {
  int b = 0;
  if (x < 0) {
    b = -x;
  } else
    b = x;
  return b;
}

long double s21_fabs(double x) {
  long double b = 0;
  if (x < 0) {
    b = -x;
  } else
    b = x;
  return b;
}