#pragma once

// std includes
#include <iostream>
#include <string>
#include <vector>

// Intel RealSense includes

#include "RealSense/SenseManager.h"
#include "RealSense/Capture.h"
#include "RealSense/VideoModule.h"

#include "RealSense/HandCursor/CursorConfiguration.h"
#include "RealSense/HandCursor/CursorData.h"
#include "RealSense/HandCursor/HandCursorModule.h"

// custom includes

#include "Point.h";



class RealSenseHandCursor {

	Intel::RealSense::Session * rs_session;
	Intel::RealSense::SenseManager * sense_manager;
	Intel::RealSense::HandCursor::HandCursorModule * hand_cursor_module;
	Intel::RealSense::HandCursor::CursorData * cursor_data;
	Intel::RealSense::HandCursor::CursorConfiguration * config_cursor;

	Intel::RealSense::Point3DF32 hand_pos[2];

	double min_x = 200;
	double max_x = 550;
	double min_y = 130;
	double max_y = 380;
	double min_z = 0;
	double max_z = 0;

public:

	RealSenseHandCursor() {

		rs_session = Intel::RealSense::Session::CreateInstance();
		sense_manager = rs_session->CreateSenseManager();
		sense_manager->EnableHandCursor(0);

		hand_cursor_module = sense_manager->QueryHandCursor();
		cursor_data = hand_cursor_module->CreateOutput();
		config_cursor = hand_cursor_module->CreateActiveConfiguration();

		if (config_cursor) {
			config_cursor->DisableAllAlerts();
			config_cursor->DisableAllGestures();
			config_cursor->ApplyChanges();
		}

		sense_manager->Init();
	}

	void processFrame() {
		sense_manager->AcquireFrame(false);
		cursor_data->Update();

		int32_t num_of_hands = cursor_data->QueryNumberOfCursors();
		if (num_of_hands == 0) {
			hand_pos[0].x = 0;
			hand_pos[0].y = 0;
			hand_pos[0].z = 0;
			hand_pos[1].x = 0;
			hand_pos[1].y = 0;
			hand_pos[1].z = 0;
		}
		for (int32_t i = 0; i < num_of_hands; i++) {

			Intel::RealSense::HandCursor::CursorData::ICursor * cursor_info;

			if (cursor_data->QueryCursorData(Intel::RealSense::HandCursor::CursorData::AccessOrderType::ACCESS_ORDER_BY_TIME, i, cursor_info) == Intel::RealSense::STATUS_NO_ERROR) {
				Intel::RealSense::Point3DF32 position_point = cursor_info->QueryCursorImagePoint();
				
				if (cursor_info->QueryBodySide() == Intel::RealSense::HandCursor::CursorData::BodySideType::BODY_SIDE_LEFT) {
					hand_pos[0] = position_point;
				}else if (cursor_info->QueryBodySide() == Intel::RealSense::HandCursor::CursorData::BodySideType::BODY_SIDE_LEFT) {
					hand_pos[1] = position_point;
				}
			}
		}

		sense_manager->ReleaseFrame();
	}

	Point convertCoors(Point origin, Point max_size) {
		origin.x = max(origin.x - min_x, 0);
		origin.y = max(origin.y - min_y, 0);
		origin.x = min(max_x - min_x, origin.x);
		origin.y = min(max_y - min_y, origin.y);
		origin.x *= max_size.x / (max_x - min_x);
		origin.y *= max_size.y / (max_y - min_y);
		origin.x = max_size.x - origin.x;
		return origin;
	}

	Point getHandPosition(int index, Point max_size) {
		Point output;
		output.x = hand_pos[index].x;
		output.y = hand_pos[index].y;
		return convertCoors(output, max_size);
	}
};