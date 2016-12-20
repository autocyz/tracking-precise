//
// Created by cyz on 16-12-18.
//


#ifndef COMPARERESULT_CREAT_GROUNDTRUTH_H
#define COMPARERESULT_CREAT_GROUNDTRUTH_H


#include <string>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

void find_files(const std::string& _folder, std::vector<std::string>& _allFiles);
void find_subfolders(const std::string& _folder, std::vector<std::string>& _subFolders);

void  creatGroundTruth(const std::string& srcPath,const std::string& gdPath );
#endif //COMPARERESULT_CREAT_GROUNDTRUTH_H

