//
// Created by cyz on 16-12-19.
//

#include "computePrecise.h"
#include <boost/filesystem.hpp>
#include <loader/creat_groundtruth.h>
#include <iostream>
#include <cxcore.h>

namespace bfs = boost::filesystem;

float computePrecise(const std::string& _resultPath, const std::string& _groundTruthPath,std::map<std::string,float>& _allPrecise){
    _allPrecise.clear();
    std::vector<std::string> allFile;
    find_files(_resultPath,allFile);
    float  averagePre = 0.0;
    for(auto fileName : allFile){
        std::string result = _resultPath+fileName ;
        std::string groundTruth= _groundTruthPath + fileName;
        std::cout<<result<<std::endl;
        std::cout<<groundTruth<<std::endl;
        float pre = computePrecise(result,groundTruth);
        printf("pre:%f \n",pre);
        _allPrecise[fileName] = pre;
        printf("pre1  :%f \n",_allPrecise[fileName]);
        averagePre += pre;
    }
    averagePre /= allFile.size();
    return averagePre;
}



//_result means your tracking out, _groundTruth means groundtruth
float computePrecise(const std::string& _result, const std::string& _groundTruth)
{

    assert(bfs::is_regular_file(_result));
    assert(bfs::is_regular_file(_groundTruth));

    FILE* result = fopen(_result.c_str(),"r");
    FILE* groundTruth = fopen(_groundTruth.c_str(),"r");

    int x1 ,y1 ,w1 ,h1;  //(x1,y1)means position,(w,h) means width and height
    int x2 ,y2,w2 ,h2 ;  //of rect

    cv::Rect box1,box2;

    float framNum = 0;       //all the frames
    float rightNum = 0;      //tracking right frames. if(intersection / union > 0.5) rightNum++
                             //intersection and union is computed from two rect
    while(true)
    {
        int statue = fscanf(result,"%d %d %d %d\n",&x1,&y1,&w1,&h1);
        if(statue == EOF){
            printf("%s read over\n",_result.c_str());
            break;
        }
        box1 = cv::Rect(x1,y1,w1,h1);
        statue = fscanf(groundTruth,"%d %d %d %d\n",&x2,&y2,&w2,&h2);
        if(statue == EOF)
        {
            printf("%s read over\n",_groundTruth.c_str());
            break;
        }
        box2 = cv::Rect(x2,y2,w2,h2);
        framNum++;

        float areaSum = w1*h1 + w2*h2;

        cv::Rect interBox = box1&box2;
        float areaDiff = interBox.width*interBox.height;

        if(areaDiff/(areaSum-areaDiff)  >= 0.5)
            rightNum++;
    }


    printf("frame= %d",framNum);
    return rightNum/framNum;

}
