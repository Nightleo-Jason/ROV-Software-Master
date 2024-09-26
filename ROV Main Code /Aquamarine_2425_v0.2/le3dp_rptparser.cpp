#include "le3dp_rptparser.h"
//#include "Arduino.h"

GamePadEventData ReadingPad;

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
	joyEvents(evt)
{}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
	}
	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
	ReadingPad = *evt;
}

int JoystickEvents::getJoyX(){
	return ReadingPad.x;
}

int JoystickEvents::getJoyY(){
	return ReadingPad.y;
}

int JoystickEvents::getHat(){
	return ReadingPad.hat;
}

int JoystickEvents::getTwist(){
	return ReadingPad.twist;
}

int JoystickEvents::getBA(){
	return ReadingPad.buttons_a;
}

int JoystickEvents::getBB(){
	return ReadingPad.buttons_b;
}

int JoystickEvents::getSlider(){
	return ReadingPad.slider;
}
