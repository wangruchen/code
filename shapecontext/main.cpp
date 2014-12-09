#include <opencv2/opencv.hpp>
#include<opencv2/shape/shape_distance.hpp>
#include<opencv2/shape.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

static vector<Point> simplecontour(const Mat& pict, int n=300)
{
    vector<vector<Point> > contour;
    vector<Point> contourz;
    findContours(pict,contour,RETR_LIST,CHAIN_APPROX_NONE);
    for(size_t b=0; b<contour.size(); b++)
    {
        for(size_t a=0; a<contour[b].size(); a++)
        {
            contourz.push_back(contour[b][a]);
        }
    }
     int dummy=0;
    for (int add=(int)contourz.size()-1; add<n; add++)
    {
    contourz.push_back(contourz[dummy++]); //adding dummy values
    }
    // Uniformly sampling
    random_shuffle(contourz.begin(), contourz.end());
    vector<Point> cont;
    for (int i=0; i<n; i++)
    {
    cont.push_back(contourz[i]);
    }
    return cont;

}

int main(int argc, char* argv[])
{
    Ptr <ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
    string path="01_0";
    int first=1;
    float mindis=FLT_MAX;
    int num=0;
    float dis[1000];
    stringstream firstname;
    firstname<<path<<first<<"_m.bmp";
    Mat firstIm=imread(firstname.str(),0);
    //imshow("firstpicture",firstIm);
    vector<Point> firstsimpcont=simplecontour(firstIm);
    for(int l=1;l<=8;l++)
    {
        for(int k=1;k<=5;k++)
        {
            stringstream kname;

            kname<<"0"<<l<<"0"<<k<<"_m.bmp";
            Mat kIm=imread(kname.str(),0);
            vector<Point> ksimpcont=simplecontour(kIm);
            dis[k-1] = mysc -> computeDistance(firstsimpcont,ksimpcont);
            //imshow("picture",kIm);

            if(dis[k-1]<mindis)
            {
                mindis=dis[k-1];
                num=k;
            }
            cout<<"distance between "<<firstname.str()<<" and "<<kname.str()<<" is "<<dis[k-1]<<endl;
    //        stringstream kname1;
    //        kname1<<path<<1<<"_m.bmp";
    //        Mat kIm1=imread(kname1.str(),0);
    //        vector<Point> ksimpcont1=simplecontour(kIm1);
    //        dis[1] = mysc -> computeDistance(firstsimpcont,ksimpcont1);
    //        //imshow("picture",kIm);
    //        cout<<"distance between "<<firstname.str()<<" and "<<kname1.str()<<" is "<<dis[1]<<endl;
    //        stringstream kname2;
    //        kname2<<path<<2<<"_m.bmp";
    //        Mat kIm2=imread(kname2.str(),0);
    //        vector<Point> ksimpcont2=simplecontour(kIm2);
    //        dis[2] = mysc -> computeDistance(firstsimpcont,ksimpcont2);
    //        //imshow("picture",kIm);
    //        cout<<"distance between "<<firstname.str()<<" and "<<kname2.str()<<" is "<<dis[2]<<endl;
    //        //waitKey();
    //        stringstream kname3;
    //        kname3<<path<<3<<"_m.bmp";
    //        Mat kIm3=imread(kname3.str(),0);
    //        vector<Point> ksimpcont3=simplecontour(kIm3);
    //        dis[3] = mysc -> computeDistance(firstsimpcont,ksimpcont3);
    //        //imshow("picture",kIm);
    //        cout<<"distance between "<<firstname.str()<<" and "<<kname3.str()<<" is "<<dis[3]<<endl;

        }
    }
    cout<<"best distance "<<" is "<<mindis<<" between "<<firstname.str()<<"and"<<path<<num<<endl;

}
