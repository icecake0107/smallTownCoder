//
// Created by Josh Lu on 2022-07-31.
//

#ifndef SMALLTOWNCODER_MATRIX_H
#define SMALLTOWNCODER_MATRIX_H

namespace MM{
struct Matrix{
    int size {};
    const int rowCount() const{
        return this->size/2;
    }
    const int colCount(){
        return rowCount();
    }

    Matrix(const int* &array, const int N){
        this->size = N;
    };
};
};


#endif //SMALLTOWNCODER_MATRIX_H
