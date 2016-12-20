#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "precise/computePrecise.h"

namespace  bfs = boost::filesystem;


int main() {
    const std::string videoFolderPath="/media/cyz/myfiles/tracking_result/goturnUseKCF1/";
    const std::string GDFoldFolderPath="/media/cyz/myfiles/tracking_result/groundtruth/";
//    if (!bfs::is_directory(videoFolderPath) || !bfs::is_directory(GDFoldFolderPath))
//    {
//        printf("ERROR-%s is not a dictionary\n",videoFolderPath.c_str());
//        return 0;
//    }
    std::map<std::string, float> allPrecise;
    float averagePre = computePrecise(videoFolderPath,GDFoldFolderPath,allPrecise);
    for(auto precise : allPrecise){
        printf("%s: %f\n",precise.first.c_str(),precise.second);
    }
    printf("average precise: %f\n",averagePre);

    return 0;
}