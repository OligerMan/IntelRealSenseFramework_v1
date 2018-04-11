#include <iostream>

#include "RealSenseGestureManager.h"
#include "WinInterface.h"


// SFML includes
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace std;


bool stop = false;

// counters
int mouse_press_cnter = 0;
int alt_press_cnter = 0;
int left_tap_cnter = 0;
int right_tap_cnter = 0;
int right_button_cnter = 0;
int double_click_cnter = 0;


//void handleGestures(std::string left_gesture, std::string right_gesture) {
//
//	if (right_gesture == "two_fingers_pinch_open") {
//		if (mouse_press_cnter < 0) {
//			mouseLeftButtonDown();
//		}
//		mouse_press_cnter = 4;
//	}
//
//	if (right_gesture == "thumb_up") {
//		mouseWheelScrollUp();
//		if (left_gesture == "thumb_up") {
//			stop = true;
//		}
//	}
//
//	if (right_gesture == "thumb_down") {
//		mouseWheelScrollDown();
//	}
//
//	if (right_gesture == "tap") {
//		if (alt_press_cnter < 0 && right_tap_cnter < 0) {
//			mouseLeftButtonClick();
//			right_tap_cnter = 1;
//		}
//		else if(alt_press_cnter >= 0){
//			tabKeyClick();
//		}
//	}
//		
//	if (left_gesture == "two_fingers_pinch_open") {
//		double_click_cnter = 5;
//	}	
//
//	if (double_click_cnter > 0) {
//		if (right_gesture == "tap") {	
//			mouseLeftButtonClick();
//			Sleep(keypress_delay_ms);
//			mouseLeftButtonClick();
//		}
//	}
//
//	if (left_gesture == "v_sign") {
//		if (alt_press_cnter < 0) {
//			altKeyDown();
//		}
//		alt_press_cnter = 10;
//	}
//
//	if (right_gesture == "click" && right_button_cnter < 0) {
//		mouseRightButtonClick();
//		right_button_cnter = 1;	
//	}
//
//	if (left_gesture == "swipe_up") {
//		arrowUpClick();
//	}
//
//	if (left_gesture == "swipe_left") {
//		arrowLeftClick();
//	}
//
//	if (left_gesture == "swipe_down") {
//		arrowDownClick();
//	}
//
//	if (left_gesture == "swipe_right") {
//		arrowRightClick();
//	}
//
//	if (alt_press_cnter == 0) {
//		altKeyUp();
//	}
//
//	if (mouse_press_cnter == 0) {
//		mouseLeftButtonUp();
//	}
//
//	alt_press_cnter--;
//	mouse_press_cnter--;
//	right_tap_cnter--;
//	left_tap_cnter--;
//	right_button_cnter--;
//	double_click_cnter--;
//}

void handleGestures(std::string left_gesture, std::string right_gesture) {

	if (right_gesture == "two_fingers_pinch_open") {
		if (mouse_press_cnter < 0) {
			mouseLeftButtonDown();
		}
		mouse_press_cnter = 4;
	}

	if (mouse_press_cnter == 0) {
		mouseLeftButtonUp();
	}

	if (right_gesture == "thumb_up") {
		mouseWheelScrollUp();
		if (left_gesture == "thumb_up") {
			stop = true;
		}
	}

	if (right_gesture == "thumb_down") {
		mouseWheelScrollDown();
	}

	if (left_gesture == "v_sign") {
		if (alt_press_cnter < 0) {
			altKeyDown();
		}
		alt_press_cnter = 10;
	}

	if (right_gesture == "tap") {
		if (alt_press_cnter < 0 && right_tap_cnter < 0) {
			mouseLeftButtonClick();
			right_tap_cnter = 1;
		}
		else if (alt_press_cnter >= 0) {
			tabKeyClick();
		}
	}

	if (left_gesture == "two_fingers_pinch_open") {
		double_click_cnter = 5;
	}

	if (double_click_cnter > 0) {
		if (right_gesture == "tap") {
			mouseLeftButtonClick();
			Sleep(keypress_delay_ms);
			mouseLeftButtonClick();
		}
	}


	if (right_gesture == "click" && right_button_cnter < 0) {
		mouseRightButtonClick();
		right_button_cnter = 1;
	}

	if (left_gesture == "swipe_up") {
		arrowUpClick();
	}

	if (left_gesture == "swipe_left") {
		arrowLeftClick();
	}

	if (left_gesture == "swipe_down") {
		arrowDownClick();
	}

	if (left_gesture == "swipe_right") {
		arrowRightClick();
	}

	if (right_gesture == "swipe_up") {
		enterKeyClick();
	}

	if (right_gesture == "swipe_down") {
		escapeKeyClick();
	}

	if (alt_press_cnter == 0) {
		altKeyUp();
	}


	alt_press_cnter--;
	mouse_press_cnter--;
	right_tap_cnter--;
	left_tap_cnter--;
	right_button_cnter--;
	double_click_cnter--;
}

int main() {
	cout << "Test module for Intel RealSense Cursor Mode Framework started" << endl;


	RealSenseGestureManager rsManager;
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

		handleGestures(currentLeftGesture, currentRightGesture);

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