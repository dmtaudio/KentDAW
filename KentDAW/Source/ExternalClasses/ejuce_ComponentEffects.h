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

#ifndef __EJUCE_COMPONENTEFFECTS__
#define __EJUCE_COMPONENTEFFECTS__


/*

//==============================================================================
class ShowBubbleAction : public TimerizedAction
{
public:
	ShowBubbleAction( const String& message_, int x_, int y_ ) :
		message(message_),
		x(x_),
		y(y_)
	{
		bubble = new BubbleMessageComponent();
		bubble->addToDesktop(0);
	}

	~ShowBubbleAction()
	{
		delete bubble;
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		bubble->showAt (x,y,message,frameCount * frameDuration,false,false);
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition) {}

protected:

	BubbleMessageComponent* bubble;
	String message;
	int x, y;
};


//==============================================================================
class ComponentEffectVisibility : public TimerizedAction
{
public:
	ComponentEffectVisibility( Component* owner_, const bool visible_ ) :
		owner(owner_),
		shouldBeVisible(visible_)
	{
	}

	void firstFrame (int frameCount,int frameDuration) {}

	void lastFrame ()
	{
		owner->setVisible (shouldBeVisible);
	}

	void stepToNextFrame (float framePosition) {}

protected:

	Component* owner;
	bool shouldBeVisible;
};


//==============================================================================
class ComponentEffectFadeout : public TimerizedAction
{
public:
	ComponentEffectFadeout( Component* owner_ ) :
		owner(owner_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		owner->fadeOutComponent (frameCount*frameDuration);
	}

	void lastFrame () {}

	void stepToNextFrame (float framePosition) {}

protected:

	Component* owner;
};


//==============================================================================
class ComponentEffectPosition : public TimerizedAction
{
public:
	ComponentEffectPosition( Component* owner_, const Point& position_ ) :
		owner(owner_),
		position(position_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerPosition = Point((float)owner->getX(),(float)owner->getY());

		deltaX = position.getX() - initialOwnerPosition.getX();
		deltaY = position.getY() - initialOwnerPosition.getY();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		float x = initialOwnerPosition.getX() + (int)(deltaX * framePosition);
		float y = initialOwnerPosition.getY() + (int)(deltaY * framePosition);

		owner->setTopLeftPosition ((int)x, (int)y);
	}


protected:

	Component* owner;
	Point initialOwnerPosition;

	Point position;

	float deltaX;
	float deltaY;
};


//==============================================================================
class ComponentEffectSize : public TimerizedAction
{
public:
	ComponentEffectSize( Component* owner_, const int width_, const int height_ ) :
		owner(owner_),
		width(width_),
		height(height_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerSize = owner->getBounds();

		deltaW = (float)(width - initialOwnerSize.getWidth());
		deltaH = (float)(height - initialOwnerSize.getHeight());
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		owner->setSize (
			initialOwnerSize.getWidth() + (int)(deltaW * framePosition),
			initialOwnerSize.getHeight() + (int)(deltaH * framePosition) );
	}


protected:

	Component* owner;
	Rectangle initialOwnerSize;

	int width, height;

	float deltaW;
	float deltaH;
};


//==============================================================================
class ComponentEffectBounds : public TimerizedAction
{
public:
	ComponentEffectBounds(	Component* owner_, const Rectangle& bound_ ) :
		owner(owner_),
		bound(bound_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerSize = owner->getBounds();

		deltaX = (float)( bound.getX() - initialOwnerSize.getX() );
		deltaY = (float)( bound.getY() - initialOwnerSize.getY() );
		deltaW = (float)( bound.getWidth() - initialOwnerSize.getWidth() );
		deltaH = (float)( bound.getHeight() - initialOwnerSize.getHeight() );
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		owner->setBounds (
			initialOwnerSize.getX() + (int)(deltaX * framePosition),
			initialOwnerSize.getY() + (int)(deltaY * framePosition),
			initialOwnerSize.getWidth() + (int)(deltaW * framePosition),
			initialOwnerSize.getHeight() + (int)(deltaH * framePosition) );
	}

protected:

	Component* owner;
	Rectangle initialOwnerSize;

	Rectangle bound;

	float deltaX;
	float deltaY;
	float deltaW;
	float deltaH;
};


//==============================================================================
class ComponentEffectRelativeSize : public TimerizedAction
{
public:
	ComponentEffectRelativeSize( Component* owner_, const float deltaWidth, const float deltaHeight ) :
		owner(owner_),
		delta(deltaWidth,deltaHeight)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		deltaW = delta.getX() - 1.0f;
		deltaH = delta.getY() - 1.0f;

		initialOwnerSize = owner->getBounds();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		int currentWidth = (int)(initialOwnerSize.getWidth() * (1.0f + deltaW * framePosition));
		int currentHeight = (int)(initialOwnerSize.getHeight() * (1.0f + deltaH * framePosition));
		if (currentWidth < 1) currentWidth = 1;
		if (currentHeight < 1) currentHeight = 1;

		int currentLeft = initialOwnerSize.getX() + (initialOwnerSize.getWidth() - currentWidth) / 2;
		int currentTop = initialOwnerSize.getY() + (initialOwnerSize.getHeight() - currentHeight) / 2;

		owner->setBounds (
			currentLeft,
			currentTop,
			currentWidth,
			currentHeight );
	}

protected:

	Component* owner;
	Rectangle initialOwnerSize;

	Point delta;
	float deltaW;
	float deltaH;
};


//==============================================================================
class WindowEffectColour : public TimerizedAction
{
public:
	WindowEffectColour(	ResizableWindow* owner_, const Colour& color_ ) :
		owner(owner_),
		color(color_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initial = owner->getBackgroundColour();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		// weirdo 8bit overflow... must change here !
		Colour current(
			initial.getRed() + (uint8)((color.getRed() - initial.getRed()) * framePosition),
			initial.getGreen() + (uint8)((color.getGreen() - initial.getGreen()) * framePosition),
			initial.getBlue() + (uint8)((color.getBlue() - initial.getBlue()) * framePosition)
		);

		owner->setBackgroundColour (current);
	}


protected:

	ResizableWindow* owner;

	Colour initial;
	Colour color;
};


*/











//==============================================================================
class ShowBubbleAction : public SliceAction
{
public:
	ShowBubbleAction( const String& message_, int x_, int y_ ) :
		message(message_),
		x(x_),
		y(y_)
	{
		bubble = new BubbleMessageComponent();
		bubble->addToDesktop(0);
	}

	~ShowBubbleAction()
	{
		delete bubble;
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		bubble->showAt (x,y,message,frameCount * frameDuration,false,false);
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition) {}

protected:

	BubbleMessageComponent* bubble;
	String message;
	int x, y;
};


//==============================================================================
class ComponentEffectVisibility : public SliceAction
{
public:
	ComponentEffectVisibility( Component* owner_, const bool visible_ ) :
		owner(owner_),
		shouldBeVisible(visible_)
	{
	}

	void firstFrame (int frameCount,int frameDuration) {}

	void lastFrame ()
	{
		owner->setVisible (shouldBeVisible);
	}

	void stepToNextFrame (float framePosition) {}

protected:

	Component* owner;
	bool shouldBeVisible;
};


//==============================================================================
class ComponentEffectFadeout : public SliceAction
{
public:
	ComponentEffectFadeout( Component* owner_ ) :
		owner(owner_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		owner->fadeOutComponent (frameCount*frameDuration);
	}

	void lastFrame () {}

	void stepToNextFrame (float framePosition) {}

protected:

	Component* owner;
};


//==============================================================================
class ComponentEffectPosition : public SliceAction
{
public:
	ComponentEffectPosition( Component* owner_, const Point& position_ ) :
		owner(owner_),
		position(position_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerPosition = Point((float)owner->getX(),(float)owner->getY());

		deltaX = position.getX() - initialOwnerPosition.getX();
		deltaY = position.getY() - initialOwnerPosition.getY();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		float x = initialOwnerPosition.getX() + (int)(deltaX * framePosition);
		float y = initialOwnerPosition.getY() + (int)(deltaY * framePosition);

		owner->setTopLeftPosition ((int)x, (int)y);
	}


protected:

	Component* owner;
	Point initialOwnerPosition;

	Point position;

	float deltaX;
	float deltaY;
};


//==============================================================================
class ComponentEffectSize : public SliceAction
{
public:
	ComponentEffectSize( Component* owner_, const int width_, const int height_ ) :
		owner(owner_),
		width(width_),
		height(height_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerSize = owner->getBounds();

		deltaW = (float)(width - initialOwnerSize.getWidth());
		deltaH = (float)(height - initialOwnerSize.getHeight());
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		owner->setSize (
			initialOwnerSize.getWidth() + (int)(deltaW * framePosition),
			initialOwnerSize.getHeight() + (int)(deltaH * framePosition) );
	}


protected:

	Component* owner;
	Rectangle initialOwnerSize;

	int width, height;

	float deltaW;
	float deltaH;
};


//==============================================================================
class ComponentEffectBounds : public SliceAction
{
public:
	ComponentEffectBounds(	Component* owner_, const Rectangle& bound_ ) :
		owner(owner_),
		bound(bound_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initialOwnerSize = owner->getBounds();

		deltaX = (float)( bound.getX() - initialOwnerSize.getX() );
		deltaY = (float)( bound.getY() - initialOwnerSize.getY() );
		deltaW = (float)( bound.getWidth() - initialOwnerSize.getWidth() );
		deltaH = (float)( bound.getHeight() - initialOwnerSize.getHeight() );
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		owner->setBounds (
			initialOwnerSize.getX() + (int)(deltaX * framePosition),
			initialOwnerSize.getY() + (int)(deltaY * framePosition),
			initialOwnerSize.getWidth() + (int)(deltaW * framePosition),
			initialOwnerSize.getHeight() + (int)(deltaH * framePosition) );
	}

protected:

	Component* owner;
	Rectangle initialOwnerSize;

	Rectangle bound;

	float deltaX;
	float deltaY;
	float deltaW;
	float deltaH;
};


//==============================================================================
class ComponentEffectRelativeSize : public SliceAction
{
public:
	ComponentEffectRelativeSize( Component* owner_, const float deltaWidth, const float deltaHeight ) :
		owner(owner_),
		delta(deltaWidth,deltaHeight)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		deltaW = delta.getX() - 1.0f;
		deltaH = delta.getY() - 1.0f;

		initialOwnerSize = owner->getBounds();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		int currentWidth = (int)(initialOwnerSize.getWidth() * (1.0f + deltaW * framePosition));
		int currentHeight = (int)(initialOwnerSize.getHeight() * (1.0f + deltaH * framePosition));
		if (currentWidth < 1) currentWidth = 1;
		if (currentHeight < 1) currentHeight = 1;

		int currentLeft = initialOwnerSize.getX() + (initialOwnerSize.getWidth() - currentWidth) / 2;
		int currentTop = initialOwnerSize.getY() + (initialOwnerSize.getHeight() - currentHeight) / 2;

		owner->setBounds (
			currentLeft,
			currentTop,
			currentWidth,
			currentHeight );
	}

protected:

	Component* owner;
	Rectangle initialOwnerSize;

	Point delta;
	float deltaW;
	float deltaH;
};


//==============================================================================
class WindowEffectColour : public SliceAction
{
public:
	WindowEffectColour(	ResizableWindow* owner_, const Colour& color_ ) :
		owner(owner_),
		color(color_)
	{
	}

	void firstFrame (int frameCount,int frameDuration)
	{
		initial = owner->getBackgroundColour();
	}

	void lastFrame ()
	{
	}

	void stepToNextFrame (float framePosition)
	{
		// weirdo 8bit overflow... must change here !
		Colour current(
			initial.getRed() + (uint8)((color.getRed() - initial.getRed()) * framePosition),
			initial.getGreen() + (uint8)((color.getGreen() - initial.getGreen()) * framePosition),
			initial.getBlue() + (uint8)((color.getBlue() - initial.getBlue()) * framePosition)
		);

		owner->setBackgroundColour (current);
	}


protected:

	ResizableWindow* owner;

	Colour initial;
	Colour color;
};






#endif // __EJUCE_COMPONENTEFFECTS__ 
