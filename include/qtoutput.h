#ifndef __GET__QT_STANDARD_OUTPUT_H
#define __GET__QT_STANDARD_OUTPUT_H

#include <qtextedit.h>
#include "standardoutput.h"


namespace GET 
{



class QtStandardOutput : public StandardOutput::Observer
{
private:
	QTextEdit * TextWindow;
	QString     m_text;
  
	static QtStandardOutput *qt_output_gout;
	static QtStandardOutput *qt_output_gerr;
public:
	QtStandardOutput( std::string caption );
	virtual ~QtStandardOutput( );
	
	virtual void update( std::string text );
	
	static void initialize( );
};

	



} /* namespace GET */

#endif /* __IMAGE_H */
