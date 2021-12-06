#include <iostream>
#include <array>
#include <stdexcept>
 
template<size_t N, size_t M, typename T>
struct Matrix{
    std::array<std::array<T, M>, N> my_Matrix {};
//CONSTRUCTORS=================================================================

    Matrix(){
        try{
            if(N == 0 && M == 0){
                throw std::underflow_error("Matrix is empty");
            }
        } 
        catch(std::underflow_error& empty){
            std::cout << "Exception: " << empty.what() <<std::endl;
        }
        if(N < M){
            throw std::range_error("Number of columns needs to be greater or equal to number of rows.");
        }
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++){
                my_Matrix[i][j] = 0;
            }
        }
    }

    template<size_t N1, size_t M1, typename T1>
    Matrix(const Matrix<N1, M1, T1>& cpy){
        try{
            if(N1 >= N || M1 >= M){
                throw std::overflow_error("Passed indexes are too high");
            }
        }
        catch(std::overflow_error& index_too_high){
            std::cout<< "Exception: " << index_too_high.what() << std::endl;
        }
        for(size_t i = 0; i < M1; i++){
            for(size_t j = 0; j < N1; j++){
                my_Matrix[i][j] = static_cast<T>(cpy[i][j]);
            }
        }
    }

    Matrix(Matrix<N, M, T>&& Moved_Matrix) noexcept 
        : my_Matrix(std::move(Moved_Matrix.my_Matrix)){}

    ~Matrix(){}

//OPERATORS====================================================================
//OPERATOR[]
    std::array<T, M>& operator[](size_t index){
        return my_Matrix.at(index);
    }

//OPERATOR+ - ADDING ANOTHER MATRIX============================================
    template<size_t N1, size_t M1, typename T1>
    Matrix<N, M, T> operator+(const Matrix<N1, M1, T1>& mat) const {
        try{
            if(N1 != N || M1 != M){
                throw std::range_error("Indexes are not equal");
            }
        } 
        catch(std::range_error unequal_index){
            std::cout << "Exception: " << unequal_index.what() << std::endl;
            Matrix<N, M, T> Fail;
            Fail = *this;
            return Fail;
        }
        Matrix<N, M, T> Add_Matrix;
        for(size_t i = 0; i < N; i++){
            for(size_t j = 0; j < M; j++){
                Add_Matrix.my_Matrix[i][j] = this->my_Matrix[i][j] + static_cast<T>(mat.my_Matrix[i][j]);
            }
        }
        return Add_Matrix;
    }

//OPERATOR+ - ADDING SCALAR====================================================
    Matrix<N, M, T>& operator+(const T& scalar){
        try{
            if(N != M){
                throw std::range_error("Indexes are not equal");
            }
        } 
        catch(std::range_error unequal_index){
            std::cout << "Exception: " << unequal_index.what() << std::endl;
            return *this;
        }
        for(size_t i = 0; i < N; i++){
            this->my_Matrix[i][i] = this->my_Matrix[i][i] + scalar;
        }
        return *this;
    }

//MULTIPLYING BY ANOTHER MATRIX================================================
    template<size_t N1, size_t M1, typename T1>
    Matrix<N, M, T> operator*(const Matrix<N1, M1, T1>& mat){
        try{
            if(N1 != N || M1 != M){
                throw std::range_error("Indexes are not equal");
            }
        } 
        catch(std::range_error unequal_index){
            std::cout << "Exception: " << unequal_index.what() << std::endl;
            std::cout << "Matrix reset." << std::endl;
            Matrix<N, M, T> Fail;
            Fail = *this;
            return Fail;
        }
        Matrix<N, M, T> multi_Matrix;
        std::array<T, N> buffer;
        T proxy;
        size_t i, j, k;
        size_t x = 0, y = 0;
        for(i = 0; i < N; i++){
            y = 0;
            for(j = 0; j < N; j++){
                for(k = 0; k < M; k++){
                    buffer[k] = this->my_Matrix[i][k] * static_cast<T>(mat.my_Matrix[k][j]);
                }
                proxy = 0;
                for(auto it : buffer){
                    proxy += it;
                }
                multi_Matrix.my_Matrix[x][y] = proxy;
                y++;
            }
            x++;
        }
        return multi_Matrix;
    }

//OPERATOR* - MULTIPLYING BY SCALAR============================================
    Matrix<N, M, T>& operator*(const T& scalar){
        for(size_t i = 0; i < N; i++){
            for(size_t j = 0; j < M; j++){
                this->my_Matrix[i][j] = this->my_Matrix[i][j] * scalar;
            }
        }
        return *this;
    }

//OPERATOR=  ==================================================================
    template<size_t N1, size_t M1, typename T1>
    Matrix<N, M, T>& operator=(const Matrix<N1, M1, T1>& other){
        try{
            if(N1 != N || M1 != M){
                throw std::range_error("Indexes are not equal");
            }
        }
        catch(std::range_error unequal_indexes){
            std::cout << "Exception: " << unequal_indexes.what() << std::endl <<
            "Matrix wasn't assigned" << std::endl;
            return *this;
        }
        for(size_t i = 0; i < N; i++){
            for(size_t j = 0; j < M; j++){
                this->my_Matrix[i][j] = static_cast<T>(other.my_Matrix[i][j]);
            }
        }
        return *this;
    }

    Matrix<N, M, T>& operator=(const Matrix<N, M, T>& other){
        if(&other == this){
            return *this;
        }
        for(size_t i = 0; i < N; i++){
            for(size_t j = 0; j < M; j++){
                this->my_Matrix[i][j] = other.my_Matrix[i][j];
            }
        }
        return *this;
    }

//OSTREAM OPERATOR=============================================================
    template<size_t A, size_t B, typename Y>
    friend std::ostream& operator<<(std::ostream& os, Matrix<A, B, Y>& matrix);
};

template<size_t N, size_t M, typename T>
std::ostream& operator<<(std::ostream& os, Matrix<N, M, T>& matrix){
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < M; j++){
            os << "|" << matrix[i][j] << "| ";
        }
        os << std::endl;
    }
    return os;
}

//SPECIALIZING FOR BOOL TYPE ==================================================
template<size_t N, size_t M>
struct Matrix<N, M, bool>{
    Matrix(){
        try{
            throw std::invalid_argument("Cannot create matrix of type bool");
        }
        catch(std::invalid_argument wrong_type){
            std::cout << "Exception: " << wrong_type.what() << std::endl;
        }
    }
};

//=============================================================================
int main(){
    try{
//CREATING 5 MATRICES==========================================================
        const size_t columns = 3;
        const size_t rows = 3;
        Matrix<3, 3, int> first_matrix;
        Matrix<columns, rows, double> second_matrix;
        Matrix<columns, rows, int> third_matrix;
        int index = 0;
        double d_index = 9.89;
        Matrix<0, 0, int> empty_matrix;
        Matrix<10, 10, int> fourth_matrix;
        Matrix<5, 5, bool> bool_matrix;
        Matrix<10, 4, int> sixth_matrix;

    //FILLING 2 MATRICES WITH VALUES FROM 1 TO 9===================================
        for(int i = 0; i < columns; i++){
            for(int j = 0; j < rows; j++){
                index++;
                first_matrix[i][j] = index;
                second_matrix[i][j] = index;
            }
        }

    //PRINTING CREATED MATRICES (OSTREAM OPERATOR TEST)============================
        std::cout << "First matrix: " << std::endl << first_matrix
        << std::endl << "Second matrix: " << std::endl << second_matrix 
        << std::endl << "Third matrix: " << std::endl << third_matrix 
        << std::endl;

    //TESTING ACTIONS =============================================================
        third_matrix = first_matrix + second_matrix;
        std::cout << "Third matrix after assigning sum of first and second to it: " <<
        std::endl << third_matrix << std::endl;

        third_matrix = first_matrix * second_matrix;
        std::cout << "Third matrix after assigning first multiplyed by second: " << std::endl;
        std::cout << third_matrix << std::endl;

        std::cout << "First matrix after multiplying it by scalar (2): " << std::endl;
        std::cout << first_matrix * 2 << std::endl;

        std::cout << "First matrix after adding scalar (5) to it: " << std::endl;
        std::cout << first_matrix + 5 << std::endl;

        std::cout << "Fourth: " << std::endl;
        std::cout << fourth_matrix + 2 << std::endl;

        Matrix<2, 2, int> fifth;
        
        fifth = fifth + first_matrix;

        std::cout << fifth << std::endl;

        std::cout << sixth_matrix << std::endl;
    
    
    }
    catch(std::range_error columns_greater_than_rows){
        std::cout << "Exception: " << columns_greater_than_rows.what() << std::endl;
    }
    
    return 0;
}