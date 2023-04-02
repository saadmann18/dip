#pragma once

#include <iostream>

namespace GET
{

	/**
	 * Complex number (base data type for complex-valued images).
	 *
	 * Each pixel of a complex-valued image (Image<Complex>) is of type Complex.
	 * The class implements the most important arithmetic operations as well as
	 *operations for converting a pixel from and to a complex number.
	 *
	 * #Notes on arithmetic with numbers of the complex type:#
	 *- operator*=(float) is faster than operator*=(complex)  [the same applies to other arithmetic operations]
	 *- The variant a=b;a*=c; is faster than a=b*c  [the same applies to other arithmetic operations]
	 *
	 * @author Holger T�ubig
	 * @version FINISHED.
	 * @note no sources
	 */
	struct Complex
	{
		/** real part */
		float re;
		/** imaginary part */
		float im;

		/* ************************************************************************** */
		/* *** assignments ********************************************************** */
		/* ************************************************************************** */

		/**
		 * allocation float -> Complex
		 */
		inline Complex &operator=(const float &src)
		{
			re = src;
			im = 0.0f;
			return *this;
		}

		/**
		 * allocation Complex -> float
		 */
		/*	inline operator float( )
			{
				return re;
			}
		*/
	};

	/* ******************************************************************************* */
	/* *** Notes on the following implementation************************************* */
	/* ******************************************************************************* */
	/*
	 * - The operators are faster if NO CONSTRUCTOR for Complex exists
	 * - the following implementation of the operator+ was slower than the
	 * one implemented here (see testComplex)
	 *
	 *     inline const Complex add1( const Complex &a, const Complex &b )
	 *     {
	 *      	Complex res(a);
	 *      	return  res *= b;
	 *     };
	 *
	 * - the same applies to operators*
	 */
	/* ******************************************************************************* */

	/* ******************************************************************************* */
	/* *** arithmetic operations ********************************************************* */
	/* ******************************************************************************* */

	/**
	 * Addition.
	 */
	inline Complex &operator+=(Complex &a, const Complex &b)
	{
		a.re += b.re;
		a.im += b.im;
		return a;
	}
	inline Complex &operator+=(Complex &a, const float &b)
	{
		a.re += b;
		return a;
	}

	inline const Complex operator+(const Complex &a, const Complex &b)
	{
		Complex c;
		c.re = a.re + b.re;
		c.im = a.im + b.im;
		return c;
	}
	inline const Complex operator+(const float &a, const Complex &b)
	{
		Complex c;
		c.re = a + b.re;
		c.im = b.im;
		return c;
	}
	inline const Complex operator+(const Complex &a, const float &b)
	{
		Complex c;
		c.re = a.re + b;
		c.im = a.im;
		return c;
	}

	/**
	 * Multiplication.
	 */
	inline Complex &operator*=(Complex &a, const Complex &b)
	{
		float tmp_re = a.re;
		float tmp_im = a.im;
		a.re = tmp_re * b.re - tmp_im * b.im;
		a.im = tmp_re * b.im + tmp_im * b.re;
		return a;
	}
	inline Complex &operator*=(Complex &a, const float &b)
	{
		a.re *= b;
		a.im *= b;
		return a;
	}

	inline const Complex operator*(const Complex &a, const Complex &b)
	{
		Complex c;
		c.re = a.re * b.re - a.im * b.im;
		c.im = a.re * b.im + a.im * b.re;
		return c;
	}
	inline const Complex operator*(const float &a, const Complex &b)
	{
		Complex c;
		c.re = a * b.re;
		c.im = a * b.im;
		return c;
	}
	inline const Complex operator*(const Complex &a, const float &b)
	{
		Complex c;
		c.re = b * a.re;
		c.im = b * a.im;
		return c;
	}

	/**
	 * Subtraction.
	 */
	inline Complex &operator-=(Complex &a, const Complex &b)
	{
		a.re -= b.re;
		a.im -= b.im;
		return a;
	}
	inline Complex &operator-=(Complex &a, const float &b)
	{
		a.re -= b;
		return a;
	}

	inline const Complex operator-(const Complex &a, const Complex &b)
	{
		Complex c;
		c.re = a.re - b.re;
		c.im = a.im - b.im;
		return c;
	}
	inline const Complex operator-(const float &a, const Complex &b)
	{
		Complex c;
		c.re = a - b.re;
		c.im = -b.im;
		return c;
	}
	inline const Complex operator-(const Complex &a, const float &b)
	{
		Complex c;
		c.re = a.re - b;
		c.im = a.im;
		return c;
	}

	/**
	 * Negation
	 */
	inline const Complex operator-(const Complex &b)
	{
		Complex c;
		c.re = -b.re;
		c.im = -b.im;
		return c;
	}

	/* ******************************************************************************* */
	/* *** Output operators ********************************************************* */
	/* ******************************************************************************* */

	inline std::ostream &operator<<(std::ostream &stream, const Complex &val)
	{
		stream << "(" << val.re << "," << val.im << ")";
		return stream;
	}

}
