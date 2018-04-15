/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Image.h"

namespace Intel {
    namespace RealSense {

            namespace HandCursor {
                /**
                @class PXCCursorData
                @brief This class holds all the output of the hand cursor tracking process.

                Each instance of this class holds the information of a specific frame.
                */
                class CursorData : public Base
                {
                public:
                    /* Constants */
                    PXC_CUID_OVERWRITE(PXC_UID('C', 'H', 'D', 'T'));

                    /* Enumerations */

                    /** @enum BodySideType
                    The side of the body to which a hand belongs.\n
                    @note Body sides are reported from the player's point-of-view, not the sensor's.
                    */
                    enum BodySideType {
                        /// The side was not determined    
                        BODY_SIDE_UNKNOWN = 0
                        , BODY_SIDE_LEFT            /// Left side of the body    
                        , BODY_SIDE_RIGHT           /// Right side of the body
                    };


                    /**
                    @enum AccessOrderType
                    Orders in which the hands can be accessed.
                    */
                    enum AccessOrderType {
                        /// From oldest to newest hand in the scene 
                        ACCESS_ORDER_BY_TIME
                        , ACCESS_ORDER_NEAR_TO_FAR        /// From nearest to farthest hand in scene
                        , ACCESS_ORDER_RIGHT_TO_LEFT      /// Right to Left hands        
                    };


                    /**
                    @enum AlertType
                    */
                    enum AlertType {
                        ///  Cursor is detected
                        CURSOR_DETECTED = 0x000001
                        , CURSOR_NOT_DETECTED = 0x000002           ///  A previously detected cursor is lost
                        , CURSOR_INSIDE_BORDERS = 0x000004      ///  Cursor is outside of the tracking boundaries
                        , CURSOR_OUT_OF_BORDERS = 0x000008      ///  Cursor has moved back inside the tracking boundaries   
                        , CURSOR_TOO_CLOSE = 0x000010      ///  Cursor is too far
                        , CURSOR_TOO_FAR = 0x000020        ///  Cursor is too close     
                        , CURSOR_OUT_OF_LEFT_BORDER = 0x000040      ///  The tracked object is touching the left border of the field of view
                        , CURSOR_OUT_OF_RIGHT_BORDER = 0x000080      ///  The tracked object is touching the right border of the field of view
                        , CURSOR_OUT_OF_TOP_BORDER = 0x000100      ///  The tracked object is touching the upper border of the field of view
                        , CURSOR_OUT_OF_BOTTOM_BORDER = 0x000200      ///  The tracked object is touching the lower border of the field of view
                        , CURSOR_ENGAGED = 0x000400        ///     The cursor entered engagement state and ready to interact with the application
                        , CURSOR_DISENGAGED = 0x000800        ///  The cursor has left the screen bounds or the engagement mode state
                    };


                    /**
                    @enum GestureType
                    */
                    enum GestureType {
                        // Cursor click - hold your hand facing the camera, close and open your hand in smooth motion. 
                        CURSOR_CLICK = 0x000001
                        , CURSOR_CLOCKWISE_CIRCLE = 0x000002           // Cursor clockwise circle  - move your hand in clockwise circle while hand facing the camera.
                        , CURSOR_COUNTER_CLOCKWISE_CIRCLE = 0x000004      // Cursor counter clockwise circle  - move your hand in counter clockwise circle while hand facing the camera.
                        , CURSOR_HAND_CLOSING = 0x000008        // Cursor hand closing - hold an open hand towards the camera and close your hand.
                        , CURSOR_HAND_OPENING = 0x000010        // Cursor hand opening - hold a closed hand towards the camera and open your hand.
                    };

                    /* Data Structures */

                    /**
                    @struct AlertData
                    Defines the properties of an alert event
                    */
                    struct AlertData
                    {
                        /// The time-stamp in which the event occurred
                        int64_t              timeStamp;
                        int32_t              frameNumber;       /// The number of the frame in which the event occurred (relevant for recorded sequences)
                        int32_t              handId;            /// The ID of the hand that triggered the alert, if relevant and known        
                        AlertType           label;             /// The type of alert

                    };

                    /**
                    @struct GestureData
                    Defines the properties of a gesture.
                    */
                    struct GestureData
                    {
                        /// Time-stamp in which the gesture occurred
                        int64_t              timeStamp;
                        int32_t              frameNumber;       /// The number of the frame in which the gesture occurred (relevant for recorded sequences)            
                        int32_t              handId;            /// The ID of the hand that made the gesture, if relevant and known     
                        GestureType          label;             /// The type of gesture        
                    };

                    /**
                    @struct TrackingBounds
                    Defines the properties of a tracking bounds.
                    */
                    struct TrackingBounds
                    {
                        //nearest tracking distance (distance of small frustum base from sensor)
                        float nearTrackingDistance;
                        float farTrackingDistance; //farthest tracking distance (distance of large frustum base from sensor)
                        float nearTrackingWidth;    //width of small frustum base
                        float nearTrackingHeight;    //height of small frustum base
                    };

                    /* Interfaces */



                    /**
                    @class ICursor
                    Contains hand cursor data
                    */
                    class ICursor
                    {
                    public:

                        /**
                        @brief Return the hand's unique identifier.
                        */
                        virtual int32_t PXCAPI QueryUniqueId() const = 0;

                        /**
                        @brief Return the time-stamp in which the collection of the data was completed.
                        */
                        virtual int64_t PXCAPI QueryTimeStamp() const = 0;

                        /**
                        @brief Return the side of the body to which the hand belongs (when known).
                        @see BodySideType
                        */
                        virtual BodySideType PXCAPI QueryBodySide() const = 0;

                        /**
                        @brief Get the geometric position of the cursor in 3D world coordinates, in meters.
                        @return the cursor point in world coordinates.
                        */
                        virtual Point3DF32 PXCAPI QueryCursorWorldPoint() const = 0;

                        /**
                        @brief Get the geometric position of the cursor in 2D image coordinates, in pixels. (Note: the Z coordinate is the point's depth in millimeters.)
                        @return the cursor point in image coordinates.
                        */
                        virtual Point3DF32 PXCAPI QueryCursorImagePoint() const = 0;

                        /**
                        @brief The module defines a bounding box around a hand in the world coordinate system, the adaptive point is a normalized point inside the bounding box with values between 0-1.
                        Using this point allows an easy way to map the hand cursor to any resolution screen.
                        @return the a 3D point with values between 0-1.
                        */
                        virtual Point3DF32 PXCAPI QueryAdaptivePoint() const = 0;

                        /**
                        @brief Get the hand cursor engagement loading percentage.
                        @return 100 - percent indicates full engagement state.
                        @return -1  - percent indicates that the feature wasn't enabled.

                        @see PXCCursorConfiguration::EnableEngagement
                        @see AlertType::CURSOR_ENGAGED
                        @see AlertType::CURSOR_DISENGAGED
                        */
                        virtual int32_t PXCAPI QueryEngagementPercent() const = 0;

                    };


                public:
                public:
                    /* General */

                    /**
                    @brief Updates hand data to the most current output.
                    */
                    virtual Status PXCAPI Update() = 0;

                    /* Alerts Outputs */

                    /**
                    @brief Return the number of fired alerts in the current frame.
                    */
                    virtual int32_t PXCAPI QueryFiredAlertsNumber(void) const = 0;

                    /**
                    @brief Get the details of the fired alert with the given index.

                    @param[in] index - the zero-based index of the requested fired alert.
                    @param[out] alertData - the information for the fired event.

                    @note the index is between 0 and the result of QueryFiredAlertsNumber()

                    @return PXC_STATUS_NO_ERROR - operation succeeded.
                    @return PXC_STATUS_PARAM_UNSUPPORTED - invalid input parameter.

                    @see CursorAlertData
                    @see QueryFiredAlertsNumber
                    */
                    virtual Status PXCAPI QueryFiredAlertData(int32_t index, AlertData & alertData) const = 0;

                    /**
                    @brief Return whether the specified alert is fired for a specific hand in the current frame, and retrieve its data.

                    @param[in] alertEvent - the alert type.
                    @param[out] alertData - the information for the fired event.
                    @return true if the alert is fired, false otherwise.

                    @see AlertType
                    @see CursorAlertData

                    */
                    virtual bool32_t PXCAPI IsAlertFired(AlertType alertEvent, AlertData & alertData) const = 0;


                    /**
                    @brief Return whether the specified alert is fired for a specific hand in the current frame, and retrieve its data.

                    @param[in] alertEvent - the alert type.
                    @param[in] handID - the ID of the hand whose alert should be retrieved.
                    @param[out] alertData - the information for the fired event.
                    @return true if the alert is fired, false otherwise.

                    @see AlertType
                    @see CursorAlertData

                    */
                    virtual bool32_t PXCAPI IsAlertFiredByHand(AlertType alertEvent, int32_t handID, AlertData & alertData) const = 0;

                    /* Gestures Outputs */

                    /**
                    @brief Return the number of gestures fired in the current frame.
                    */
                    virtual int32_t PXCAPI QueryFiredGesturesNumber(void) const = 0;

                    /**
                    @brief Get the details of the fired gesture with the given index.

                    @param[in] index - the zero-based index of the requested fired gesture.
                    @param[out] gestureData - the information for the fired gesture.

                    @note The gesture index must be between 0 and [QueryFiredGesturesNumber() - 1]

                    @return PXC_STATUS_NO_ERROR - operation succeeded.
                    @return PXC_STATUS_PARAM_UNSUPPORTED - invalid input parameter.

                    @see CursorGestureData
                    @see QueryFiredGesturesNumber
                    */
                    virtual Status PXCAPI QueryFiredGestureData(int32_t index, GestureData & gestureData) const = 0;


                    /**
                    @brief Return whether the specified gesture is fired for a specific hand in the current frame, and if so retrieve its data.
                    @param[in] gestureEvent - the gesture type.
                    @param[out] gestureData - the information for the fired gesture.

                    @return true if the gesture was fired, false otherwise.

                    @see GestureType
                    @see CursorGestureData
                    */
                    virtual bool32_t PXCAPI IsGestureFired(GestureType gestureEvent, GestureData & gestureData) const = 0;


                    /**
                    @brief Return whether the specified gesture is fired for a specific hand in the current frame, and if so retrieve its data.
                    @param[in] gestureEvent - the gesture type.
                    @param[in] handID - the ID of the hand whose alert should be retrieved.
                    @param[out] gestureData - the information for the fired gesture.

                    @return true if the gesture was fired, false otherwise.

                    @see GestureType
                    @see CursorGestureData
                    */
                    virtual bool32_t PXCAPI IsGestureFiredByHand(GestureType gestureEvent, int32_t handID, GestureData & gestureData) const = 0;


                    /* Cursors Outputs */

                    /**
                    @brief Return the number of hands detected in the current frame.
                    */
                    virtual int32_t PXCAPI QueryNumberOfCursors(void) const = 0;

                    /**
                    @brief Retrieve the cursor object data using a specific AccessOrder and related index.

                    @param[in] accessOrder - the order in which the cursors are enumerated (accessed).
                    @param[in] index - the index of the cursor to be retrieved, based on the given AccessOrder.
                    @param[out] cursorData - the information for the cursor.

                    @return PXC_STATUS_NO_ERROR - operation succeeded.
                    @return PXC_STATUS_DATA_UNAVAILABLE  - index >= number of detected cursors.

                    @see AccessOrder
                    @see ICursor
                    */
                    virtual Status PXCAPI QueryCursorData(AccessOrderType accessOrder, int32_t index, ICursor *& cursorData) const = 0;

                    /**
                    @brief Retrieve the cursor object data by its unique Id.
                    @param[in] cursorID - the unique ID of the requested cursor.
                    @param[out] cursorData - the information for the cursor.

                    @return PXC_STATUS_NO_ERROR - operation succeeded.
                    @return PXC_STATUS_DATA_UNAVAILABLE  - there is no output data.
                    @return PXC_STATUS_PARAM_UNSUPPORTED - there is no data for the given cursor ID.

                    @see ICursor
                    */
                    virtual Status PXCAPI QueryCursorDataById(int32_t cursorID, ICursor *& cursorData) const = 0;




                    /**
                    @brief Reset the adaptive point.
                    @param[in] resetPosition - the position of the new point. should be between 0-1 in every axis.
                    @param[in] cursorID - the unique ID of the requested cursor.

                    @return PXC_STATUS_NO_ERROR - operation succeeded.
                    @return PXC_STATUS_PARAM_UNSUPPORTED - invalid input parameter.
                    */
                    virtual Status PXCAPI ResetAdaptiveById(int32_t cursorID, Point3DF32 resetPosition) const = 0;


                };

                typedef CursorData::BodySideType BodySideType;
                typedef CursorData::AccessOrderType AccessOrderType;
                typedef CursorData::AlertType AlertType;
                typedef CursorData::GestureType GestureType;
                typedef CursorData::AlertData AlertData;
                typedef CursorData::GestureData GestureData;
                typedef CursorData::TrackingBounds TrackingBounds;
                typedef CursorData::ICursor ICursor;

                /** Operator | for alertType labels */
                static inline AlertType operator|(AlertType a, AlertType b)
                {
                    return static_cast<AlertType>(static_cast<int32_t>(a) | static_cast<int32_t>(b));
                }

                /** Operator | for gestureType labels */
                static inline GestureType operator|(GestureType a, GestureType b)
                {
                    return static_cast<GestureType>(static_cast<int32_t>(a) | static_cast<int32_t>(b));
                }
            }
        }
    }
