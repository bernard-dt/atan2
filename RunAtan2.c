// RunAtan2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include "RunAtan2.h"



const double f64AtanTable[101] = {
				   0,  			0.009999667,    0.019997334,    0.029991005,    0.039978687,    0.049958396,    0.059928155,    0.069886002,    0.079829986,    0.089758174,
				   0.099668652, 0.109559527,    0.119428926,    0.129275004,    0.139095941,    0.148889948,    0.158655262,    0.168390157,    0.178092938,    0.187761947,
				   0.19739556, 	0.206992194,    0.216550305,    0.226068388,    0.235544981,    0.244978663,    0.254368059,    0.263711834,    0.273008703,    0.282257422,
				   0.291456794, 0.30060567, 	0.309702945,    0.31874756, 	0.327738507,    0.336674819,    0.345555581,    0.354379919,    0.36314701, 	0.371856074,
				   0.380506377, 0.389097231,    0.397627992,    0.406098058,    0.414506875,    0.422853926,    0.431138741,    0.439360887,    0.447519975,    0.455615653,
				   0.463647609, 0.471615568,    0.479519292,    0.48735858, 	0.495133263,    0.502843211,    0.510488322,    0.518068528,    0.525583794,    0.53303411,
				   0.5404195,  	0.547740014,    0.554995727,    0.562186744,    0.569313191,    0.576375221,    0.583373007,    0.590306747,    0.597176658,    0.603982978,
				   0.610725964, 0.617405892,    0.624023053,    0.630577757,    0.637070329,    0.643501109,    0.649870449,    0.656178718,    0.662426294,    0.668613568,
				   0.674740942, 0.680808829,    0.68681765, 	0.692767835,    0.698659825,    0.704494064,    0.710271007,    0.715991114,    0.721654851,    0.727262688,
				   0.732815102, 0.738312573,    0.743755584,    0.749144625,    0.754480184,    0.759762755,    0.764992833,    0.770170914,    0.775297497,    0.78037308,
				   0.785398163
};


int main()
{
	double ret,ret1;
	int result;
	int i, j;
	result = 1;

#if 1
	for (i = -10000; i < 10000; i = i + 1)
	{
		for (j = -10000; j < 10000; j = j + 1)
		{
			ret = Cmath_Gdi_atan2_qMath2(i, j);
			ret1 = Cmath_Gdi_atan2_qMath3(i, j);

			if (ret != ret1)
			{
				printf("\r\n %.4lf , %.4lf", ret, ret1);
				result = 0;
				break;
			}
			//Sleep(20);
		}
		if (result == 0)
		{
			break;
		}
	}
	printf("\r\nTo End :  %d , %d", i,j);
#endif
}


double Cmath_arcTan_Calc(short s16Index, double f64Xdot)
{
	double f64ArcTanInterpol = 0;

	if (s16Index < 0)	s16Index = 0;
	if (s16Index > 100)	s16Index = 100;

	f64ArcTanInterpol = f64AtanTable[s16Index] + (f64Xdot - (double)s16Index) * (f64AtanTable[s16Index + 1] - f64AtanTable[s16Index]);

	return f64ArcTanInterpol;
}

double Cmath_Gdi_atan2_qMath2(short s16CosData, short s16SinData)				// 15usec,  return degree
{
	double rVal = 0;

	int   s32YdivX_Scaled;
	int   s32YdivX_Inv_Scaled;

	double f64Xdot;

	double f64ArcTanInterpol;
	double f64ArcTan;

	// arctan2 -  case : x == 0  
	if (s16CosData == 0)
	{

		if (s16SinData > 0)		f64ArcTan = MATH_PAI_HALF;
		else if (s16SinData < 0)	f64ArcTan = MATH_PAI_HALF_MINUS;
		else					f64ArcTan = 0;
	}
	else
	{
		s32YdivX_Scaled = (abs(s16SinData) << Q_15_BIT) / abs(s16CosData);
		s32YdivX_Scaled = s32YdivX_Scaled * MATH_SIGN(s16CosData) * MATH_SIGN(s16SinData);

		if (s16SinData != 0)
		{
			s32YdivX_Inv_Scaled = (abs(s16CosData) << Q_15_BIT) / abs(s16SinData);
			s32YdivX_Inv_Scaled = s32YdivX_Inv_Scaled * MATH_SIGN(s16CosData) * MATH_SIGN(s16SinData);
		}
		else
			s32YdivX_Inv_Scaled = 0;

		if (s32YdivX_Scaled >= Q_15_0)
		{
			if (s32YdivX_Scaled <= Q_15_1)
			{
				f64Xdot = (double)s32YdivX_Scaled * Q_15_INV_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot); 		// 8usec

				f64ArcTan = f64ArcTanInterpol;
			}
			else
			{
				f64Xdot = (double)s32YdivX_Inv_Scaled * Q_15_INV_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);

				f64ArcTan = MATH_PAI_HALF - f64ArcTanInterpol;
			}
		}
		else		// f64YdivX < 0
		{
			if (s32YdivX_Scaled >= Q_15_1_MINUS)
			{
				f64Xdot = (double)s32YdivX_Scaled * Q_15_INV_MINUS_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);

				f64ArcTan = -f64ArcTanInterpol;

			}
			else
			{
				f64Xdot = (double)s32YdivX_Inv_Scaled * Q_15_INV_MINUS_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);

				f64ArcTan = MATH_PAI_HALF_MINUS - (-f64ArcTanInterpol);
			}

		}

		if (s16CosData > 0)
		{
			f64ArcTan = f64ArcTan;
		}
		else
		{
			if (s16SinData >= 0)	f64ArcTan = MATH_PAI + f64ArcTan;
			else				f64ArcTan = MATH_PAI_MINUS + f64ArcTan;
		}
	}

	///gf64ArcTan = f64ArcTan; 			// just for test
	rVal = (f64ArcTan + MATH_PAI) * C_RADIAN2DEGREE;

	return rVal;
}



double Cmath_Gdi_atan2_qMath3(short s16CosData, short s16SinData)				// 15usec,  return degree
{
	double rVal = 0;

	int   s32YdivX_Scaled;
	int   s32YdivX_Inv_Scaled;

	double f64Xdot;

	double f64ArcTanInterpol;
	double f64ArcTan;

	// arctan2 -  case : x == 0  
	if (s16CosData == 0)
	{

		if (s16SinData > 0)		f64ArcTan = MATH_PAI_HALF;
		else if (s16SinData < 0)	f64ArcTan = MATH_PAI_HALF_MINUS;
		else					f64ArcTan = 0;
	}
	else
	{
		s32YdivX_Scaled = (abs(s16SinData) << Q_15_BIT) / abs(s16CosData);
		s32YdivX_Scaled = s32YdivX_Scaled * MATH_SIGN(s16CosData) * MATH_SIGN(s16SinData);

		if (s32YdivX_Scaled >= Q_15_0)
		{
			if (s32YdivX_Scaled <= Q_15_1)
			{
				f64Xdot = (double)s32YdivX_Scaled * Q_15_INV_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot); 		// 8usec

				f64ArcTan = f64ArcTanInterpol;
			}
			else
			{
				s32YdivX_Inv_Scaled = (abs(s16CosData) << Q_15_BIT) / abs(s16SinData);
				s32YdivX_Inv_Scaled = s32YdivX_Inv_Scaled * MATH_SIGN(s16CosData) * MATH_SIGN(s16SinData);
				f64Xdot = (double)s32YdivX_Inv_Scaled * Q_15_INV_x100;
				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);
				f64ArcTan = MATH_PAI_HALF - f64ArcTanInterpol;
			}
		}
		else		// f64YdivX < 0
		{
			if (s32YdivX_Scaled >= Q_15_1_MINUS)
			{
				f64Xdot = (double)s32YdivX_Scaled * Q_15_INV_MINUS_x100;

				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);

				f64ArcTan = -f64ArcTanInterpol;

			}
			else
			{
				s32YdivX_Inv_Scaled = (abs(s16CosData) << Q_15_BIT) / abs(s16SinData);
				s32YdivX_Inv_Scaled = s32YdivX_Inv_Scaled * MATH_SIGN(s16CosData) * MATH_SIGN(s16SinData);
				f64Xdot = (double)s32YdivX_Inv_Scaled * Q_15_INV_MINUS_x100;
				f64ArcTanInterpol = Cmath_arcTan_Calc((short)f64Xdot, f64Xdot);
				f64ArcTan = MATH_PAI_HALF_MINUS - (-f64ArcTanInterpol);
			}

		}

		if (s16CosData > 0)
		{
			f64ArcTan = f64ArcTan;
		}
		else
		{
			if (s16SinData >= 0)	f64ArcTan = MATH_PAI + f64ArcTan;
			else				f64ArcTan = MATH_PAI_MINUS + f64ArcTan;
		}
	}

	///gf64ArcTan = f64ArcTan; 			// just for test
	rVal = (f64ArcTan + MATH_PAI) * C_RADIAN2DEGREE;

	return rVal;
}
