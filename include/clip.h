#pragma once

#include "image.h"

namespace GET
{



/**
 * Truncates the value range of an image at the specified boundaries.
 * 
 * That is, each pixel that is above the upper bound is set to the upper bound value. 
 *Similarly, any pixel whose value is below the lower bound is set to the lower bound.
 * 
 * @author Holger Täubig
 * @version FINISHED.
 * @note no sources
 */
class Clip
{
	/** lower limit of the value range */
	float m_minval;
	
	/** upper limit of the value range */
	float m_maxval;
  public:
	/** Constructor */
	Clip(  );
	
	/** Sets the range of values to which the images should be clipped with doClip() */
	void setRange( float minval = 0, float maxval = 255 );
	
	/** The pixels of the image are clipped to the set value range as described under Clip.
	 * 
	 * @param image Image whose value range is to be cropped
	 */
	void doClipImage( Image<float> &image );
};



}/*__GET__CLIP_H*/
