#pragma once

// std includes
#include <iostream>
#include <string>
#include <vector>

// Intel RealSense includes
#include "pxcsession.h"
#include "pxccapturemanager.h"
#include "pxccapture.h"
#include "pxchandmodule.h"
#include "pxchanddata.h"
#include "pxcmetadata.h"
#include "service/pxcsessionservice.h"


struct Point3D {
	double x = 0,
		y = 0,
		z = 0;

	void setCoordinates(PXCHandData::JointData input_coors) {
		x = input_coors.positionWorld.x;
		y = input_coors.positionWorld.y;
		z = input_coors.positionWorld.z;
	}
};

class RealSenseGestureManager {


	// Intel RS system object pointers
	PXCSession  * pxcSession;
	PXCSenseManager * senseManager;
	PXCHandModule * handAnalizer;
	PXCHandConfiguration * config;
	PXCHandData * handData;
	PXCHandData::IHand * handInfo;

	// RealSenseGestureManager own info classes
	std::vector<std::pair<int, std::string>> gestureBuffer;
	Point3D handCoors[2];


	void updateHandInfo() {
		if (handData != nullptr) {
			handData->Update();
		}
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
					gestureBuffer.push_back(std::pair<int, std::string>(handSide, str));
				}
			}
		}

		pxcI32 numberOfHands = handData->QueryNumberOfHands();

		for (pxcI32 i = 0; i < numberOfHands; i++) {
			if (handData->QueryHandData(PXCHandData::AccessOrderType::ACCESS_ORDER_BY_TIME, i, handInfo) == PXC_STATUS_NO_ERROR) {
				PXCHandData::JointData handCoordinates;
				handInfo->QueryNormalizedJoint(PXCHandData::JointType::JOINT_CENTER, handCoordinates);
				if (handInfo->QueryBodySide() == Intel::RealSense::Hand::BodySideType::BODY_SIDE_LEFT) {
					handCoors[0].setCoordinates(handCoordinates);
				}
				else if (handInfo->QueryBodySide() == Intel::RealSense::Hand::BodySideType::BODY_SIDE_RIGHT) {
					handCoors[1].setCoordinates(handCoordinates);
				}
			}
		}

	}

	void configGestureManager() {
		config->SetTrackingMode(PXCHandData::TRACKING_MODE_FULL_HAND);
		config->EnableNormalizedJoints(true);
		config->EnableAllGestures();
		/*config->DisableGesture(L"swipe_up");
		config->DisableGesture(L"swipe_down");
		config->DisableGesture(L"swipe_left");
		config->DisableGesture(L"swipe_right");*/
		config->DisableGesture(L"fist");
		config->DisableGesture(L"spreadfingers");
		config->DisableGesture(L"wave");
		config->ApplyChanges();
	}

public:
	RealSenseGestureManager() {
		pxcSession = PXCSession::CreateInstance();
		senseManager = pxcSession->CreateSenseManager();
		senseManager->EnableHand();
		senseManager->Init();
		handAnalizer = senseManager->QueryHand();
		handData = handAnalizer->CreateOutput();
		config = handAnalizer->CreateActiveConfiguration();
		configGestureManager();
		
	};

	void processFrame() {
		senseManager->AcquireFrame(true);
		updateHandInfo();
		senseManager->ReleaseFrame();
	}

	enum handSide {
		leftHand, 
		rightHand
	};

	Point3D getHandPosition(handSide handSide) {
		return handCoors[handSide];
	}

	std::vector<std::pair<int, std::string>> getGesturesVector() {
		return gestureBuffer;
	}
};