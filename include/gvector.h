#pragma once

namespace GET 
{
	
	

/**
 * Zwiedimensionaler Vektor mit den Komponenten x und y.
 * 
 * @author Holger Täubig
 * @version unvollständig aber FUNKTIONSFÄHIG.
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
 * @author Holger Täubig
 * @version unvollständig aber FUNKTIONSFÄHIG.
 */	
struct Vector3D 
{
	float x;
	float y;
	float z;
};



} /*VECTOR_H_*/
