
## ROS에서 Realsense camera 영상을 OpenCV 이용하여 publish 후 subscriber가 edge detection 후 영상 출력

## Setting

<pre>
OS : Ubuntu 18.04
ROS Version : melodic
Realsense SDK 2.0 Version : 2.42.0 
Realsense Camera D435i 사용 
</pre>


## 순서

<pre>
1. catkin package 모두 작성 후 한 workspace 내에 pub용 패키지, 노드(cpp) 작성 (publish용 노드 1개)

2. 노드 코드
    Realsense 카메라로 컬러 영상 프레임 획득
    각 프레임의 matrix data 얻어서 “color” mat로 생성
    cv_bridge를 이용하여 각 프레임 mat를 sensor_msgs로 변환
    변환된 결과인 sensor_msgs를 "camera/image" topic으로 publish

3. 동일 프로젝트 내에 sub용 패키지, 노드(cpp) 작성 
    (subscribe용 노드 1개)

4. 같은 "camera/image" topic 경로로 subscribe

5. 받은 msg를 mono8(grayscale)로 변환

6. Canny edge detector로 에지 추출 후 cv::imshow

※ roscore, build(catkin_make), source ./devel/setup.bash 잊지 말기

7-1. 노드 1개씩 실행시에는 rosrun 패키지 노드
 
7-2. 노드 한번에 실행시에는 [패키지] – [launch] - launch 파일 작성
    pub과 sub 노드 launch 모두 가능하도록 작성
    실행 : roslaunch 패키지 launch파일.launch
</pre>




## ROS에서 Realsense camera 영상을 OpenCV 이용하여 egde detection 후 Rviz에 띄우기

<pre>
1. 프로젝트, 패키지, 노드(cpp) 작성 (publish용 노드 1개) 

2. 노드 코드

    a. Realsense 카메라로 컬러 영상 프레임 획득

    b. 각 프레임의 matrix data 얻어서 “color” mat로 생성
    
    c. 각 mat를 canny edge detector 함수 이용해 에지 추출

    d. 에지 결과는 1채널 grayscale 이므로 3채널인 bgr로 변환

    e. cv_bridge를 이용하여 CV mat를 sensor_msgs로 변환

    f. 변환된 결과인 sensor_msgs를 topic으로 publish

3. Rviz 실행 : $rviz

4. 왼쪽 하단 [Add] – [Image] OK

5. 왼쪽 메뉴바 [Image] – [Image Topic] – [topic 경로] enter

※ roscore, build(catkin_make), source ./devel/setup.bash 잊지 말기
</pre>

