// Example of using Kalman Filter for tracking
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Initialize Kalman Filter
    cv::KalmanFilter KF(4, 2, 0);
    KF.transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
    cv::setIdentity(KF.measurementMatrix);
    cv::setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));
    cv::setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-1));
    cv::setIdentity(KF.errorCovPost, cv::Scalar::all(1));

    // Initialize state and measurement
    cv::Mat state(4, 1, CV_32F);
    cv::Mat measurement(2, 1, CV_32F);
    state << 0, 0, 0, 0; // Initial x, y, dx, dy

    // Your video capture loop
    cv::VideoCapture cap("input_video.mp4");
    while (true) {
        cv::Mat frame;
        bool bSuccess = cap.read(frame);
        if (!bSuccess) {
            break;
        }

        // Object detection and bounding box extraction (using your chosen method)
        // For this example, let's assume you have the bounding box 'bbox' for the tracked object
        cv::Rect bbox = ...;
        measurement << bbox.x + bbox.width / 2, bbox.y + bbox.height / 2;

        // Update Kalman Filter
        KF.correct(measurement);
        KF.predict();

        // Get the estimated state
        state = KF.statePost;
        float x = state.at<float>(0);
        float y = state.at<float>(1);

        // Visualization
        cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2);
        cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        cv::imshow("Tracking", frame);
        char key = (char)cv::waitKey(1);
        if (key == 27) break;
    }
    return 0;
}