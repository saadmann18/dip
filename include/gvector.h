#ifndef __GET__VECTORS_H_
#define __GET__VECTORS_H_

namespace GET 
{
	
	

/**
 * Zwiedimensionaler Vektor mit den Komponenten x und y.
 * 
 * @author Holger T�ubig
 * @version unvollst�ndig aber FUNKTIONSF�HIG.
 */	
struct Vector2D
{
	float x;
	float y;
};

/**
 * Multiplikation mit einem Skalar.
 */
inline Vector2D& operator*=(Vector2D& vec, const float& val )
{
	vec.x *= val;
	vec.y *= val;
	return vec;
}


/**
 * Dreidimensionaler Vektor mit den Komponenten x, y und z.
 * 
 * @author Holger T�ubig
 * @version unvollst�ndig aber FUNKTIONSF�HIG.
 */	
struct Vector3D 
{
	float x;
	float y;
	float z;
};



}

#endif /*VECTOR_H_*/
