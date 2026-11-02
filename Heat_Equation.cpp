#include <cmath>
#include <iostream>
#include <initializer_list>
#include <memory>
#include <map>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector
{
public:
// Constructors

// Default
Vector()
:length(0), vec(nullptr){}

// Length of argument constructor
Vector(int len)
:length(len), vec(new T[len]){}

// Initializer
Vector(const std::initializer_list<T> list) 
:Vector((int)list.size())  
{ 
std::uninitialized_copy(list.begin(), list.end(), vec);  
} 


// Copy
Vector(const Vector& other)
:Vector(other.length){
    for (auto i=0; i<other.length; i++) {vec[i] = other.vec[i];
}
}

// Move constructor 
Vector(Vector&& other)
:length(other.length),vec(other.vec){
        other.vec = nullptr;
        other.length = 0;
    }

// Destructor
~Vector(){
    delete[] vec;
    vec = nullptr;
    length = 0;
}

// Operators and functions

// Copy
Vector& operator=(const Vector& other){ 
    delete[] vec; 
    length = other.length; 
    vec = new T[length]; 
    for (auto i=0; i<length; i++) {
        vec[i] = other.vec[i]; 
    }
    
    return *this; 
} 

// Move
Vector& operator=(Vector&& other){  
    delete[] vec; 
    length = other.length; 
    vec = other.vec; 
    other.length = 0; 
    other.vec = nullptr; 
    return *this; 
} 

// operator []

T& operator[](int i) {
    return vec[i];
}

const T& operator[](int i) const {
    return vec[i];
}


// +- operators
template<typename U>
auto operator+(const Vector<U>& other)const
    ->Vector<typename std::common_type<T, U>::type>{
    if (length!= other.length) 
        throw std::invalid_argument("Vector lengths mismatch");
    
    //Creating the new data type and the sum of the vectors
    using type_sum = typename std::common_type<T,U>::type;
    Vector<type_sum> sum_Vector(length);

    for (int i = 0;i<length; i++){
        sum_Vector[i] = vec[i] + other.vec[i];
    }
    return sum_Vector;
}

template<typename U>
auto operator-(const Vector<U>& other)const
    ->Vector<typename std::common_type<T, U>::type>{
    if (length!= other.length) 
        throw std::invalid_argument("Vector lengths mismatch");
    
    //Creating the new data type and the sum of the vectors
    using type_minus = typename std::common_type<T,U>::type;
    Vector<type_minus> minus_Vector(length);

    for (int i = 0;i<length; i++){
        minus_Vector[i] = vec[i] - other.vec[i];
    }
    return minus_Vector;
}

template<typename S>
auto operator*(const S& scalar)const
    ->Vector<typename std::common_type<T, S>::type>{
    using type_scalar = typename std::common_type<T,S>::type;
    Vector<type_scalar> scalar_Vector(length);
    for (int i = 0;i<length; i++){
        scalar_Vector[i] = vec[i] * scalar;
    }
    return scalar_Vector;
}


int len()const{
    return length;
}


int length;
T* vec;
};

// This is outside the function not 100% sure about this
template<typename S, typename T>
auto operator*(const S& scalar,const Vector<T>& other) 
->Vector<typename std::common_type<S, T>::type>{
    return other * scalar;
}

template<typename T, typename U>
typename std::common_type<T,U>::type 
dot(const Vector<T>& lhs, 
    const Vector<U>& rhs)
{
    if (lhs.length!= rhs.length) 
        throw std::invalid_argument("Vector lengths mismatch");
   auto sum = lhs.vec[0] * rhs.vec[0]; 
   for(int i = 1; i< lhs.length;i++){
        sum += lhs.vec[i]*rhs.vec[i];
   }
   return sum;
}

template <typename T>
class Matrix

{     // Start your implementation of the matrix class here
public:
   int m;
   int n;
   std::map<std::pair<int,int>, T> M;



   Matrix(const int& row, const int& col)
    :m(row),n(col){}

// Not sure what the destructor has to be
   ~Matrix() = default;


    T& operator[](const std::pair<int, int>& ij){
        return M[ij];
    }
    
    const T& operator[](const std::pair<int, int>& ij) const{
        return M[ij];
    }

    const T& operator()(const std::pair<int,int>& ij) const {
    int i = ij.first;
    int j = ij.second;

    if (i < 0 || i >= m || j < 0 || j >= n) {
        throw std::out_of_range("Index out of bounds");
    }

    auto it = M.find(ij);
    if (it == M.end()) {
        throw std::out_of_range("Matrix entry not present");
    }
    return it->second;
}


};

template<typename T, typename U>
Vector<typename std::common_type<T,U>::type>
operator*(const Matrix<T>& lhs, const Vector<U>& rhs){
    if (lhs.n != rhs.len()){
        throw std::invalid_argument("Dimensions don't match");
        }
    Vector<typename std::common_type<T,U>::type> result_vec(lhs.m);
    for (int i = 0; i<lhs.m;i++){
        result_vec[i]=0;
    }
    for (auto it = lhs.M.begin(); it != lhs.M.end(); ++it){
        int i   = it->first.first;
        int j   = it->first.second;
        T value = it->second;
        result_vec[i] += value * rhs[j];
    }
    return result_vec;
    }










template<typename T>
int cg(const Matrix<T>& A,
       const Vector<T>& b,
             Vector<T>& x,
             T          tol = (T)1e-8,
             int        maxiter = 100)
{
    
    Vector<T> r = b - A * x;

    Vector<T> p = r;

    T rr_old = dot(r, r);

    if (rr_old < tol * tol) {
        return 0;
    }

    for (int k = 0; k < maxiter; ++k) {
        Vector<T> Ap = A * p;

        T alpha = rr_old / dot(Ap, p);

 
        x = x + alpha * p;

        r = r - alpha * Ap;

        T rr_new = dot(r, r);


        if (rr_new < tol * tol) {
            return k + 1;
        }

        T beta = rr_new / rr_old;


        p = r + beta * p;

        rr_old = rr_new;
    } 

    return -1;
}

template <int n, typename T>
class Heat {
public:
    T alpha;
    int m;          
    T dt;
    int N;          
    T dx;
    Matrix<T> M; 

    Heat(T input_alpha, int input_m, T input_dt)
        : alpha(input_alpha), 
        m(input_m), 
        dt(input_dt),
        N(1), 
        dx(1.0 / (input_m + 1)), 
        M(0, 0) 
    {

        N = static_cast<int>(std::pow(m, n));

        M = Matrix<T>(N, N);

        T diag_term = 1 + 2 * n * alpha * dt / (dx * dx);
        T off_term  = -alpha * dt / (dx * dx);


        for (int i = 0; i < N; ++i) {
            M[{i, i}] = diag_term;

            for (int d = 0; d < n; ++d) {
                int step = 1;
                for (int k = 0; k < d; ++k)
                    step *= m;

                int coord = (i / step) % m;

                if (coord > 0)
                    M[{i, i - step}] = off_term;
                if (coord < m - 1)
                    M[{i, i + step}] = off_term;
            }
        }
    }


    Vector<T> exact(const T &t) const {
    Vector<T> result(N);

    T factor = std::exp(-n * M_PI * M_PI * alpha * t);

    for (int i = 0; i < N; ++i) {
        T value = factor;

        int idx = i;
        for (int d = 0; d < n; ++d) {
            int coord = idx % m;
            idx /= m;
            

            T x = (coord + 1) * dx;

            value *= std::sin(M_PI * x);
        }

        result[i] = value;
    }

    return result;
}

    Vector<T> solve(T t) const {
        int steps = static_cast<int>(t / dt);

        Vector<T> u = exact(0);   

        for (int k = 0; k < steps; ++k) {
            Vector<T> u_new = u;
            cg(M, u, u_new);     
            u = u_new;
        }

        return u;
    }
};


int main(int argc, char* argv[])
{
    // Your testing of the Heat class starts here
    Heat<2, double> H(0.3125, 20, 0.001);
    //std::cout << H.M({0,0}) << std::endl;
    double t = 1;

    auto sole = H.exact(t);
    auto sola = H.solve(t);
    double exact = 0;
    double error = 0;
    for (int i = 0; i<20*20 ; i++){

        std::cout << sola[i] << ',';
        //std::cout << sole[i] << " exact" <<std::endl;
        //std::cout << sola[i] << " approx" <<  std::endl;
        error += std::abs(sole[i] - sola[i]);
        exact += std::abs(sole[i]);
    }

    //std::cout << error/exact*100 << " error" << std::endl;
    return 0;
}
