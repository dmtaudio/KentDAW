/*
  ==============================================================================

   This file is part of the eJUCE library
   which is based on Raw Material Software ltd. JUCE

   eJUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   eJUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
   Boston, MA 02111-1307 USA
   
   @author Asnaghi Lucio

  ==============================================================================
*/

#ifndef __EJUCE_TIMELINESYSTEM__
#define __EJUCE_TIMELINESYSTEM__


//==============================================================================
class TimelineSystem;
class SliceActionChain;
class SliceActionSynchronized;


//==============================================================================
typedef float (*TransitionCallback) (float);

class TransitionLinear {
public:
	static float stepToNextFrame (float framePosition) {
		return framePosition;
	}
};

class TransitionSinusoidal {
public:
	static float stepToNextFrame (float framePosition) {
//		return (-cos (framePosition*float_Pi)/2.0f) + 0.5f; // can easily replace
		return (-costable.lookup (framePosition*float_Pi)/2.0f) + 0.5f;
	}
};

class TransitionCircular {
public:
	static float stepToNextFrame (float framePosition) {
		return pow((-costable.lookup (framePosition*float_Pi)/2.0f) + 0.5f, 0.2f);
	}
};

class TransitionPlastic {
public:
	static float stepToNextFrame (float framePosition) {
		return pow((-costable.lookup (framePosition*float_Pi)/2.0f) + 0.5f, 0.5f);
	}
};

class TransitionCubic {
public:
	static float stepToNextFrame (float framePosition) {
		return exp(log(framePosition));
	}
};


//==============================================================================
class SliceAction
{
public:
	SliceAction () {}
	virtual ~SliceAction () {}

	virtual void firstFrame (int frameCount,int frameDuration) = 0;
	virtual void lastFrame () = 0;
	virtual void stepToNextFrame (float framePosition) = 0;

protected:
	friend class SliceActionChain;

	int frameCount;
	int currentFrame;
	TransitionCallback transition;
};

class SlicePause : public SliceAction
{
public:
	virtual void firstFrame (int frameCount,int frameDuration) {}
	virtual void lastFrame () {}
	virtual void stepToNextFrame (float framePosition) {}
};


//==============================================================================
class SliceActionChain
{
public:

	SliceActionChain();
	virtual ~SliceActionChain();

	void addAction (SliceAction* actionToAdd,
					int durationInMilliseconds,
					TransitionCallback transition = TransitionLinear::stepToNextFrame);

	void addPause (int durationInMilliseconds);

	void play ();
	void stop ();
	void stepToNextFrame ();

	void setFrameDuration (int milliseconds);

protected:
	friend class SliceActionSynchronized;

	void startToPlaySlice (SliceAction* playingSlice);

	OwnedArray<SliceAction> serialActions;
	SliceActionSynchronized* chainHolder;

	bool isPlaying;
	int currentAction;
	int frameDurationInMilliseconds;
};


//==============================================================================
class SliceActionSynchronized
{
public:

	SliceActionSynchronized (TimelineSystem* timeline);
	~SliceActionSynchronized ();

	void addChain (SliceActionChain* chainToAdd);
	bool isStillPlaying();

protected:
	friend class SliceActionChain;
	friend class TimelineSystem;

	void play ();
	void stop ();
	void stepToNextFrame ();
	void checkIfTimelineIsToStop ();

	OwnedArray<SliceActionChain> parallelChains;
	TimelineSystem* timeline;
};


//==============================================================================
class TimelineSystem : public Timer
{
public:

	TimelineSystem (float timeSmoothFactor=1.0f, int loopCount=1);
	~TimelineSystem ();

	void addChain (SliceActionChain* chainToAdd);

	void play ();
	void stop ();

	void timerCallback ();

protected:
	friend class SliceActionSynchronized;
	SliceActionSynchronized* timelineActions;

	void internalPlay ();
	void internalStop ();
	void checkIfTimelineIsToStop ();

	float timeSmoothFactor;
	int frameDurationInMilliseconds;
	int direction;

	int loopNumber;
	int currentLoopCount;
};


#endif // __EJUCE_TIMELINESYSTEM__ 
