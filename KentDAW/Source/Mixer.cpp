#include "Mixer.h"

// CONSTRUCTOR
//==============================================================================
Mixer::Mixer ()
{
    addAndMakeVisible (mixerSlider = new Slider ("mixerSlider"));
    mixerSlider->setRange (0, 128, 0);
    mixerSlider->setSliderStyle (Slider::LinearVertical);
    mixerSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mixerSlider->addListener (this);
    
    addAndMakeVisible (trackLabel = new Label ("trackLabel",
                                               TRANS("Track")));
    trackLabel->setFont (Font (15.00f, Font::plain));
    trackLabel->setJustificationType (Justification::centredLeft);
    trackLabel->setEditable (false, false, false);
    trackLabel->setColour (TextEditor::textColourId, Colours::black);
    trackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (inputCombo = new ComboBox ("inputCombo"));
    inputCombo->setEditableText (false);
    inputCombo->setJustificationType (Justification::centredLeft);
    inputCombo->setTextWhenNothingSelected (String::empty);
    inputCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    inputCombo->addItem (TRANS("synth"), 1);
    inputCombo->addItem (TRANS("audio"), 2);
    inputCombo->addSeparator();
    inputCombo->addListener (this);
    
    // Set Size
    setSize (200, 600);
}

// DESTRUCTOR
//==============================================================================
Mixer::~Mixer()
{
    mixerSlider = nullptr;
    trackLabel = nullptr;
    inputCombo = nullptr;
}

//==============================================================================
void Mixer::sineWave()
{
    // varying sine wave for testing
    for(x = 0; x < BUFFER_LENGTH; x++)
    {
        buffer[x] = sin(1000 * (2 * PI) * x / SR);
    }
}

void Mixer::paint (Graphics& g)
{
    // Set Background Colour
    g.fillAll (Colours::grey);
}

void Mixer::resized()
{
    // Set Component Bounds
    mixerSlider->setBounds (24, 88, 150, 420);
    trackLabel->setBounds (72, 520, 56, 24);
    inputCombo->setBounds (24, 24, 150, 24);
}

void Mixer::sliderValueChanged (Slider* sliderThatWasMoved)
{
    // Slider Changed Listener
    if (sliderThatWasMoved == mixerSlider)
    {
        // add code
    }
}

void Mixer::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    // Input Combo Listener
    if (comboBoxThatHasChanged == inputCombo)
    {
        // add code
    }
    
}


//==============================================================================
#if 0
/*  -- Introjucer information section --
 
 This is where the Introjucer stores the metadata that describe this GUI layout, so
 make changes in here at your peril!
 
 BEGIN_JUCER_METADATA
 
 <JUCER_COMPONENT documentType="Component" className="Mixer" componentName="" parentClasses="public Component"
 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="200"
 initialHeight="600">
 <BACKGROUND backgroundColour="ffffffff"/>
 <SLIDER name="mixerSlider" id="790728f495e7666f" memberName="mixerSlider"
 virtualName="" explicitFocusOrder="0" pos="24 88 150 424" min="0"
 max="10" int="0" style="LinearVertical" textBoxPos="TextBoxBelow"
 textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
 <LABEL name="trackLabel" id="7d76532b7957ccb3" memberName="trackLabel"
 virtualName="" explicitFocusOrder="0" pos="72 520 56 24" edTextCol="ff000000"
 edBkgCol="0" labelText="Track" editableSingleClick="0" editableDoubleClick="0"
 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
 bold="0" italic="0" justification="33"/>
 <COMBOBOX name="inputCombo" id="a598aff47d90557" memberName="inputCombo"
 virtualName="" explicitFocusOrder="0" pos="24 24 150 24" editable="0"
 layout="33" items="synth&#10;audio&#10;" textWhenNonSelected=""
 textWhenNoItems="(no choices)"/>
 </JUCER_COMPONENT>
 
 END_JUCER_METADATA
 */
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

