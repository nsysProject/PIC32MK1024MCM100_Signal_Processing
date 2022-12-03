#include "trig.h"
/****************************************************************************
 * This file contains the trigonometric calculations using various
 * methods
 *
 ****************************************************************************/
ANG_t Taylor_SincosParm;
/****************************************************************************
 * Input: pointer to structure of type "ANG_t". The parameter "angle" from 
 * the structure should be in radians (0 to 2*PI).
 * 
 * Output: void. The sine and cosine are returned as elements of the structure
 * 
 * APPROXIMATE execution time: 3.33uSec
 ****************************************************************************/
void Taylor_SinCos(ANG_t *ptr)
{
    float y0 = ptr->angle;
    if(ptr->angle > M_PI)
    {
        y0 = -(ptr->angle - M_PI);
    }
    

    float x2 = (y0 * y0);    
    float x3 = (x2 * y0);
    float x4 = (x3 * y0);
    float x5 = (x4 * y0);
    float x6 = (x5 * y0);
    float x7 = (x6 * y0);
    
    float y2 = x2/(1.0*2.0);
    float y3 = x3/(1.0*2.0*3.0);
    float y4 = x4/(1.0*2.0*3.0*4.0);
    float y5 = x5/(1.0*2.0*3.0*4.0*5.0);
    float y6 = x6/(1.0*2.0*3.0*4.0*5.0*6.0);
    float y7 = x7/(1.0*2.0*3.0*4.0*5.0*6.0*7.0);
    
    ptr->sin = (y0 - y3 + y5 - y7);
    ptr->cos = (1.0 - y2 + y4 - y6);
    
    if(ptr->angle > M_PI)
    {
        ptr->cos = -ptr->cos;
    }
}
/****************************************************************************
 *
 *
 *
 ****************************************************************************/
