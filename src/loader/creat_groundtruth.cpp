//
// Created by cyz on 16-12-18.
//

#include "creat_groundtruth.h"

namespace bfs = boost::filesystem;

//Find all the files in _folder, push_back to _allFile and sort them
void find_files(const std::string& _folder, std::vector<std::string>& _allFiles){
    if(!bfs::is_directory(_folder)){
        printf("Error - %s is not a valid directory\n",_folder.c_str());
        return;
    }
    _allFiles.clear();
    //Find all the subfolders and sort them
    bfs::directory_iterator end_itr; // default construction yields past-the-end
    for (bfs::directory_iterator itr(_folder); itr != end_itr; ++itr) {
        if (bfs::is_regular_file(itr->status())) {
            std::string filename = itr->path().filename().string();
            _allFiles.push_back(filename);
        }
    }
    std::sort(_allFiles.begin(),_allFiles.end());

    for(auto sub : _allFiles){
        printf("%s\n",sub.c_str());
    }
    printf("files num = %zu\n",_allFiles.size());
}


//Find all the subfolders in _folder, push_back to _subFolders and sort them
void find_subfolders(const std::string& _folder, std::vector<std::string>& _subFolders){
    if(!bfs::is_directory(_folder)){
        printf("Error - %s is not a valid directory\n",_folder.c_str());
        return;
    }

    //Find all the subfolders and sort them
    bfs::directory_iterator end_itr; // default construction yields past-the-end
    for (bfs::directory_iterator itr(_folder); itr != end_itr; ++itr) {
        if (bfs::is_directory(itr->status())) {
            std::string filename = itr->path().filename().string();
            _subFolders.push_back(filename);
        }
    }
    std::sort(_subFolders.begin(),_subFolders.end());

    for(auto sub : _subFolders){
        printf("%s\n",sub.c_str());
    }
    printf("sub_folders.size = %zu\n",_subFolders.size());
}

void creatGroundTruth(const std::string &_srcPath, const std::string& _gdPath){

    std::vector<std::string> sub_folders;
    find_subfolders(_srcPath,sub_folders);

    int x,y,width,height;

    for(auto video_name:sub_folders)
    {
        const std::string video_path = _srcPath+video_name;
        printf("%s\n",video_path.c_str());
        if(bfs::is_regular_file(video_path+"/groundtruth.txt"))
        {
            const std::string groundTruthPath = video_path+"/groundtruth.txt";

            printf("%s\n",groundTruthPath.c_str());
            FILE* groundtruthfile = fopen(groundTruthPath.c_str(),"r");

            const std::string GDPath = _gdPath+video_name+".txt";
            FILE* GDfile = fopen(GDPath.c_str(),"w+");

            double ax,ay,bx,by,cx,cy,dx,dy;

            while(true)
            {
                const int status = fscanf(groundtruthfile,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",&ax, &ay, &bx, &by, &cx, &cy, &dx, &dy);
                if(status == EOF)
                    break;
                x = (int)round(std::min(ax,std::min(bx,std::min(cx,dx))));
                y = (int)round(std::min(ay,std::min(by,std::min(cy,dy))));
                width = (int)round(std::max(ax,std::max(bx,std::max(cx,dx)))) - x;
                height = (int)round(std::max(ay,std::max(by,std::max(cy,dy)))) - y;
                fprintf(GDfile,"%d %d %d %d\n",x,y, width,height);
            }
        }
    }
}

