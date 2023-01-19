#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <iostream>
//
// Created by 黄哲亨 on 10/6/22.
//

using namespace std;

class BookInfo{
public:

    void printVec();
    int ISNB;
    string Type, Language;
    bool operator<( const BookInfo& nextBook)const;
    bool operator==( const BookInfo& nextBook)const;
    //friend ostream& operator<<(ostream os, const BookInfo oneLine);
};

//ostream& operator<<(ostream os, const BookInfo oneBook){
//    os << oneBook.ISNB << ' ' << oneBook.Type << ' '<< oneBook.Language << endl;
//    return os;
//}
// read data from the input file and store in vec containers

void BookInfo::printVec(){
    std::cout <<ISNB << ' ' << Type << ' '<< Language << endl;
}

vector<BookInfo> readDataIntoVec(const string &userInputFileName) {
    //cout<<"testReadData"<<endl;
    ifstream bookIfStream;
    bookIfStream.open(userInputFileName);

    std::vector<BookInfo> BookVec;

    if(!bookIfStream.is_open()){
        cerr << "Error: cannot open file " << userInputFileName << endl;
    }

    if(bookIfStream.is_open()){
//      cout << "jinlaile"<<endl;
        string nextBook;
        while(getline(bookIfStream, nextBook)){
//          cout << "meijinlai"<<endl;
            string curISNB, curType, curLanguage;
            BookInfo curBook;
            stringstream ss(nextBook);
            getline(ss,curISNB,',');
            curBook.ISNB = stoi(curISNB);
            //cout << curISNB << endl;
            getline(ss, curType,',');
            curBook.Type = curType;
            getline(ss,curLanguage, ',');
            curBook.Language = curLanguage;
            BookVec.push_back(curBook);
        }
        bookIfStream.close();
    }

    return BookVec;
}

//int linearSearch(const std::vector<BookInfo>& newBookData, const std::vector<BookInfo>& requestBookData){
//    int count = 0;
//    //bool found = false;
//    //vector<BookInfo> outputFile;
//    for(long unsigned int i = 0; i < requestBookData.size();i++){//auto & i : requestBookData//
//        for(long unsigned int j = 0; j < newBookData.size(); j++){//auto & j : newBookData//
//            if(newBookData[j] ==requestBookData[i]){
//                //found = true;
//                count ++;
//                //outputFile.push_back(newBookData[j]);
//            }
//        }
//    }
//    return count;
//}

//int binarySearch(std::vector<BookInfo> newBookData, const std::vector<BookInfo>& requestBookData){
//    int count = 0;
//    //bool found = false;
//    //vector<BookInfo> outputFile;
//    int left = 0;
//    int right = newBookData.size() - 1;
//    for(long unsigned int i = 0 ; i < requestBookData.size();i++){//auto & i : requestBookData
//        while(left < right){
//            int  mid = left + (right - left) / 2;
//            if(newBookData[mid] == requestBookData[i]){
//                //outputFile.push_back(newBookData[mid]);
//                //just need the number of founded book in request, not the list of founded book
//                count ++;
//            }
//            else if(newBookData[mid] < requestBookData[i]){
//                left = mid + 1;
//            }
//            else{
//                right = mid;
//            }
//        }
//    }
//    return count;
//}

bool BookInfo::operator<(const BookInfo& nextBook)const{

    if(ISNB != nextBook.ISNB){
        return (ISNB < nextBook.ISNB);
    }
        // if ISNB == nextBook.ISNB
    else if(Type != nextBook.Type){
        //if curBook type is new, no need to move, or curType = used, and following book is not new,
        //or curtype == digital and following type is also digital
        return(Type == "new"
               || (Type == "used" && nextBook.Type != "new")
               || (Type == "digital" && nextBook.Type == "digital"));
    }
    else{
        return Language > nextBook.Language;
    }
}

bool BookInfo::operator==(const BookInfo& nextBook)const{
    if(ISNB == nextBook.ISNB && Type == nextBook.Type && Language == nextBook.Language){
        return true;
    }
    else{
        return false;
    }
}

char chooseLorB(){
    char choice;
    cin>>choice;
    return choice;
}

void OutputFile(int count, const string& fileName){
    ofstream outputFile;
    outputFile.open(fileName);
    //cout<<count<<endl;
    outputFile << count;
    outputFile.close();
}


int main(int argc, char *argv[]) {

    while (argc < 4) {
        std::cerr << "Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>" << endl;
        return 0;
    }
//    while(argv[1] != "newBooks.dat" ||argv[2] != "request.dat"){
//        if(argv[1] != "newBooks.dat" && argv[2] != "request.dat"){
//            cout << "Error: cannot open file " << argv[1];
//        }
//        else if(argv[1] == "newBooks.dat" && argv[2] != "request.dat"){
//            cout << "Error: cannot open file " << argv[2];
//        }
    vector<BookInfo> newBookData;
    vector<BookInfo> requestBookData;
    //cout<<"sb"<<endl;

    newBookData = readDataIntoVec(argv[1]);
    requestBookData = readDataIntoVec(argv[2]);

    //cout << newBookData.size() << endl;
    //cout << requestBookData.size() << endl;
    if(newBookData.size() != 0 && requestBookData.size() != 0){
        cout << "Choice of search method ([l]inear, [b]inary)?" << endl;
        char choice = chooseLorB();
    std::sort(newBookData.begin(), newBookData.end());

    std::chrono::high_resolution_clock::time_point start;
    start = std::chrono::high_resolution_clock::now();

    while(choice != 'b' && choice != 'l'){
        cerr << "Incorrect choice" << endl;
        choice = chooseLorB();
    }

    if (choice == 'l'){
        int count = 0;
        for(long unsigned int i = 0; i < requestBookData.size();i++){
            for(long unsigned int j = 0; j < newBookData.size(); j++){
                if(newBookData[j] ==requestBookData[i]){
                    count ++;
                }
            }
        }
        OutputFile(count, argv[3]);
    }
    else if(choice == 'b'){
        int count = 0;
        sort(newBookData.begin(), newBookData.end());
        //for (vector<BookInfo>::iterator it = newBookData.begin(); it != newBookData.end(); ++it){
        //            it -> printVec();
        //        }
        //for(auto index : newBookData)
        //        for (int i = 0; i < newBookData.size(); i++){
        //            cout << newBookData[i] << endl;
        //        }
        for(long unsigned int i = 0 ; i < requestBookData.size();i++){
            //cout << "jinlaile" << endl;
            int left = 0;
            int right = newBookData.size() - 1;
            while(left <= right){
                int  mid = left + (right - left) / 2;
                cout << "meijinlai"<<endl;
                if (newBookData[mid] == requestBookData[i]){
                    //cout << "zhaodaole"<<endl;
                    count += 1;
                    break;
                }
                else if(newBookData[mid] < requestBookData[i]){
                    cout << "taixiaole"<<endl;
                    left = mid + 1;
                }
                else{
                    cout << "taidale"<<endl;
                    right = mid - 1;
                }
            }
        }
        OutputFile(count, argv[3]);
    }
//    else{
//        cerr << "Incorrect choice" << endl;
//        choice = chooseLorB();
//    }
    //   while (!done) {
    //        switch (choice) {
    //            case 'l':
    //                //linearSearch(newBookData, requestBookData);
    //                {//auto & i : requestBookData//
    //                    {//auto & j : newBookData//
    //                        {
    //                            //found = true;
    //                            //outputFile.push_back(newBookData[j]);
    //                done = true;
    //                break;
    //            case 'b':
    //                {//auto & i : requestBookData
    //                    {
    //                        {
    //                            //outputFile.push_back(newBookData[mid]);
    //                            //just need the number of founded book in request, not the list of founded book
    //                        }
    //                        else if(newBookData[mid] < requestBookData[i]){
    //                        }
    //                        else{
    //                done = true;
    //                break;
    //            default:
    //        }
    //    }
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "CPU time: " << elapsed_us << " microseconds" << endl;
    //cout << count <<endl;
}
}
