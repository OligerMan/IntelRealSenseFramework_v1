#include <iostream>

#include "RealSenseGestureManager.h"
#include "WinInterface.h"
#include "GestureHandler.h"


// SFML includes
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace std;


bool stop = false;



std::vector<bool> last_left_gestures(100); 
std::vector<bool> last_right_gestures(100);

void processWinAPI(std::vector<bool> left_gestures, std::vector<bool> right_gestures) {

	if (left_gestures[nothing]) {
		if (right_gestures[tap]) {
			mouseLeftButtonClick();
		}
		if (right_gestures[two_fingers_pinch_open] && !last_right_gestures[two_fingers_pinch_open]) {
			mouseLeftButtonDown();
		}
		if (!right_gestures[two_fingers_pinch_open] && last_right_gestures[two_fingers_pinch_open]) {
			mouseLeftButtonUp();
		}
		if (right_gestures[thumb_up]) {
			mouseWheelScrollUp();
		}
		if (right_gestures[thumb_down]) {
			mouseWheelScrollDown();
		}
	}

	if (left_gestures[thumb_up]) {
		if (right_gestures[thumb_up]) {
			stop = true;
		}
		if (right_gestures[tap]) {
			mouseRightButtonClick();
		}
	}
	
	if (left_gestures[v_sign] && !last_left_gestures[v_sign]) {
		altKeyDown();
	}

	if (!left_gestures[v_sign] && last_left_gestures[v_sign]) {
		altKeyUp();
	}

	if (left_gestures[v_sign]) {
		if (right_gestures[tap]) {
			tabKeyClick();
		}
	}

	if (left_gestures[two_fingers_pinch_open]) {
		if (right_gestures[tap]) {
			mouseLeftButtonClick();
			Sleep(keypress_delay_ms);
			mouseLeftButtonClick();
		}
	}

	last_left_gestures = left_gestures;
	last_right_gestures = right_gestures;
}


int main() {
	cout << "Test module for Intel RealSense Cursor Mode Framework started" << endl;


	RealSenseGestureManager rsManager;
	GestureHandler gest_handler;

	std::string lastLeftGesture = "nothing";
	std::string lastRightGesture = "nothing";

	int cnter = 0;

	Point maxPosition(1920,1080,1);
	Point sensivity(640, 480, 1);
	Point handSpeed[2];
	Point handCoors[2];
	Point absolCoors[2];
	Point currentPosition[2];

	bool is_button_pressed = true;

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	while (!stop) {
		rsManager.processFrame();
		handCoors[0] = rsManager.getHandPosition(rsManager.leftHand, maxPosition);
		handCoors[1] = rsManager.getHandPosition(rsManager.rightHand, maxPosition);


		SetCursorPos(handCoors[0].x, handCoors[0].y);

		std::string currentLeftGesture = rsManager.getLastGesture(rsManager.leftHand);
		std::string currentRightGesture = rsManager.getLastGesture(rsManager.rightHand);

		gest_handler.handleGestures(currentLeftGesture, currentRightGesture);
		processWinAPI(gest_handler.getLeftGestures(), gest_handler.getRightGestures());

		if (currentRightGesture != "nothing") {
			lastRightGesture = currentRightGesture;
			cout << "Current right-handed gesture is: " << lastRightGesture << endl;
		}

		if (currentLeftGesture != "nothing") {
			lastLeftGesture = currentLeftGesture;
			cout << "Current left-handed gesture is: " << lastLeftGesture << endl;
		}

		if (cnter % 60 == 0) {
			cout << cnter << endl;
		}
		cnter++;
	}

}