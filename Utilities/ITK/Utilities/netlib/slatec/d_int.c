#define V3P_NETLIB_SRC
#include "v3p_netlib.h"

#ifdef KR_headers
double floor();
double d_int(x) doublereal *x;
#else
#undef abs
#include "math.h"
double d_int(doublereal *x)
#endif
{
return( (*x>0) ? floor(*x) : -floor(- *x) );
}
