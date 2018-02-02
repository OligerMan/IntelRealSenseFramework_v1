#include <iostream>
#include <Windows.h>

#include "RealSenseGestureManager.h"

using namespace std;

int main() {
	cout << "Test module for Intel RealSense Cursor Mode Framework started" << endl;

	RealSenseGestureManager rsManager;
	std::string lastLeftGesture = "nothing";
	std::string lastRightGesture = "nothing";

	int cnter = 0;

	while (true) {
		rsManager.processFrame();
		Point3D handPos[2];
		handPos[0] = rsManager.getHandPosition(rsManager.leftHand);
		handPos[1] = rsManager.getHandPosition(rsManager.rightHand);

		//cout << "Left hand position: x:" << handPos[0].x << " y:" << handPos[0].y << " z:" << handPos[0].z << endl;
		//cout << "Right hand position: x:" << handPos[1].x << " y:" << handPos[1].y << " z:" << handPos[1].z << endl;

		std::string currentLeftGesture = rsManager.getLastGesture(rsManager.leftHand);
		std::string currentRightGesture = rsManager.getLastGesture(rsManager.rightHand);
		if (currentLeftGesture != "nothing") {
			lastLeftGesture = currentLeftGesture;
			cout << "Current left-handed gesture is: " << lastLeftGesture << endl;
		}
		if (currentRightGesture != "nothing") {
			lastRightGesture = currentRightGesture;
			cout << "Current right-handed gesture is: " << lastRightGesture << endl;
		}

		if (cnter % 60 == 0) {
			cout << cnter << endl;
		}
		cnter++;

		//std::vector<std::pair<int, std::string>> gestVector = rsManager.getGesturesVector();

		/*for (int i = 0; i < gestVector.size(); i++) {
			cout << "Gesture number " << i << " fired by " << gestVector[i].first << " hand:" << gestVector[i].second << endl;
		}*/
	}

}