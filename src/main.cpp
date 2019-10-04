/*
 * main.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: eduardo
 */

#include <iostream>
#include <opencv2/opencv.hpp>



using namespace cv;
using namespace std;


Mat maskImg(Mat srcImageIn, Size size){

	Mat maskin;
	Mat mask;


	cvtColor(srcImageIn, maskin, COLOR_BGR2GRAY);

	resize(maskin, mask, size);
	bitwise_not(mask,mask);




	return mask;
}




int main(){
	//Mat image = imread("./src/IMG_3105.JPG");
	//Mat image2;
	//Mat glasses = imread("./src/sunglass.jpg");
	/*if(!image.data){
		cout<<"no read"<<endl;
		return -1;
	}


	namedWindow("image",WINDOW_AUTOSIZE);
	cvtColor(image,image2,COLOR_BGR2GRAY);

	Size size(373,70); //This is just the size I want the glasses to be (same as region of interest)

	resize(glasses,glasses,size); //I am resizing the glasses to the dimensions of "size" which I declared
	//in the last line

	Rect roi(1120,840,373,70);//Making my region of interest as a rectangle
	//(top corner x coordinate, top corner y coordinate, width, height)

	Mat img_roi = image(roi);//Making my area of interest on the specific picture I want it to be in

	glasses.copyTo(img_roi);//putting my glasses picture into the area of interest in the picture I want it
	//to be in

	imshow("image",image);
	waitKey();

	cout<<"Run"<<endl;
	cout<<image.size<<endl;
	*/
	Mat frame;
	Mat frame2;
	String face_cascade_name = "./src/haarcascade_frontalface_default.xml";
	String glass_name = "./src/sunglass.jpg";
	CascadeClassifier classifier;

	VideoCapture capture;

	if (!classifier.load(face_cascade_name)){
		cout<<"xml file not load in"<<endl;
		return -1;
	}
	Mat glasses = imread(glass_name);

	capture.open(0);

	if (!capture.isOpened()){
		cout<<"cannot open camera!"<<endl;
		return -1;
	}

	while(capture.read(frame)){
		if (frame.empty()){
			cout << "--(!) No captured frame -- Break!\n"<<endl;
			break;
		}

		cvtColor(frame,frame2,COLOR_BGR2GRAY);
		equalizeHist(frame2,frame2);

		vector<Rect> faces;
		classifier.detectMultiScale(frame2,faces);

		for(size_t i = 0; i < faces.size(); i++){
			if (faces[i].width > 50 || faces[i].height > 20){


				Size size(faces[i].width,faces[i].height/5);
				Rect roi(faces[i].x,faces[i].y+faces[i].height/4, faces[i].width, faces[i].height/5);
				Mat frame_roi = frame(roi);
				Mat glasses1;
				resize(glasses, glasses1, size);

				//Mat mask = maskImg(glasses,size);

				glasses1.copyTo(frame_roi);

			}
		}


		imshow("filter",frame);

		if (waitKey(1) == 2){
			break;
		}
	}

	return 0;
}
