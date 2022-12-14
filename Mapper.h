//
//  Mapper.h
//  csv3
//
//  Created by F on 24/11/2022.
//
#include "ofApp.h"
#include <ctime>
#include <iostream>
#include "ofxCsv.h"
#include <algorithm>
#include <utility>
#include <chrono>

#ifndef Mapper_h
#define Mapper_h
#define separ ";"


#endif /* Mapper_h */


struct MainTimeArray
{
    std::string codeQr;
    std::string firstUseDate;
    std::string lastUseDate;
    int mainCounter = 0; //liczba użyć kodu QR
};

class MainVectorModifier
{
public:
    
   
    std::vector<MainTimeArray> mainCsvVector;
    

    
    MainVectorModifier()
    {
        if(xcsv.load("XX.csv", separ))
        {std::cout << xcsv.getNumRows();
            for(int i = 0; i < xcsv.getNumRows(); ++i)
           
            {
                ofxCsvRow xcsvr;

                MainTimeArray tempElement;
                xcsvr = xcsv.getRow(i);
                tempElement.codeQr = xcsvr.getString(0);
                tempElement.mainCounter = xcsvr.getInt(1);
                tempElement.firstUseDate = xcsvr.getString(2);
                tempElement.lastUseDate = xcsvr.getString(3);
                mainCsvVector.push_back(tempElement);
                
                
            }
        }
        else{
            xcsv.load("20000.csv", separ);
            for(int i = 0; i < xcsv.getNumRows(); ++i){
//                std::vector <std::string> secondTableVector = xcsv.getRow(i).getData();
                MainTimeArray tempElement;
                ofxCsvRow xcsvr;
                xcsvr = xcsv.getRow(i);
               
                tempElement.codeQr =  xcsvr.getString(0);

                mainCsvVector.push_back(tempElement);
                
            }
        }
    }
    bool checkQrCode(const std::string &codeQr){
        auto clock_start_time = std::chrono::high_resolution_clock::now();
        //std::cout << mainCsvVector.size();
        for(auto& item : mainCsvVector){
//            std::cout << item.codeQr;
            
            if(item.codeQr == codeQr){
                //std::cout << item.mainCounter;
                ++item.mainCounter;
                if(item.mainCounter > 1)
                {
//                    ++item.mainCounter;
                    std::cout << "\nITS QR CODE: " << codeQr << " " << "THIS CODE IS USED\n";
                    char strTime[26];
                        struct tm* tmInfo;
                        time_t rawtime;
                        time(&rawtime);
                        tmInfo = localtime(&rawtime);
                        strftime(strTime, 26, "%Y-%m-%d %H:%M:%S", tmInfo);
//                        newRow.setString(4, strTime);
                    
                    
                    item.lastUseDate = std::string(strTime);
                  
                    
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto vectortimer = end_time - clock_start_time;
                    std::cout << "\nczas wykonania wyszukiwania kodu\n" << vectortimer/std::chrono::microseconds(1) << " mikrosekund";
                    
                    //std::cout << item.mainCounter;
                    saverOfFile();
                    
                    return false;
                }else{
//                    ++item.mainCounter;
                    std::cout << "CODE   " << codeQr << "   APPROVE\n\n";
//                    time_t nowt = time(0);
//                    char* td = ctime(&nowt);
//                    item.lastUseDate = std::string(td);
//                    item.firstUseDate = std::string(td);
                    
                    
                    char strTime[26];
                        struct tm* tmInfo;
                        time_t rawtime;
                        time(&rawtime);
                        tmInfo = localtime(&rawtime);
                        strftime(strTime, 26, "%Y-%m-%d %H:%M:%S", tmInfo);
//                        newRow.setString(4, strTime);
                    
                    item.lastUseDate = std::string(strTime);
                    item.firstUseDate = std::string(strTime);
                    
                    saverOfFile();
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto vectortimer = end_time - clock_start_time;
                    std::cout << "\nczas wykonania wyszukiwania kodu\n" << vectortimer/std::chrono::microseconds(1) << " mikrosekund";
                    
                    
                    return true;
                }
                
               
                }

            
        }
        
    }
    void  saverOfFile(){
        //
        ofxCsv toSave;
        for(auto& item : mainCsvVector)
        
        
        {
            //std::cout << item.mainCounter;
            ofxCsvRow tempRow;
            
            tempRow.setString(0, item.codeQr);
            tempRow.setInt(1, item.mainCounter);
            tempRow.setString(2, item.firstUseDate);
            tempRow.setString(3, item.lastUseDate);
            
            toSave.addRow(tempRow);
        }
        //toSave.load(mainCsvVector);
       
        toSave.save("XX.csv",true, separ);
        xcsv.save
       
    }
    

                     
    
    ofxCsv xcsv;
};
