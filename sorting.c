#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, j, N, *v, temp;
	time_t T = 1;
	
	// Create N random integers
	srand(time(&T));
	N = 10;
	v = (int *) malloc( N * sizeof(int) );
	for(i=0;i<N;++i)
	{
		v[i] = rand() % 100;
		printf("%d,",v[i]);
	}
	printf("\n");
	
	// Bubble Sort
	// compare v[i] and v[j], 
	// if v[i] > v[j] then v[i] <-> v[j]
	// �ѥ���k�A�۾F������A���j�̩��k���A
	// �̫�̤j�ȷ|�X�{�b�}�C�k�ݡC
	// ���j�B�z�|���ƧǪ� N-1 �Ӥ����C
	for(i=0;i<N-1;++i) // �ѥ���k  N-1 need your attention
	{
		if(v[i]>v[i+1]) // �۾F�����: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
		{					// ���j�̩��k��
			temp = v[i];	// ����u�g�U���o��... 
			v[i] = v[i+1];	// V[0] = V[1]
			v[i+1] = temp;  // V[1] = V[0]
		}
	}
	for(i=0;i<N;++i) // �ѥ���k  N-1 need your attention
	{
		printf("%d,",v[i]);
	}
	printf("\n");

	for(i=0;i<N-2;++i) // �ѥ���k  N-1 need your attention
	{
		if(v[i]>v[i+1]) // �۾F�����: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
		{					// ���j�̩��k��
			temp = v[i];	// ����u�g�U���o��... 
			v[i] = v[i+1];	// V[0] = V[1]
			v[i+1] = temp;  // V[1] = V[0]
		}
	}
	
	for(i=0;i<N;++i) // �ѥ���k  N-1 need your attention
	{
		printf("%d,",v[i]);
	}
	printf("\n");
	// �`����@���ƻs�K�W�K�즺�a�K
	for(j=1;j<N;++j)
	{
		for(i=0;i<N-j;++i) // �ѥ���k  N-1 need your attention
		{
			if(v[i]>v[i+1]) // �۾F�����: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
			{					// ���j�̩��k��
				temp = v[i];	// ����u�g�U���o��... 
				v[i] = v[i+1];	// V[0] = V[1]
				v[i+1] = temp;  // V[1] = V[0]
			}
		}
		for(i=0;i<N;++i) // �ѥ���k  N-1 need your attention
		{
			printf("%d,",v[i]);
		}
		printf("\n");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
