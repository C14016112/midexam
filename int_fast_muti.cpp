#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
int ISPRIME(int p) ;
int FINDPRIME(int N ) ;
int FINDBASIS(int p, int t);
int INITIAL(int *x, int value, int & N)  ; 
void FFT(int *x, int *y,  int N, int p, int W)  ;
void iFFT(int *x, int *y,  int N, int p, int W)  ;
// ifft �ȬO�� fft ���� W ���� W^-1
// �{���X�����ۦP 
int FMU( int value1, int value2) ; 
void test() ; 
int main()
{   int value1, value2 ; 
	cout << "Please enter the number you want to multiple." << endl ;
	cin >> value1 >> value2 ; 
	cout << FMU(value1, value2) << endl ;
//	test() ;
// test() �O�@�Ӵ��զ��S�����~���禡�A���0~100000���Ʀr�ۭ��A�bFMU�M�����ۭ������p�U����50�����~�t 
}

int ISPRIME(int p)
{	// �ˬd P  �O�_�O�@�ӽ�ơA�Y�O�A�^��1�A�_�h�^��0 
	int i = 2 ; 
	while ( (p%i)!= 0 && i < sqrt(p) )	
	{	i ++ ; 	}
	if ( (p%i) != 0  ) return 1 ; // if p is prime, cout 1. else cout 0.
	else	return 0 ; 	
	
}

int FINDPRIME(int N )
{	//���ơA N�O��J�}�C�����סA��@�ӽ��P�ϱoP�j��81*N
	//and P = 1+ N*k for some integer k  
	int p = 1 ; 
	int r = 0 ; 
	while(r == 0 )
	{
		if ( p > 81*(N) && ISPRIME(p) == 1 ) 	r = 1 ;
		else 	p += N ; 
	}
	return p ; 
}

int FINDBASIS(int p, int t)
{	// �w����P�A�}�C����t�A��@�ӭ�W�ϱo
	// W^t = 1 mod p , and W^k != 1 for all 0 < k < 8  
	int i = 1 ;
	while( i <  p  )
	{
		int m = 1 ; 
		for ( int k = 0 ; k< t ; k ++)
		{
			m *= i ; 
			m = m % p ; 
		}
		if ( m == 1 )
		{
			m = 1 ; 
			for ( int j = 0 ; j < t-1 ; j ++) 
			{	
				m *= i ; 
				m = m % p ; 
				if ( m == 1 ) break ; 
			}
			if ( m!= 1 ) return i ; 	
		}
		i++ ; 
	}
	return 0 ; 
}

int INITIAL(int *x,  int value, int &N )  
{	// �N���value� sum a(k) * 10 ^k , k = 0 .. N-1 ;  
	int i = 0 ; 
	while ( value > 0 )
	{
		x[i] = value % 10 ; 
		value = (value-x[i]) / 10 ; 
		i++ ; 
	}
	while ( i < N ) 
	{
		x[i] = 0 ; 
		i ++  ;
	}
}

/* x ��J�x�}	y ��X�x�}	N �x�}��size�A����2^k 
	p : �ҧ䪺��ơA�إߦb Zp �W�� 
	W : W^8 = 1 and W^k != 1 if 0 < k < 8 ; 
*/ 
void FFT(int *x, int *y,  int N, int p, int W)  
{
	// ��@�� { 0 ... N } ���x�}����bitreverse 
	// �A�Nx[i] ��D���ө�y����m 
	int *z ;
	z = (int*)malloc(N*sizeof(int)) ; 
	for ( int i = 0 ; i<N ; i++)	z[i] = i ; 
	int i = 0 , j = 0, M ;
	while ( i < N)
	{
		z[i] = j ; 
		M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	}
	for ( int i = 0 ; i < N ; i++ ) 
	{
		int t = z[i];
		y[i] = x[t] ; 	
	}
	free(z) ; 
	
	// �������A��n=2�}�l�A����n=N���� 
	int n = 2 ;
	int WW = 1 ; 
	while (n<=N)
	{	int WW = 1 ; // WW = W^(N/n)
		for ( int i = 0 ; i< N/n ; i++) WW = WW*W %p ; 
		int WWW = 1 ; 
		for ( int i = 0 ; i< n/2 ; i++)
		{	
			// theta = -2.0*i*M_PI/n 
			for ( int j = i ; j < N ; j += n )
			{
				int k = j + n/2 ;
				int temp = y[k]*WWW % p ;
				
				if ( (y[j] - temp) < 0) y[k] = (p+(y[j]%p)-(temp%p)) %p; 
				else 	y[k] = (y[j]-temp) % p ; 
				y[j] = (y[j]+temp) % p ;
			}
			WWW = WWW*WW % p ; //WWW = WW^i ; 
		}
		n *=2  ;
	}
	for ( int i = 0 ; i< N ; i++) y[i] = y[i] % p ; 
}


void iFFT(int *x, int *y,  int N, int p, int W)  
{
	// ��@�� { 0 ... N } ���x�}����bitreverse 
	// �A�Nx[i] ��D���ө�y����m 
	int *z ;
	z = (int*)malloc(N*sizeof(int)) ; 
	for ( int i = 0 ; i<N ; i++)	z[i] = i ; 
	int i = 0 , j = 0, M ;
	while ( i < N)
	{
		z[i] = j ; 
		M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	}
	for ( int i = 0 ; i < N ; i++ ) 
	{
		int t = z[i];
		y[i] = x[t] ; 	
	}
	free(z) ; 
	
	// �������A��n=2�}�l�A����n=N���� 
	int n = 2 ;
	int WW = 1 ; 
	while (n<=N)
	{	int WW = 1 ; // WW = W^(N/n)
		for ( int i = 0 ; i< N/n ; i++) WW = WW*W %p ; 
		int WWW = 1 ; 
		for ( int i = 0 ; i< n/2 ; i++)
		{	
			// theta = -2.0*i*M_PI/n 
			for ( int j = i ; j < N ; j += n )
			{
				int k = j + n/2 ;
				int temp = y[k]*WWW % p ;
				
				if ( (y[j] - temp) < 0) y[k] = (p+(y[j]%p)-(temp%p)) %p; 
				else 	y[k] = (y[j]-temp) % p ; 
				y[j] = (y[j]+temp) % p ;
			}
			WWW = WWW*WW % p ; //WWW = WW^i ; 
		}
		n *=2  ;
	}
	for ( int i = 0 ; i< N ; i++) y[i] = y[i] % p ; 
	
	// ���ઽ����N�A�n���HN�bZP����inverse 
	// �Dinverse 
	int k = 1 ; 
	int inverse = 0 ; 
	for ( int i = 0 ; i< p ; i++)
	{
		int s = k ; 
		k = k * N % p ; 
		if ( k == 1 ) 
		{
			inverse = s ; 
			break ; 
		}
	}
	for ( int i = 0 ; i < N ; i ++) y[i] = y[i] * inverse % p  ; 
	
}

int FMU( int value1, int value2) 
{
	int *x,  *X, *y, *Y, *XY, *xy ; 
	int N=1, p=0 , W=1, W_1=1, value ; 
//	cout << "Please input the int number you want to do fft :" ;
	if (value1 > value2 ) value = value1 ; // ������j������ǡA��X�}�C�j�p 
	else value = value2 ; 
	while ( N < 2*((int)log10(value) +1)  )
	{
		N *= 2 ; 
	}
	p = FINDPRIME(N) ; 
	W = FINDBASIS(p, N) ; // basis element 

	for ( int i = 0 ; i< N-1; i ++) W_1 = W_1*W % p ; // W_1 = W^(N-1) 
//	cout <<  "The basis of fft is " << W_1 
//		<< " under Z " << p << "." << endl ;
	x = (int*) malloc( N*sizeof(int)) ; 
	y = (int*) malloc( N*sizeof(int)) ; 
	X = (int*) malloc( N*sizeof(int)) ; 
	Y = (int*) malloc( N*sizeof(int)) ; 
	xy = (int*) malloc( N*sizeof(int)) ; 
	XY = (int*) malloc( N*sizeof(int)) ; 
	
	INITIAL(x, value1, N) ; 
	INITIAL(y, value2, N) ; 
	INITIAL(X, 0, N) ; 
	INITIAL(Y, 0, N) ; 
	INITIAL(XY, 0, N) ; 
	INITIAL(xy, 0, N) ; 
	// x,y :��J�禡
	// X,Y :x �My FFT�᪺���G
	// XY = X.*Y 
	// xy : XY IFFT �᪺���G 
	FFT(x, X, N, p, W_1) ; // x -> F(x) = X
	FFT(y, Y, N, p, W_1) ; // y -> F(y) = Y 
							// X.*Y -> F^-1(X.*Y) = x*y
	for ( int i = 0 ; i< N ; i++) XY[i] = (X[i]*Y[i] )%p ; 
	iFFT(XY, xy, N, p, W) ;
	
	// �p���`�X
	// sum a(k)*10^k k = 0 .. N-1 ; 
	int answer = 0 ; 
	for ( int i = 0 ; i< N ; i ++)
	{
		int pow = 1 ; 
		for ( int j = 0 ; j<i ; j++) pow = pow*10 ; 
		answer += pow*xy[i] ; 
	}
	free(x) ; 
	free(X) ; 
	free(y) ; 
	free(Y) ; 
	free(xy) ; 
	free(XY) ; 
	return answer ; 
}

void test()
{
	srand(0) ; 
	int error = 0 , sum = 0 ; 
	for ( int i = 0 ; i < 100 ; i++)
	{
		
		int value1 = rand()&100000, value2 = rand()%100000 ; 
		int f = FMU(value1, value2 ) ; 
		error = value1*value2 - f ; 
//		cout << "The true answer of " << value1 << " X " << value2 << "is " << value1 * value2 << endl 
//			<< "The result of FMU is " << f << endl 
//			<< "The error is " << error << endl ;
		sum += error ; 
	}
	cout << "The total error is : " << sum  << endl ; 
}
