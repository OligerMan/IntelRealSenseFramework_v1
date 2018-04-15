#pragma once

#include <vector>

enum Gestures {
	nothing,
	v_sign,
	two_fingers_pinch_open,
	full_pinch,
	swipe_up,
	swipe_left,
	swipe_down,
	swipe_right,
	tap,
	click,
	thumb_up,
	thumb_down
};

class GestureHandler {

	std::vector<int> static_gest_index{
		v_sign,
		two_fingers_pinch_open,
		full_pinch,
		thumb_up,
		thumb_down
	};

	const int delay_const = 5;

	std::vector<std::pair<int, std::string>> gesture_info_left{
		std::pair<int, std::string>(0, "nothing"),
		std::pair<int, std::string>(0, "v_sign"),
		std::pair<int, std::string>(0, "two_fingers_pinch_open"),
		std::pair<int, std::string>(0, "full_pinch"),
		std::pair<int, std::string>(-1, "swipe_up"),
		std::pair<int, std::string>(-1, "swipe_left"),
		std::pair<int, std::string>(-1, "swipe_down"),
		std::pair<int, std::string>(-1, "swipe_right"),
		std::pair<int, std::string>(-1, "tap"),
		std::pair<int, std::string>(-1, "click"),
		std::pair<int, std::string>(-1, "thumb_up"),
		std::pair<int, std::string>(-1, "thumb_down")
	};

	std::vector<std::pair<int, std::string>> gesture_info_right{
		std::pair<int, std::string>(0, "nothing"),
		std::pair<int, std::string>(0, "v_sign"),
		std::pair<int, std::string>(0, "two_fingers_pinch_open"),
		std::pair<int, std::string>(0, "full_pinch"),
		std::pair<int, std::string>(-1, "swipe_up"),
		std::pair<int, std::string>(-1, "swipe_left"),
		std::pair<int, std::string>(-1, "swipe_down"),
		std::pair<int, std::string>(-1, "swipe_right"),
		std::pair<int, std::string>(-1, "tap"),
		std::pair<int, std::string>(-1, "click"),
		std::pair<int, std::string>(-1, "thumb_up"),
		std::pair<int, std::string>(-1, "thumb_down")
	};

	std::vector<bool> gesture_buffer[2];


	bool isStatic(int index) {
		for (int i = 0; i < static_gest_index.size(); i++) {
			if (static_gest_index[i] == index) {
				return true;
			}
		}
		return false;
	}

	void infoDecrement() {
		for (int i = 1; i < gesture_info_left.size(); i++) {
			gesture_info_left[i].first--;
		}
		for (int i = 1; i < gesture_info_right.size(); i++) {
			gesture_info_right[i].first--;
		}
	}

	int getIndex(std::string input) {
		for (int i = 0; i < gesture_info_left.size(); i++) {
			if (input == gesture_info_left[i].second) {
				return i;
			}
		}
		return -1;
	}

public:

	GestureHandler() {
		gesture_buffer[0].resize(gesture_info_left.size());
		gesture_buffer[1].resize(gesture_info_right.size());
	}

	void handleGestures(std::string left_gesture, std::string right_gesture) {

		for (int i = 1; i < gesture_info_left.size(); i++) {
			if (gesture_info_left[i].second == left_gesture) {
				gesture_info_left[i].first = delay_const;
			}
		}
		for (int i = 1; i < gesture_info_right.size(); i++) {
			if (gesture_info_right[i].second == right_gesture) {
				gesture_info_right[i].first = delay_const;
			}
		}

		bool left_nothing = true;
		bool right_nothing = true;

		for (int i = 1; i < gesture_info_left.size(); i++) {
			if (isStatic(i)) {
				if (gesture_info_left[i].first > 0) {
					gesture_buffer[0][getIndex(gesture_info_left[i].second)] = true;
					left_nothing = false;
				}
				else {
					gesture_buffer[0][getIndex(gesture_info_left[i].second)] = false;
				}
			}
			else {
				if (gesture_info_left[i].first == 0) {
					gesture_buffer[0][getIndex(gesture_info_left[i].second)] = true;
					left_nothing = false;
				}
				else {
					gesture_buffer[0][getIndex(gesture_info_left[i].second)] = false;
				}
			}
		}
		gesture_buffer[0][nothing] = left_nothing;
		for (int i = 1; i < gesture_info_right.size(); i++) {
			if (isStatic(i)) {
				if (gesture_info_right[i].first > 0) {
					gesture_buffer[1][getIndex(gesture_info_left[i].second)] = true;
					right_nothing = false;
				}
				else {
					gesture_buffer[1][getIndex(gesture_info_left[i].second)] = false;
				}
			}
			else {
				if (gesture_info_right[i].first == 0) {
					gesture_buffer[1][getIndex(gesture_info_left[i].second)] = true;
					right_nothing = false;
				}
				else {
					gesture_buffer[1][getIndex(gesture_info_left[i].second)] = false;
				}
			}
		}
		gesture_buffer[1][nothing] = right_nothing;

		infoDecrement();
	}

	std::vector<bool> getLeftGestures() {

		return gesture_buffer[0];
	}

	std::vector<bool> getRightGestures() {
		
		return gesture_buffer[1];
	}
};