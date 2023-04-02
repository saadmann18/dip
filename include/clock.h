#pragma once

#include <sys/times.h>
#include <ostream>


namespace GET 
{

/** Stopwatch for process run time.
 * 
 * Suitable for carrying out runtime measurements for calculations/algorithms.
 * 
 * @author Holger Täubig
 * @version FINISHED.
 * @note no source.
 */
class Clock
{
  public:
    /** Conversion constant from %clock ticks to seconds.
     * 
     * Time is measured in CLOCK TICKS. With the help of this constant, 
     *these CLOCK TICKS can be converted into seconds.
     */
  	static long CLOCKS_TICKS_PER_SECOND;
  	
  private:
	struct tms m_clock;          ///< Total time of the stopwatch (all start->stop intervals)
	struct tms m_times_at_start; ///< Time the stopwatch was last started
	struct tms m_times_at_stop;  ///< Time the stopwatch was last stopped 

  public:
  	Clock( ); 		///< Constructor. 

  	void start(); 	///< Start stopwatch
	void stop(); 	///< Stop stopwatch
	void reset(); 	///< Reset stopwatch
	
	/**
	 * Returns the running time of the stopwatch.
	 * 
	 * @return Running time of the stopwatch in milliseconds [ms]
	 */
	long getElapsedTime();
	
	friend std::ostream& operator<<( std::ostream &out, const Clock &clock );
};

/** 
 * Stopwatch output.
 * 
 * Returns the stopped total time (all start->stop intervals) of the stopwatch.
 * 
 * @param out output stream (e.g. gout)
 * @param clock stopwatch to be printed
 * @return returns the output stream
 */
std::ostream& operator<<( std::ostream &out, const Clock &clock );

} /* namespace GET */
