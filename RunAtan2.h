typedef short S16;
typedef double F64;



#define MATH_PAI                 (3.14159265)			// pi
#define MATH_PAI_MINUS           (-3.14159265)			// pi
#define MATH_PAI_HALF            (1.570796325)			// pi /2
#define MATH_PAI_HALF_MINUS      (-1.570796325)			// -pi /2
#define MATH_RADIAN2DEGREE		(57.29577951)			// 180 / pi


#define MATH_PAI_DEGREE       		(360.0)
#define MATH_PAI_MINUS_DEGREE 		(0.0)
#define MATH_PAI_HALF_DEGREE       	(270.0)
#define MATH_PAI_HALF_MINUS_DEGREE  (90.0)	

#define Q_15                0x8000                      // fix point Q15 32768
#define Q_15_BIT  15

#define Q_15_INV		 1.0/32768

#define Q_15_1			 Q_15
#define Q_15_1_MINUS	 -Q_15
#define Q_15_0	 		 0

#define MATH_SIGN(x) ((x<0) ? -1:1)	
#define	C_PI		3.1415926
#define	C_2PI		6.2831853
#define C_RADIAN2DEGREE		(360.0 / C_2PI)

#define Q_15_INV_x100 			100.0/32768					// scaled
#define Q_15_INV_MINUS_x100		-100.0/32768

extern double Cmath_Gdi_atan2_qMath2(short s16Xdata, short s16Ydata);