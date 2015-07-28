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

#include "../basics/ejuce_StandardHeader.h"


BEGIN_EJUCE_NAMESPACE

#include "ejuce_TimelineSystem.h"


//==============================================================================
SliceActionChain::SliceActionChain() :
	frameDurationInMilliseconds(25),
	currentAction(0),
	isPlaying(false)
{
}

SliceActionChain::~SliceActionChain()
{
}

void SliceActionChain::addAction (SliceAction* actionToAdd,
									int durationInMilliseconds,
									TransitionCallback transition)
{
	actionToAdd->frameCount = jmax(1, durationInMilliseconds / frameDurationInMilliseconds);
	actionToAdd->currentFrame = 0;
	actionToAdd->transition = transition;

	serialActions.add (actionToAdd);
}

void SliceActionChain::addPause (int durationInMilliseconds)
{
	SlicePause* actionToAdd = new SlicePause();
	actionToAdd->frameCount = jmax(1, durationInMilliseconds / frameDurationInMilliseconds);
	actionToAdd->currentFrame = 0;
	actionToAdd->transition = TransitionLinear::stepToNextFrame;

	serialActions.add (actionToAdd);
}

void SliceActionChain::play ()
{
	if (!isPlaying && serialActions.size() > 0)
	{
		currentAction = 0;

		SliceAction* playingSlice = serialActions.getUnchecked (currentAction);

		startToPlaySlice (playingSlice);

		isPlaying = true;
	}
}

void SliceActionChain::stop ()
{
	if (isPlaying)
	{
		SliceAction* playingSlice = serialActions.getUnchecked (currentAction);

		playingSlice->lastFrame();

		isPlaying = false;

		chainHolder->checkIfTimelineIsToStop();
	}
}

void SliceActionChain::stepToNextFrame ()
{
	SliceAction* playingSlice = serialActions.getUnchecked (currentAction);

	// this can be optimized a bit by not dividing every time
	float framePosition =
		playingSlice->transition( playingSlice->currentFrame / (float) (playingSlice->frameCount-1) );

	// this is actually the
	playingSlice->stepToNextFrame (framePosition);

	if (++(playingSlice->currentFrame) >= playingSlice->frameCount)
	{
		++currentAction;

		// current action is further than last one
		if (currentAction >= serialActions.size())
		{
			currentAction = serialActions.size() - 1;
			stop();
		}
		else
		// current action is a good one
		{
			// finish the previous
			playingSlice->lastFrame();

			// start with the new one
			playingSlice = serialActions.getUnchecked (currentAction);

			startToPlaySlice (playingSlice);
		}
	}
}

void SliceActionChain::startToPlaySlice (SliceAction* playingSlice)
{
	playingSlice->currentFrame = 0;
	playingSlice->firstFrame(playingSlice->frameCount, frameDurationInMilliseconds);
}

void SliceActionChain::setFrameDuration(int milliseconds)
{
	frameDurationInMilliseconds = milliseconds;
}


//==============================================================================
SliceActionSynchronized::SliceActionSynchronized (TimelineSystem* timeline_) :
	timeline (timeline_)
{
}

SliceActionSynchronized::~SliceActionSynchronized ()
{
}

void SliceActionSynchronized::addChain (SliceActionChain* chainToAdd)
{
	chainToAdd->chainHolder = this;
	parallelChains.add (chainToAdd);
}

void SliceActionSynchronized::play ()
{
	for (int i=0; i<parallelChains.size(); i++ )
	{
		SliceActionChain* actionChain = parallelChains.getUnchecked (i);
		if (!actionChain->isPlaying)
			actionChain->play ();
	}
}

void SliceActionSynchronized::stop ()
{
	for (int i=0; i<parallelChains.size(); i++ )
	{
		SliceActionChain* actionChain = parallelChains.getUnchecked (i);
		if (actionChain->isPlaying)
			actionChain->stop ();
	}
}

void SliceActionSynchronized::stepToNextFrame()
{
	for (int i=0; i<parallelChains.size(); i++ )
	{
		SliceActionChain* actionChain = parallelChains.getUnchecked (i);
		if (actionChain->isPlaying)
			actionChain->stepToNextFrame ();
	}
}

bool SliceActionSynchronized::isStillPlaying()
{
	bool isAChainStillPlaying = false;
	for (int i=0; i<parallelChains.size(); i++ )
	{
		SliceActionChain* actionChain = parallelChains.getUnchecked (i);
		if (actionChain->isPlaying) {
			isAChainStillPlaying = true;
			break;
		}
	}

	return isAChainStillPlaying;
}

void SliceActionSynchronized::checkIfTimelineIsToStop()
{
	bool isAChainStillPlaying = false;
	for (int i=0; i<parallelChains.size(); i++ )
	{
		SliceActionChain* actionChain = parallelChains.getUnchecked (i);
		if (actionChain->isPlaying) {
			isAChainStillPlaying = true;
			break;
		}
	}

	if (!isAChainStillPlaying)
		timeline->checkIfTimelineIsToStop();
}


//==============================================================================
TimelineSystem::TimelineSystem (float timeSmoothFactor_, int loopCount_) :
	timelineActions(0),
	loopNumber(loopCount_),
	timeSmoothFactor(timeSmoothFactor_)
{
	frameDurationInMilliseconds = jmax(10, (int)(25 * (1.0f/timeSmoothFactor)));

	timelineActions = new SliceActionSynchronized(this);
}

TimelineSystem::~TimelineSystem ()
{
	if (timelineActions)
		delete timelineActions;
}

void TimelineSystem::addChain (SliceActionChain* chainToAdd)
{
	chainToAdd->setFrameDuration (frameDurationInMilliseconds);

	timelineActions->addChain (chainToAdd);
}

void TimelineSystem::play()
{
	if (!timelineActions->isStillPlaying())
	{
		currentLoopCount = loopNumber;

		timelineActions->play();

		internalPlay ();
	}
}

void TimelineSystem::stop()
{
	timelineActions->stop ();

	internalStop ();
}

void TimelineSystem::checkIfTimelineIsToStop()
{
	if (--currentLoopCount > 0 )
		timelineActions->play();
	else
		internalStop();
}

void TimelineSystem::internalPlay()
{
	startTimer (frameDurationInMilliseconds);
}

void TimelineSystem::internalStop()
{
	if (isTimerRunning())
		stopTimer();
}

void TimelineSystem::timerCallback()
{
	timelineActions->stepToNextFrame ();
}


END_EJUCE_NAMESPACE