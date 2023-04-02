#include "fdfiltering_basetemplate.h"
#include "gexception.h"

namespace GET
{

	template <typename MASKTYPE>
	FrequencyDomainFilteringBaseTemplate<MASKTYPE>::FrequencyDomainFilteringBaseTemplate() : m_filter_mask(),
																							 m_filter_mask_available(false),
																							 m_input_image(),
																							 m_input_image_available(false)
	{
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setMask(const Image<MASKTYPE> &filter_mask)
	{
		// Copy filter mask
		m_filter_mask.copy(filter_mask);

		// Test whether the new mask can be used.
		if ((m_filter_mask.getWidth() > 0) && (m_filter_mask.getHeight() > 0))
			m_filter_mask_available = true;
		else
			m_filter_mask_available = false;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::getMask(Image<MASKTYPE> &filter_mask)
	{
		filter_mask.copy(m_filter_mask);
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setImage(const Image<Complex> &image)
	{
		// Copy filter mask
		m_input_image.copy(image);

		// Input fields are always usable (even empty ones)
		m_input_image_available = true;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doFiltering(const Image<Complex> &input_image, const Image<MASKTYPE> &filter_mask, Image<Complex> &result)
	{
		//
		// Test sizes
		//
		if ((input_image.getWidth() != filter_mask.getWidth()) || (input_image.getHeight() != filter_mask.getHeight()))
		{
			throw GException(
				"FrequencyFiltering::doFiltering( const Image<Complex> &input_image, const Image<float> &filter_mask, Image<Complex> &result )",
				"Filter mask and image must be the same size.");
		}
		if ((input_image.getWidth() != result.getWidth()) || (input_image.getHeight() != result.getHeight()))
		{
			result.resize(input_image.getWidth(), input_image.getHeight());
		}

		//
		// Get data pointer
		//
		MASKTYPE *mask_data = filter_mask.getData();
		Complex *inp_data = input_image.getData();
		Complex *res_data = result.getData();

		//
		// Go through the entire image area
		//
		for (MASKTYPE *ende = mask_data + filter_mask.getSize(); mask_data < ende; ++mask_data)
		{
			*(res_data++) = *(inp_data++) * (*mask_data);
		}
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setIdealLowpassMask(float d0, int width, int height)
	{
		if ((width > 0) && (height > 0))
		{
			// Adjust mask size
			m_filter_mask.resize(width, height);

			// Get data pointer
			MASKTYPE *mdata = m_filter_mask.getData();

			// Calculate the center of the image exactly
			float mx = (float)width / 2.0f;
			float my = (float)height / 2.0f;

			// Loop through the image and set all pixels inside the circle with radius d0 to 1
			float radius2 = d0 * d0;
			register float distx, disty;

			for (int y = 0; y < height; ++y)
				for (int x = 0; x < width; ++x)
				{
					distx = x - mx;
					disty = y - my;
					if (distx * distx + disty * disty > radius2)
						*(mdata++) = 0.0f;
					else
						*(mdata++) = 1.0f;
				}

			// Filter mask prepared
			m_filter_mask_available = true;
		}
		else
			m_filter_mask_available = false;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setIdealHighpassMask(float d0, int width, int height)
	{
		if ((width > 0) && (height > 0))
		{
			// Adjust mask size
			m_filter_mask.resize(width, height);

			// Get data pointer
			MASKTYPE *mdata = m_filter_mask.getData();

			// Calculate the center of the image exactly
			float mx = (float)width / 2.0f;
			float my = (float)height / 2.0f;

			// Loop through the image and set all pixels inside the circle with radius d0 to 1
			float radius2 = d0 * d0;
			register float distx, disty;

			for (int y = 0; y < height; ++y)
				for (int x = 0; x < width; ++x)
				{
					distx = x - mx;
					disty = y - my;
					if (distx * distx + disty * disty > radius2)
						*(mdata++) = 1.0f;
					else
						*(mdata++) = 0.0f;
				}

			// Filter mask prepared
			m_filter_mask_available = true;
		}
		else
			m_filter_mask_available = false;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setButterworthLowpassMask(float d0, int n, int width, int height)
	{
		if ((width > 0) && (height > 0))
		{
			// Adjust mask size
			m_filter_mask.resize(width, height);

			// Get data pointer
			MASKTYPE *mdata = m_filter_mask.getData();

			// Calculate the center of the image exactly
			float mx = (float)width / 2.0f;
			float my = (float)height / 2.0f;

			// Loop through the image and set all pixels inside the circle with radius d0 to 1
			float radius2 = d0 * d0;
			register float distx, disty;

			for (int y = 0; y < height; ++y)
				for (int x = 0; x < width; ++x)
				{
					// Weight calculation for 1 / (1 + (D(u,v)/d0) ^ 2n ) d0 and D(u,v) are already squared
					distx = x - mx;
					disty = y - my;
					*(mdata++) = 1.0f / (1.0f + powf((distx * distx + disty * disty) / radius2, n));
				}

			// Filter mask prepared
			m_filter_mask_available = true;
		}
		else
			m_filter_mask_available = false;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setButterworthHighpassMask(float d0, int n, int width, int height)
	{
		if ((width > 0) && (height > 0))
		{
			// Adjust mask size
			m_filter_mask.resize(width, height);

			// Get data pointer
			MASKTYPE *mdata = m_filter_mask.getData();

			// Calculate the center of the image exactly
			float mx = (float)width / 2.0f;
			float my = (float)height / 2.0f;

			// Loop through the image and set all pixels inside the circle with radius d0 to 1
			float radius2 = d0 * d0;
			register float distx, disty;

			for (int y = 0; y < height; ++y)
				for (int x = 0; x < width; ++x)
				{
					// Weight calculation for 1 / (1 + (d0/D(u,v)) ^ 2n ) d0 and D(u,v) are already squared
					distx = x - mx;
					disty = y - my;
					*(mdata++) = 1.0f / (1.0f + powf(radius2 / (distx * distx + disty * disty), n));
				}

			// Filtermaske vorbereitet
			m_filter_mask_available = true;
		}
		else
			m_filter_mask_available = false;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::getSpatialMask(Image<Complex> &filter_mask)
	{
		// inverse Fourier-Transformation
		a_fft.doInvFourierTransform2D(m_filter_mask, filter_mask);
		// Nyquist Modulation
		a_fft.doNyquistModulation(filter_mask);
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::setSpatialImage(const Image<Complex> &image)
	{
		// Nyquist Modulation
		a_fft.doNyquistModulation(image, m_tmp2);
		// Copy filter mask
		a_fft.doFourierTransform2D(m_tmp2, m_input_image);

		// Input images are always usable (even empty ones)
		m_input_image_available = true;
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doConvolution(Image<Complex> &result)
	{
		if (m_filter_mask_available && m_input_image_available)
		{
			// Perform filtering
			doFiltering(m_input_image, m_filter_mask, m_tmp1);
			// Transform the result back into position space
			a_fft.doInvFourierTransform2D(m_tmp1, result);
			// Nyquist Modulation
			a_fft.doNyquistModulation(result);
		}
		else
		{
			gerr << "Error in FrequencyFiltering::doConvolution( Image<Complex> &result )" << endl;
			gerr << "Filter mask or input image does not exist." << endl;
		};
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doConvolutionWithImage(const Image<Complex> &input_image, Image<Complex> &result)
	{
		if (m_filter_mask_available)
		{
			// Nyquist Modulation
			a_fft.doNyquistModulation(input_image, m_tmp1);
			// Bild in den Frequenzraum transformieren
			a_fft.doFourierTransform2D(m_tmp1, m_tmp2);
			// Perform filtering
			doFiltering(m_tmp2, m_filter_mask, m_tmp1);
			// Transform the result back into position space
			a_fft.doInvFourierTransform2D(m_tmp1, result);
			// Nyquist Modulation
			a_fft.doNyquistModulation(result);
		}
		else
		{
			gerr << "Error in FrequencyFiltering::doConvolutionWithImage( const Image<Complex> &input_image, Image<Complex> &result )" << endl;
			gerr << "Filter mask does not exist." << endl;
		};
	}

	template <typename MASKTYPE>
	void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doFilteringWithMaskGiveSpatialResult(const Image<MASKTYPE> &filter_mask, Image<Complex> &result)
	{
		if (m_input_image_available)
		{
			// Perform filtering
			doFiltering(m_input_image, filter_mask, m_tmp1);
			// Transform the result back into position space
			a_fft.doInvFourierTransform2D(m_tmp1, result);
			// Nyquist Modulation
			a_fft.doNyquistModulation(result);
		}
		else
		{
			gerr << "Error in FrequencyFiltering::doFilteringWithMask( const Image<Complex> &filter_mask, Image<Complex> &result )" << endl;
			gerr << "Input image does not exist." << endl;
		};
	}

}
