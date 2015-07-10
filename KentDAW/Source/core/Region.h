/*
  ==============================================================================

    Region.h
    Created: 9 Jul 2015 9:10:36pm
    Author:  Matt

  ==============================================================================
*/

#ifndef REGION_H_INCLUDED
#define REGION_H_INCLUDED

struct Region
{
	/*
	The UNIQUE ID of a region
	*/
	int regionID;

	/*
	The start position of a region. The time is measured in samples.
	*/
	int startPostion;

	/*
	The end position of a region. The time is measured in samples and represents
	the first sample after the end of the region
	*/
	int endPosition;

	/*
	The point in time where the region begins on the timeline. The time is measured
	in samples.
	*/
	int regionBeginPosition;
};



#endif  // REGION_H_INCLUDED
