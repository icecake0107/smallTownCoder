//
// Created by Josh Lu on 2022-07-16.
//
// Using Hungarian Algorithm (https://en.wikipedia.org/wiki/Hungarian_algorithm)
// to solve an assigment problem.
//

#import <iostream>
#import <vector>
#import <array>
#import <map>
#import <cmath>

using array1D = std::array<int, 40>;
using array2D = std::array<array1D, 40>;
using strokes = std::vector<std::array<int, 2>>; // [x,y, 0|1] 0=row, 1=col
using loc = std::array<int, 2>; // [x,y, 0|1] 0=row, 1=col

//const int test_data[4] = {3,5,10,1}; // 4
//const int test_data[9] = {2, 1, 2, 9, 8, 1, 1, 1, 1}; // 3
//const int test_data[9] = {108, 125, 150, 150, 135, 175, 122, 148, 250}; // 407
//const int test_data[36] = {9,3,57,53,1,95,86,64,49,64,93,80,74,60,27,89,44,66,44,56,11,42,43,28,99,75,20,9,99,81,70,34,56,95,18,30}; //155
//127
const int test_data[36] = {93,59,18,72,33,73,81,54,26,5,85,13,67,49,55,38,91,35,29,5,57,89,40,41,56,50,21,87,69,15,28,79,31,52,17,11 };
//const int test_data[49] = {28,30,81,56,52,97,17,17,53,98,65,74,7,16,80,58,13,5,25,42,92,53,74,28,49,92,7,15,66,82,20,85,53,51,5,45,93,48,81,30,89,88,57,7,22,22,94,33,7};


int min(const array1D array, int low=0){
    int _min = INT_MAX;
    for (auto i: array){
        if (i<_min && i>0)
            _min = i;
    }
    return _min;
}

void initMatrix(const int Arr[], int N, array2D& M){
    for(int i=0; i<N; ++i) {
        for (int j = 0; j < N; ++j) {
            M[i][j] = Arr[i * N + j];
        }
        M[i][N] = -1;
    }
    M[N][0] = -1;
}

void printM(const array2D& M) {
    for (auto row: M){
        if(row[0]<0)
            break;
        for (auto i: row){
            if (i < 0)
                break;
            std::cout<<i<<"\t";
        }
        std::cout<<" x "<<std::endl;
    }
}

void printResult(const int* result){
    std::cout<<"=== Removed Rows ===\n";
    int i = 1;
    while(result[i]!=-1){
        std::cout<<"("<<result[i]<<")";
        i+=1;
    }
    std::cout<<std::endl;

    std::cout<<"=== Removed columns ===\n";
    i +=1;
    while(result[i]!=-1){
        std::cout<<"("<<result[i]<<")";
        i+=1;
    }
    std::cout<<std::endl;
    std::cout<<"=== Total ("<<result[0]<< ") ==="<<std::endl;
}

auto solution(const array2D& M, const int N) -> int*{
    int* ret = new int[N*2];
    ret[0] = N;
    std::vector<loc> zeros {};
    std::map<int, int> rows {};
    std::map<int, int> cols {};
    std::vector<int> row_to_remove {};
    std::vector<int> col_to_remove {};
    int totalZeros = 0;
    int totalRemoved = 0;

    for (int i=0; i<N; i++){
        for(int j=0; j<N;j++)
            if(M[i][j]==0){
                totalZeros += 1;
                rows[i] += 1;
                cols[j] += 1;
                zeros.push_back(loc{i, j});
            }
    }
    bool lastRemoved = true;  //row =0, col = 1;
    while (totalRemoved<totalZeros){
        auto r_rit = rows.begin();
        auto c_rit = cols.begin();
        std::array<int, 2> max_row = {};
        std::array<int, 2> max_col = {};

        while(r_rit!=rows.end()){
            if(r_rit->second >= max_row[1]){
                max_row[0] = r_rit->first;
                max_row[1] = r_rit->second;
            }
            ++r_rit;
        }
        while(c_rit!=cols.end()){
            if(c_rit->second >= max_col[1]){
                max_col[0] = c_rit->first;
                max_col[1] = c_rit->second;
            }
            ++c_rit;
        }

        if ( (max_row[1]> max_col[1]) ||  ((max_row[1]==max_col[1]) && lastRemoved)){
            lastRemoved = false;
            row_to_remove.push_back(max_row[0]);
            totalRemoved += max_row[1];
            for (auto z: zeros) {
                if (z[0] == max_row[0] && cols[z[1]]>0 ) {
                    cols[z[1]] -= 1;
                }
            }
            rows[max_row[0]] = 0;
        }else{
            lastRemoved = true;
            col_to_remove.push_back(max_col[0]);
            totalRemoved += max_col[1];
            for (auto z: zeros) {
                if (z[1] == max_col[0] && rows[z[0]] > 0) {
                    rows[z[0]] -= 1;
                }
            }
            cols[max_col[0]] = 0;
        }
    }

    auto total = row_to_remove.size() + col_to_remove.size();
    ret[0] = total;
    for (int i = 1; i <= row_to_remove.size(); i++)
        ret[i] = row_to_remove[i - 1];
    ret[row_to_remove.size() + 1] = -1;

    for (int i = 0; i < col_to_remove.size(); i++)
        ret[i + row_to_remove.size() + 2] = col_to_remove[i];
    ret[total + 2] = -1;
    // [N/-1, row1, row2, row3...,rowN, -1, col1, col2, col3...colN, -1]
    return ret;
}


int calculate(const array2D& M, array2D& MM, const int N, int& total){

//    printM(MM);
    bool find = false;
    for(int i =0; i<N;i++){
        if (MM[0][i] != -1) {
            find = true;
            break;
        }
    }
    if(!find)
        return total;

    for (int i=0; i<N; i++){
        int value = 0;
        int column = 0;
        int zero_count = 0;
        for(int j=0;j<N;j++){
            if(MM[0][j]==-1){
                continue;
            }
            if(MM[i][j] == 0) {
                if(zero_count >0) {zero_count=0;break;}
                zero_count += 1;
                value = M[i][j];
                column = j;
            }
        }
        if(zero_count==1){
            total += value;
            MM[0][column] = -1;
        }

    }
    calculate(M, MM, N, total);

}



class Solution{
public:
    int assignmentProblem(const int Arr[], int N){

        // Step 0. initialize the matrix
        array2D M {0};
        array2D MM {0};
        initMatrix(Arr, N, M);
        initMatrix(Arr, N, MM);
        std::cout<<"=== Original ==="<<std::endl;
        printM(M);

        // Step 1. Row operation, find the lowest value in each row and subtract it from each item in the same row.
//        for (auto row: MM){
//            int min_ = min(row);
//            for(int i=0;i<N;i++)
//                row[i] -=min_;
//        }
        for(int i=0; i<N; i++){
            int min_ = min(MM[i]);
            for (int j=0; j<N;j++)
                MM[i][j] -= min_;
        }



        std::cout<<"=== Step 1. ==="<<std::endl;
        printM(MM);

        auto result = solution(MM, N);
        printResult(result);

        std::cout<<"=== Step 2. ==="<<std::endl;
        if (result[0]<N)
        {
            for (int i=0;i<N;i++){
                int m = 99999;
                for(int j=0;j<N;j++){
                    if (MM[j][i] < m){
                        m = MM[j][i];
                    };
                }
                if (m==0){ continue;}
                for(int j=0;j<N;j++){
                    MM[j][i] -= m;
                }
            }
            printM(MM);
            result = solution(MM, N);

            printResult(result);


            // Last step
            int guard = 0;
            while (result[0]<N && guard<8){
                guard += 1;
                std:: vector<int> coverRows {};
                std:: vector<int> coverCols {};
                int k = 1;
                while (result[k]!=-1) {
                    coverRows.push_back(result[k]);
                    k += 1;
                }
                k +=1;
                while (result[k]!=-1) {
                    coverCols.push_back(result[k]);
                    k+=1;
                }

                // Find out the min of all the uncovered
                int min_ = 999999;
                for(int i=0;i<N;i++){
                    if ( std::find(coverRows.begin(), coverRows.end(), i) != coverRows.end() )
                        continue;
                    for(int j=0;j<N;j++){
                        if ( std::find(coverCols.begin(), coverCols.end(), j) != coverCols.end() )
                            continue;
                        if(MM[i][j]<min_)
                            min_ = MM[i][j];
                    }
                }

                // Subtract min from all uncovered
                for(int i=0;i<N;i++){
                    for(int j=0;j<N;j++){
                        if ( std::find(coverRows.begin(), coverRows.end(), i) != coverRows.end() and
                             std::find(coverCols.begin(), coverCols.end(), j) != coverCols.end()
                                ){
                            MM[i][j] += min_;
                            continue;
                        }
                        if ( std::find(coverRows.begin(), coverRows.end(), i) == coverRows.end() and
                             std::find(coverCols.begin(), coverCols.end(), j) == coverCols.end()
                                ) {
                            MM[i][j] -= min_;
                        }
                    }
                }
                printM(MM);
                result = solution(MM, N);

                printResult(result);


            }

        }
        if (result[0]>=N){
            int total = 0;
            calculate(M, MM, N, total);
            std::cout<<"Has solution: "<<total<<std::endl;
            return total;
        }
        delete[] result;
        return 0;
    }
};

int main(){
    int result = Solution().assignmentProblem(test_data, std::sqrt(std::size(test_data)));
    std::cout<<result;
}