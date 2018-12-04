

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace dlib;
using namespace std;

#include <android/log.h>

#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

// ----------------------------------------------------------------------------------------

uchar * test_faced() {
    try {

        frontal_face_detector detector = get_frontal_face_detector();

        shape_predictor sp;
        deserialize("/sdcard/dlibfolder/shape_predictor_68_face_landmarks.dat") >> sp;


//         Loop over all the images provided on the command line.
        array2d<rgb_pixel> img;
        load_image(img, "/sdcard/dlibfolder/header.png");
        const rectangle &rectOri = get_rect(img);
        pyramid_up(img);
        const rectangle &rectUp = get_rect(img);
        float scalY = rectUp.bottom() / rectOri.bottom();
        float scalX = rectUp.right() / rectOri.right();
        LOGD("%f == %f",scalY, scalX);

        cv::Mat temp;
        temp=cv::imread("/sdcard/dlibfolder/header.png",cv::IMREAD_UNCHANGED);
        // Now tell the face detector to give us a list of bounding boxes
        // around all the faces in the image.
        std::vector<rectangle> dets = detector(img);

        std::vector<full_object_detection> shapes;
        for (unsigned long j = 0; j < dets.size(); ++j) {
            full_object_detection shape = sp(img, dets[j]);
            shapes.push_back(shape);
        }

        if (!shapes.empty()) {
            for (int i = 0; i < 68; i++) {
                LOGD("%d == %d",shapes[0].part(i).x(), shapes[0].part(i).y());
                //bgr
                circle(temp, cvPoint(static_cast<int>(shapes[0].part(i).x() / scalX), static_cast<int>(shapes[0].part(i).y() / scalY)), 1, cv::Scalar(0, 0, 255, 255), 1, cv::LINE_AA, 0);
            }
        }


        return temp.data;
    }
    catch (exception &e) {
        LOGD("\nexception thrown!");
        LOGD("%s", e.what());
    }
}

// ----------------------------------------------------------------------------------------

