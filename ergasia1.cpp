#include <stdio.h>
#include <vector>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include<list>


using namespace cv;
using namespace std;


void askisi_1();
void askisi_2();

int main(int argc, char** argv )
{
    askisi_1();
    askisi_2();
    
    
    return 0;
}


void askisi_1()
{
    Mat image;
    image = imread("C:/Users/user/Desktop/UTH/epeksergasia/standard_test_images/lena_gray_256.tif");

    if ( !image.data )
    {
        printf("No image data \n");
        std::exit(0);
    }
    Mat image2,image3,image4;
    image2 = image.clone();
    image3 = image.clone();
    image4 = image.clone();

    Mat image5,image6,image7;
    image5 = image.clone();
    image6 = image.clone();
    image7 = image.clone();
    
    int radius[3] = {1,4,7};

    int height = image.rows;
    int width = image.cols;

    list<int> list_blue;
    
    for( int z = 0; z < 3; z++)
    {
        
        for ( int i = 0; i < height ; i++)
        {
            for (int  j = 0; j < width ; j++)
            {
                
                for(int k=1; k <= radius[z]; k=k+3)
                {
                    int sum_b = 1;
                    
                    int sum_blue = 0;  
                   
                    int alt_blue = 0; 
                    

                    sum_blue = sum_blue + image.at<Vec3b>(i,j)[0];
                    
                    list_blue.push_back(image.at<Vec3b>(i,j)[0]);

                    for (int a = -k; a <= k; a++) 
                    {
                        for (int b = -k; b <= k; b++) 
                        {
                            if ((i + a) >= 0 && (i + a) < height && (j + b) >= 0 && (j + b) < width) 
                            {
                                sum_blue = sum_blue + image.at<Vec3b>(i+a,j+b)[0];
                                sum_b = sum_b +1;
                                list_blue.push_back(image.at<Vec3b>(i+a,j+b)[0]);
                            }
                        }
                    }
                    
                    list_blue.sort();
                    

                    alt_blue = sum_blue / sum_b; 
                    

                    if(k == 1)
                    {
                        image2.at<Vec3b>(i,j)[0] = alt_blue;
                        image2.at<Vec3b>(i,j)[1] = alt_blue; //3x3
                        image2.at<Vec3b>(i,j)[2] = alt_blue;

                        

                         list<int>::iterator it = list_blue.begin();
                         int step=1;
                         if(list_blue.size()%2==1){
                             step = ((int)list_blue.size()-1)/2;
                         }else{
                             step = ((int)list_blue.size())/2-1;
                         }
                         advance(it, step);

                        

                          image5.at<Vec3b>(i,j)[0] = *it;
                          image5.at<Vec3b>(i,j)[1] = *it; 
                          image5.at<Vec3b>(i,j)[2] = *it;
                        
                    }
                    else if(k == 4)
                    {
                        image3.at<Vec3b>(i,j)[0] = alt_blue;
                        image3.at<Vec3b>(i,j)[1] = alt_blue; //9x9
                        image3.at<Vec3b>(i,j)[2] = alt_blue;

                        

                        list<int>::iterator it = list_blue.begin();
                         int step=1;
                         if(list_blue.size()%2==1){
                             step = ((int)list_blue.size()-1)/2;
                         }else{
                             step = ((int)list_blue.size())/2-1;
                         }
                         advance(it, step);

                        

                          image6.at<Vec3b>(i,j)[0] = *it;
                          image6.at<Vec3b>(i,j)[1] = *it; 
                          image6.at<Vec3b>(i,j)[2] = *it;
                    }
                    else
                    {
                        image4.at<Vec3b>(i,j)[0] = alt_blue;
                        image4.at<Vec3b>(i,j)[1] = alt_blue; //15x15
                        image4.at<Vec3b>(i,j)[2] = alt_blue;


                        

                        list<int>::iterator it = list_blue.begin();
                         int step=1;
                         if(list_blue.size()%2==1){
                             step = ((int)list_blue.size()-1)/2;
                         }else{
                             step = ((int)list_blue.size())/2-1;
                         }
                         advance(it, step);

                        

                          image7.at<Vec3b>(i,j)[0] = *it;
                          image7.at<Vec3b>(i,j)[1] = *it; 
                          image7.at<Vec3b>(i,j)[2] = *it;
                    }

                list_blue.clear();
                }

            }

        }
    }

    imshow("Original image",image);

    imshow("Blurred Image 3x3", image2);

    imshow("Blurred Image 9x9", image3);

    imshow("Blurred Image 15x15", image4);

    waitKey(0);

    //  
    imshow("Median Image 3x3", image5);

    imshow("Median Image 9x9", image6);

    imshow("Median Image 15x15", image7);

    waitKey(0);
}

void askisi_2()
{
    Mat image = imread("C:/Users/user/Desktop/UTH/epeksergasia/standard_test_images/lena_gray_256.tif");

    if ( !image.data )
    {
        printf("No image data \n");
        std::exit(0);
    }

    Mat image2,image3,image4,image5,image6,image7;

    GaussianBlur(image, image2, Size(3, 3), 0); //3x3
    GaussianBlur(image, image3, Size(9, 9), 0); //9x9
    GaussianBlur(image, image4, Size(15, 15), 0); //15x15

    medianBlur(image, image5,  3); 
    medianBlur(image, image6,  9); 
    medianBlur(image, image7,  15); 


    imshow("OpenCV Image", image);

    imshow("OpenCV 3x3 blur image", image2);

    imshow("OpenCV 9x9 blur image", image3);

    imshow("OpenCV 15x15 blur image", image4);



    imshow("OpenCV 3x3 median image", image5);

    imshow("OpenCV 9x9 median image", image6);

    imshow("OpenCV 15x15 median image", image7);

    
    waitKey(0);
}
