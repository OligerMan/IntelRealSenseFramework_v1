#pragma once

// std includes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Intel RealSense includes
#include "pxcsession.h"
#include "pxccapturemanager.h"
#include "pxccapture.h"
#include "pxchandmodule.h"
#include "pxchanddata.h"
#include "pxcmetadata.h"
#include "service/pxcsessionservice.h"

#include "RealSense/HandCursor/CursorConfiguration.h"
#include "RealSense/HandCursor/CursorData.h"
#include "RealSense/HandCursor/HandCursorModule.h"


#include "Point.h"


class RealSenseGestureManager {


	// constant borders for hand position (left handed)

	const double lMinX = 0.05;
	const double lMaxX = 0.25;
	const double lMinY = -0.10;
	const double lMaxY = 0.10;
	const double lMinZ = 0.25;
	const double lMaxZ = 0.50;

	// constant borders for hand position (right handed)

	const double rMinX = -0.25;
	const double rMaxX = 0.00;
	const double rMinY = -0.10;
	const double rMaxY = 0.10;
	const double rMinZ = 0.25;
	const double rMaxZ = 0.50;

	// demo borders


	double min_x = 200;
	double max_x = 550;
	double min_y = 130;
	double max_y = 380;
	double min_z = 0;
	double max_z = 0;


	// Intel RS system object pointers
	PXCSession  * pxcSession;
	PXCSenseManager * senseManager;
	PXCHandModule * handAnalizer;
	PXCHandConfiguration * config;
	PXCHandData * handData;
	PXCHandData::IHand * handInfo;

	Intel::RealSense::Session * RSSession;
	Intel::RealSense::SenseManager * cursorSenseManager;
	Intel::RealSense::HandCursor::CursorData * cursorAnalysis;
	Intel::RealSense::HandCursor::HandCursorModule * handCursorAnalyzer;
	Intel::RealSense::HandCursor::CursorConfiguration * configCursor;

	// RealSenseGestureManager own info classes
	std::vector<std::string> gestureBuffer[2];
	Point prevHandCoors[2];
	Point handCoors[2];

	void updateHandInfo() {

		std::swap(prevHandCoors, handCoors);
		handData->Update();
		cursorAnalysis->Update();

		int gestureAmount = handData->QueryFiredGesturesNumber();

		for (int i = 0; i < gestureAmount; i++) {

			PXCHandData::GestureData gestureData;
			if (handData->QueryFiredGestureData(i, gestureData) == PXC_STATUS_NO_ERROR) {

				
				if (handData->QueryHandDataById(gestureData.handId, handInfo) == PXC_STATUS_NO_ERROR) {
					int handSide;
					if (handInfo->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_LEFT) {
						handSide = 0;
					}
					else if (handInfo->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_RIGHT) {
						handSide = 1;
					}
					std::wstring wstr = gestureData.name;
					std::string str = std::string(wstr.begin(), wstr.end());
					gestureBuffer[handSide].push_back(str);
				}
			}
		}

		int32_t num_of_hands = cursorAnalysis->QueryNumberOfCursors();
		if (num_of_hands == 0) {
			handCoors[0].x = 0;
			handCoors[0].y = 0;
			handCoors[0].z = 0;
			handCoors[1].x = 0;
			handCoors[1].y = 0;
			handCoors[1].z = 0;
		}
		for (int32_t i = 0; i < num_of_hands; i++) {

			Intel::RealSense::HandCursor::CursorData::ICursor * cursor_info;

			if (cursorAnalysis->QueryCursorData(Intel::RealSense::HandCursor::CursorData::AccessOrderType::ACCESS_ORDER_BY_TIME, i, cursor_info) == Intel::RealSense::STATUS_NO_ERROR) {
				Intel::RealSense::Point3DF32 position_point = cursor_info->QueryCursorImagePoint();

				if (cursor_info->QueryBodySide() == Intel::RealSense::HandCursor::CursorData::BodySideType::BODY_SIDE_LEFT) {
					handCoors[0].x = position_point.x;
					handCoors[0].y = position_point.y;
					handCoors[0].z = position_point.z;
				}
				else if (cursor_info->QueryBodySide() == Intel::RealSense::HandCursor::CursorData::BodySideType::BODY_SIDE_LEFT) {
					handCoors[1].x = position_point.x;
					handCoors[1].y = position_point.y;
					handCoors[1].z = position_point.z;
				}
			}
		}

	}

	void configGestureManager() {

		config->SetTrackingMode(PXCHandData::TRACKING_MODE_FULL_HAND);
		config->EnableNormalizedJoints(true);
		config->EnableAllAlerts();
		config->EnableSegmentationImage(true);
		config->EnableAllGestures(true);
		config->SetSmoothingValue(1);

		config->DisableGesture(L"fist");
		config->DisableGesture(L"full_pinch");
		config->DisableGesture(L"spreadfingers");
		config->DisableGesture(L"wave");
		config->ApplyChanges();
	}

public:

	RealSenseGestureManager() {
		pxcSession = Intel::RealSense::Session::CreateInstance();
		senseManager = pxcSession->CreateSenseManager();
		senseManager->EnableHand(0);
		senseManager->EnableHandCursor(0);

		//RSSession = Intel::RealSense::Session::CreateInstance();
		//cursorSenseManager = RSSession->CreateSenseManager();
		//cursorSenseManager->EnableHand(0);
		handCursorAnalyzer = senseManager->QueryHandCursor();
		cursorAnalysis = handCursorAnalyzer->CreateOutput();
		configCursor = handCursorAnalyzer->CreateActiveConfiguration();

		if (configCursor) {
			configCursor->DisableAllAlerts();
			configCursor->DisableAllGestures();
			configCursor->ApplyChanges();
		}

		handAnalizer = senseManager->QueryHand();
		handData = handAnalizer->CreateOutput();
		config = handAnalizer->CreateActiveConfiguration();
		configGestureManager();
		senseManager->Init();
		
	};

	void processFrame() {
		senseManager->AcquireFrame(false);
		updateHandInfo();
		senseManager->ReleaseFrame();
	}

	enum handSide {
		leftHand, 
		rightHand
	};

	//Point convertCoors(Point input, handSide handSide, Point maxParam) {
	//	Point output = input;

	Point convertCoors(Point origin, Point max_size) {
		origin.x = std::max(origin.x - min_x, 0.0);
		origin.y = std::max(origin.y - min_y, 0.0);
		origin.x = std::min(max_x - min_x, origin.x);
		origin.y = std::min(max_y - min_y, origin.y);
		origin.x *= max_size.x / (max_x - min_x);
		origin.y *= max_size.y / (max_y - min_y);
		origin.x = max_size.x - origin.x;
		return origin;
	}

	Point getHandPosition(handSide handSide, Point maxParam) {
		return convertCoors(handCoors[handSide]/*, handSide*/, maxParam);
	}

	Point getHandSpeed(handSide handSide, Point maxParam) {
		double speedLimit = (maxParam.getLength() / 3);
		
		Point output = convertCoors(handCoors[handSide]/*, handSide*/, maxParam) - 
						 convertCoors(prevHandCoors[handSide]/*, handSide*/, maxParam);
		
		double dist = output.getLength();
		if (dist > speedLimit) {
			output.x = 0;
			output.y = 0;
			output.z = 0;
		}
		return output;
	}

	std::vector<std::string> getGesturesVector(handSide handSide) {
		return gestureBuffer[handSide];
	}

	std::string getLastGesture(handSide handSide) {
		if (gestureBuffer[handSide].size() == 0) {
			return "nothing";
		}
		else {
			std::string output = gestureBuffer[handSide][gestureBuffer[handSide].size() - 1];
			gestureBuffer[handSide].pop_back();
			return output;
		}
	}
};