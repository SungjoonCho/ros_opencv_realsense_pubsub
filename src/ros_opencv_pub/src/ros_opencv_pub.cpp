#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <librealsense2/rs.hpp>
#include <sstream>
#include <image_transport/image_transport.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_opencv_pub");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  rs2::pipeline pipe;
  rs2::config cfg;
  rs2::frameset frames;
  rs2::frame color_frame;

  cv_bridge::CvImage img_bridge;
  sensor_msgs::Image img_msg;



  cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
  pipe.start(cfg);

  for(int i=0; i < 30; i ++)
  {
    frames = pipe.wait_for_frames();
  }

//  namedWindow("Display Imagee", WINDOW_AUTOSIZE);

  ros::Rate loop_rate(30);

  uint counter = 0;

  while(ros::ok())
  {
    cv::Mat dst_127, dst_bgr;

    frames = pipe.wait_for_frames();
    color_frame = frames.get_color_frame();
    Mat color(Size(640,480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

    // first, imshow original image
//    imshow("Original image", color);

    // second, publishing image after edge detection

//    cv::Canny(color, dst_127, 100, 127, 3, false);
//    cv::cvtColor(dst_127, dst_bgr, cv::COLOR_GRAY2BGR);

//    std_msgs::Header header; // empty header
//    header.seq = counter; // user defined counter
//    header.stamp = ros::Time::now(); // time
//    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, dst_bgr);
//    img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image
//    pub.publish(img_msg); // ros::Publisher pub_img = node.advertise<sensor_msgs::Image>("topic", queuesize);




    // second, publishing original image

    std_msgs::Header header; // empty header
    header.seq = counter; // user defined counter
    header.stamp = ros::Time::now(); // time
    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, color);
    img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image
    pub.publish(img_msg); // ros::Publisher pub_img = node.advertise<sensor_msgs::Image>("topic", queuesize);




    cout << counter << " frame published" << endl;
    counter++;

    if(waitKey(10)==27) break;
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}


