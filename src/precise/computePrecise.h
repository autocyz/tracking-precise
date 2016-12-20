//
// Created by cyz on 16-12-19.
//

#ifndef COMPARERESULT_COMPUTEPRECISE_H
#define COMPARERESULT_COMPUTEPRECISE_H

#include <string>
#include <vector>
#include <map>
float computePrecise(const std::string& _resultPath, const std::string& _groundTruthPath,std::map<std::string,float>& _allPrecise);
float computePrecise(const std::string& _result,const std::string& _groundTruth);


#endif //COMPARERESULT_COMPUTEPRECISE_H
