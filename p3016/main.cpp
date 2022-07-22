//
// Created by Josh Lu on 2022-07-16.
//
// Using Hungarian Algorithm (https://en.wikipedia.org/wiki/Hungarian_algorithm)
// to solve an assigment problem.
//

#import <iostream>
#import <vector>
#import <array>
#import <cmath>

using array2D = int[50][50];
using indicies = std::vector<std::array<int, 2>>;

//const int test_data[9] = {2, 1, 2, 9, 8, 1, 1, 1, 1};
//const int test_data[4] = {3,5,10,1};

const int test_data[9] = {108, 125, 150, 150, 135, 175, 122, 148, 250};


int min(const int array[], int low=0){
    int _min = INT_MAX;

    while (*array > 0){
        if (*array == low)
            return *array;
        if (*array<_min)
        {
            _min=*array;
        }
        ++array;
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
    for (auto r: M){
        if (*r < 0){
            break;
        }
        while(*r >= 0){
            std::cout<<*r<<"\t";
            ++r;
        }
        std::cout<<" x "<<std::endl;
    }
}


indicies hasSolution(const array2D& M, const int N){
    indicies strokes {};

    // Collect all zeros' index.
    for (int i=0; i<N; i++){
        for(int j=0; j<=N; j++){
            if (M[i][j]==0){
                bool hasLink = true;
                for (auto x: strokes){
                    if(x[0]==i || x[1] ==j){
                        hasLink = false;
                        break;
                    }
                }
                if (hasLink){
                    std::array<int, 2> a {i, j};
                    strokes.push_back(a);
                }
            }
        }
    }

    std::cout<<"=== zero locs ===\n";
    for (auto x: strokes){
        std::cout<<"("<<x[0]<<","<<x[1]<<"),";
    }
    std::cout<<std::endl;

    return strokes;
}

class Solution{
public:
    int assignmentProblem(const int Arr[], int N){

        // Step 0. initialize the matrix
        array2D M {0};
        array2D MM {};
        initMatrix(Arr, N, M);
        initMatrix(Arr, N, MM);
        std::cout<<"=== Original ==="<<std::endl;
        printM(M);

        // Step 1. Row operation, find the lowest value in each row and subtract it from each item in the same row.
        for (auto row: MM){
            int min_ = min(row);
            while(*row>0) {
                *row -= min_;
                row++;
            }
        }
        std::cout<<"=== Step 1. ==="<<std::endl;
        printM(MM);

        std::cout<<"=== Step 2. ==="<<std::endl;
        auto result = hasSolution(MM, N);
        if (result.size()>=N){
            int v = 0;
            for(auto i : result){
                v += M[i[0]][i[1]];
            }
            std::cout<<"Has solution: "<<v<<std::endl;
        }else{

            std::cout<<"No  solution: "<<std::endl;
        }
        return 0;
    }
};

int main(){
    int result = Solution().assignmentProblem(test_data, std::sqrt(std::size(test_data)));
    std::cout<<result;
}