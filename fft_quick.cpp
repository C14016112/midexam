#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iomanip>
#include<time.h>
using namespace std;

int FFT( double* x_r, double* x_i, double* y_r, double* y_i, int N ) ; 
int main()
{
	// y_k = sum( x_n * w^{-kn}, n=0..N-1}
	// w = cos(2*pi / N) + i*sin(2*pi/N)
	
	double *y_r, *y_i, *x_r, *x_i, w_r, w_i, t1, t2 ; 
									// x_r : real part of x 
									// x_i : image part of x 
									// y_r : real part of y
									// y_i : image part of y
	int k, n, N, p ;  // in put an integer to N 
	cout << "Please enter an interger:" ;
	cin  >> p ; 
	N=1 << p  ;
	cout << "N=" << N << endl ;
	
	// create memory of x, y 
	x_r = (double*) malloc ( N*sizeof(double)) ; 
	x_i = (double*) malloc ( N*sizeof(double)) ; 
	y_r = (double*) malloc ( N*sizeof(double)) ; 
	y_i = (double*) malloc ( N*sizeof(double)) ; 
	
	for ( int i = 0 ; i < N ; i++) 
	{
		x_r[i] = i ; 
		x_i[i] = 0 ;
	}
	

	

	t1 = clock() ; 
	
	FFT( x_r, x_i, y_r, y_i, N ) ; 
	
	t2 = clock() ; 
	
		
	for ( int i = 0 ; i< N ; i++) 
	{
		cout << setprecision(6)  
			 << "第" << i << "個y的實部為:" << y_r[i] << "  "
			 << "第" << i << "個y的虛部為:" << y_i[i] << "i" << " " << endl ;
			 
	}
	cout << (t2-t1)/1000 << endl ;
	
	return 0 ;
	
}


// yk = sum ( x(n) * w^(-kn) , n=0..N-1)
// yk = sum ( x(n) 
int FFT( double* x_r, double* x_i, double* y_r, double* y_i, int N )  
{
	if ( N==1)
	{
		y_r[0] = x_r[0] ; 
		y_i[0] = x_i[0] ; 
		return 0 ;
	}
	int k, n ;
	double *u_r, *u_i, *v_r, *v_i , w_r, w_i ; 
	
	u_r = (double*) malloc(N*sizeof(double)) ; 
	u_i = (double*) malloc(N*sizeof(double)) ; 
	v_r = (double*) malloc(N*sizeof(double)) ; 
	v_i = (double*) malloc(N*sizeof(double)) ; 
	
	for ( n=0 ; n< N/2 ; n++)
	{
		u_r[n] = x_r[2*n] ; // even terms of real part of x puts in first n terms of u_r
		u_i[n] = x_i[2*n] ; // even terms of image part of x puts in first n terms of u_i
		u_r[n+N/2] = x_r[2*n+1] ; // odd terms of real part of x puts in last n terms of u_r
		u_i[n+N/2] = x_i[2*n+1] ; // odd terms of real part of x puts in last n terms of u_r
	}
	FFT(u_r, u_i, v_r, v_i, N/2 ) ; 
	FFT(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2 ) ; 
	
	// compute y 
	for ( k = 0 ; k<N/2; k++) 
	{
		// w^{-k} 
		w_r = cos(-k*2*M_PI/N) ; 
		w_i = sin(-k*2*M_PI/N) ; 
		y_r[k] = u_r[k] + w_r*u_r[k+N/2] - w_i*u_i[k+N/2] ;
		y_i[k] = u_i[k] + w_r*u_i[k+N/2] + w_i*u_r[k+N/2] ;
		y_r[k+N/2] = u_r[k] - (w_r*u_r[k+N/2] - w_i*u_i[k+N/2] ) ;
		y_i[k+N/2] = u_i[k] - (w_r*u_i[k+N/2] + w_i*u_r[k+N/2] ) ; 
	}
	free(u_r) ; 
	free(u_i) ; 
	free(v_r) ; 
	free(v_i) ;
	
}

