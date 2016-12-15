#include<stdio.h>
#include<stdlib.h>
#include<time.h>

float** Naive(float**,float**,int);
float** div_conq(float**,float**,int);
float** strassen(float**,float**,int);
float** strassen_p(float** m1,float** m2,int n);
float** add(float**,float**,int);
float** sub(float**,float**,int);
float** alloc_array(int r, int c);
float** copy_array(float** b,int index1,int index2,int index3,int index4,int size);
void print(float **,int);
void free_array(float **a, int r);
double computeTime(struct timespec start,struct timespec end);
void* threadFunc(void* p);
struct dac
{
	int n;
	float** mat1;
	float** mat2;
};
struct final
{
	float** mat;
};

int main()
{

	int n,i,j,m;
	float **m1;
	float **m2;
	float **m3;
	struct timespec start,end;
	printf("enter the size of the matrix\n");
	scanf("%d",&n);
	/*m1 = (float**)malloc(sizeof(float*)*n);
	for(i=0;i<n;i++)
	{
		m1[i]= (float*)malloc(sizeof(float)*n);
	}
	m2 = (float**)malloc(sizeof(float*)*n);
	for(i=0;i<n;i++)
	{
		m2[i]= (float*)malloc(sizeof(float)*n);
	}*/
	//m1 = alloc_array(n,n);
	//m2 = alloc_array(n,n);
	m1 = malloc(sizeof(float*)*n);
	m2 = malloc(sizeof(float*)*n);
		for(m=0;m<n;m++)
		{
			m1[m]=malloc(sizeof(float)*n);
			m2[m] = malloc(sizeof(float)*n);
		}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			m1[i][j] = ((float)rand()/(float)(RAND_MAX))*5.0;
			m2[i][j] = ((float)rand()/(float)(RAND_MAX))*5.0;
		}
	}
	/*printf("matrix1\n");
	print(m1,n);
	printf("\n");
	printf("matrix2\n");
	print(m2,n);
	printf("\n");*/
	/*m3 = Naive(m1,m2,n);
	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%f\t",m3[i][j]);
		}
		printf("\n");
	}*/
	printf("by naive\n");
	
	/*clock_gettime(CLOCK_REALTIME,&start);
	m3 = Naive(m1,m2,n);
	clock_gettime(CLOCK_REALTIME,&end);
	//print(m3,n);
	printf("Execution time of first matrix :%lf ms\n",computeTime(start,end));
	free_array(m3,n);
	free(m3);*/
	
	printf("by normal\n");
	clock_gettime(CLOCK_REALTIME,&start);
	m3 = strassen(m1,m2,n);
	clock_gettime(CLOCK_REALTIME,&end);
	//print(m3,n);
	free_array(m3,n);
	free(m3);
	printf("Execution time :%lf ms\n",computeTime(start,end));

	clock_gettime(CLOCK_REALTIME,&start);
	m3 = strassen_p(m1,m2,n);
	clock_gettime(CLOCK_REALTIME,&end);
	//print(m3,n);
	free_array(m3,n);
	free(m3);
	printf("Execution time of parallel :%lf ms\n",computeTime(start,end));

	free_array(m1,n);
	free(m1);
	free_array(m2,n);
	free(m2);
		
	return 0;
	//printf("by stras\n");
	//print(strassen(m1,m2,n),n);


}
float** Naive(float** m1,float** m2,int n)
{
	int i,j,k,m;
	float** m3;
	//m3 = alloc_array(n,n);
	m3=malloc(sizeof(float*)*n);
	for(m=0;m<n;m++)
	{
		m3[m]=malloc(sizeof(float)*n);
	}

	for(i=0;i<n;i++)
	{
        	for(j=0;j<n;j++)
		{
            		m3[i][j] = 0;
            		for(k=0;k<n;k++)
			{
                		m3[i][j] = m3[i][j] + (m1[i][k]*m2[k][j]);
			}
		}
	}
	return m3;
}
void* threadFunc(void* p)
{
	//int n = *((int *) arg);
	struct dac* f=p;
	float **temp;
	temp = strassen(f->mat1,f->mat2,f->n);
	struct final *t=malloc(sizeof(struct final));;
	t->mat=temp;
	
	return t;
}

float** strassen_p(float** m1,float** m2,int n)
{
	float **a11;
	float **a12;
	float **a21;
	float **a22;
	float **b11;
	float **b12;
	float **b21;
	float **b22;
	float **c1;
	float **c2;
	float **c3;
	float **c4;
	float **c;
	float **add1;
	float **add2;
	float **add3;
	float **add4;
	float **add5;
	float **add6;
	float **add7;
	float **add8;
	float **sub1;
	float **sub2;
	float **sub3;
	float **sub4;
	float **sub5;
	float **sub6;
	
	if(n==1)
	{
		return Naive(m1,m2,n);
	}
	else
	{

		/*a11 = alloc_array(n/2,n/2);
		a12 = alloc_array(n/2,n/2);
		a21 = alloc_array(n/2,n/2);
		a22 = alloc_array(n/2,n/2);
		b11 = alloc_array(n/2,n/2);
		b12 = alloc_array(n/2,n/2);
		b21 = alloc_array(n/2,n/2);
		b22 = alloc_array(n/2,n/2);

		c1 = alloc_array(n/2,n/2);
		c2 = alloc_array(n/2,n/2);
		c3 = alloc_array(n/2,n/2);
		c4 = alloc_array(n/2,n/2);*/
		c = alloc_array(n,n);
		
		a11 = copy_array(m1,0,0,n/2,n/2,n/2);
		a12 = copy_array(m1,0,n/2,n/2,n,n/2);
		a21 = copy_array(m1,n/2,0,n,n/2,n/2);
		a22 = copy_array(m1,n/2,n/2,n,n,n/2);
		b11 = copy_array(m2,0,0,n/2,n/2,n/2);
		b12 = copy_array(m2,0,n/2,n/2,n,n/2);
		b21 = copy_array(m2,n/2,0,n,n/2,n/2);
		b22 = copy_array(m2,n/2,n/2,n,n,n/2);
		
		//print(a11,n/2);
		//print(a12,n/2);
		pthread_t recursive_dac[8];
	
		
		add1 = add(a11,a22,n/2);
		add2 = add(b11,b22,n/2);
		struct dac *p1=malloc(sizeof(struct dac));
		p1->n = n/2; p1->mat1= add1 ; p1->mat2 = add2;
		pthread_create(&recursive_dac[0],NULL,&threadFunc,p1);

		add3 = add(a21,a22,n/2);
		struct dac *p2=malloc(sizeof(struct dac));
		p2->n = n/2; p2->mat1 = add3 ; p2->mat2 = b11;
		pthread_create(&recursive_dac[1],NULL,&threadFunc,p2);
		
		sub1 = sub(b12,b22,n/2);		
		struct dac *p3=malloc(sizeof(struct dac));
		p3->n = n/2; p3->mat1 = a11 ; p3->mat2 = sub1;
		pthread_create(&recursive_dac[2],NULL,&threadFunc,p3);
	
		sub2 = sub(b21,b11,n/2);		
		struct dac *p4=malloc(sizeof(struct dac));
		p4->n = n/2; p4->mat1 = a22 ; p4->mat2 = sub2;
		pthread_create(&recursive_dac[3],NULL,&threadFunc,p4);

		add4 = add(a11,a12,n/2);	
		struct dac *p5=malloc(sizeof(struct dac));
		p5->n = n/2; p5->mat1 = add4 ; p5->mat2 = b22;
		pthread_create(&recursive_dac[4],NULL,&threadFunc,p5);
		
		sub3 = sub(a21,a11,n/2);
		add5 = add(b11,b12,n/2);	
		struct dac *p6=malloc(sizeof(struct dac));
		p6->n = n/2; p6->mat1 = sub3 ; p6->mat2 = add5;
		pthread_create(&recursive_dac[5],NULL,&threadFunc,p6);

		sub4 = sub(a12,a22,n/2);
		add6 = add(b21,b22,n/2);	
		struct dac *p7=malloc(sizeof(struct dac));
		p7->n = n/2; p7->mat1 = sub4 ; p7->mat2 = add6;
		pthread_create(&recursive_dac[6],NULL,&threadFunc,p7);
		

		struct final *temp1;struct final *temp2; struct final *temp3; struct final *temp4;
		struct final *temp5; struct final *temp6; struct final *temp7;
	
		pthread_join(recursive_dac[0],(void **)&temp1);
		pthread_join(recursive_dac[1],(void **)&temp2);
		pthread_join(recursive_dac[2],(void **)&temp3);
		pthread_join(recursive_dac[3],(void **)&temp4);
		pthread_join(recursive_dac[4],(void **)&temp5);
		pthread_join(recursive_dac[5],(void **)&temp6);
		pthread_join(recursive_dac[6],(void **)&temp7);
		
		add7 = add(temp1->mat,temp4->mat,n/2);
		sub5 = sub(add7,temp5->mat,n/2);
		
		c1 = add(sub5,temp7->mat,n/2);
        	c2 = add(temp3->mat,temp5->mat,n/2);
        	c3 = add(temp2->mat,temp4->mat,n/2);
		sub6 = sub(temp1->mat,temp2->mat,n/2);
		add8 = add(sub6,temp3->mat,n/2);
		
        	c4 = add(add8,temp6->mat,n/2);
		
		
		int k=0,g=0,i,j;

		for(i=0;i<n/2;i++)
		{

			k=0;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c1[i][j];
				k++;
			}
			g++;
		}
		g = 0;
		k = n/2;
		for(i=0;i<n/2;i++)
		{
			k = n/2;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c2[i][j];
				k++;
			}
			g++;
		}
		g = n/2;
		k=0;
		for(i=0;i<n/2;i++)
		{
			k = 0;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c3[i][j];
				k++;
			}
			g++;
		}
		g = n/2;
		k=n/2;
		for(i=0;i<n/2;i++)
		{
			k = n/2;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c4[i][j];
				k++;
			}
			g++;
		}
		//print(c,n);
		
		free_array(a11,n/2);
		free_array(a12,n/2);
		free_array(a21,n/2);
		free_array(a22,n/2);
		free_array(b11,n/2);
		free_array(b12,n/2);
		free_array(b21,n/2);
		free_array(b22,n/2);
		free_array(c1,n/2);
		free_array(c2,n/2);
		free_array(c3,n/2);
		free_array(c4,n/2);
		free(a11);
		free(a12);
		free(a21);
		free(a22);
		free(b11);
		free(b12);
		free(b21);
		free(b22);
		free(c1);
		free(c2);
		free(c3);
		free(c4);

		free_array(add1,n/2);
		free(add1);
		free_array(add2,n/2);
		free(add2);
		free_array(add3,n/2);
		free(add3);
		free_array(add4,n/2);
		free(add4);
		free_array(add5,n/2);
		free(add5);
		free_array(add6,n/2);
		free(add6);
		free_array(sub1,n/2);
		free(sub1);
		free_array(sub2,n/2);
		free(sub2);
		free_array(sub3,n/2);
		free(sub3);
		
		
		
		free_array(add7,n/2);
		free(add7);
		free_array(sub4,n/2);
		free(sub4);
		free_array(sub5,n/2);
		free(sub5);
		free_array(sub6,n/2);
		free(sub6);
		
		free_array(add8,n/2);
		free(add8);
		free_array(temp1->mat,n/2);free_array(temp2->mat,n/2);free_array(temp3->mat,n/2);
		free_array(temp4->mat,n/2);free_array(temp5->mat,n/2);free_array(temp6->mat,n/2);free_array(temp7->mat,n/2);
		free(temp1->mat);free(temp2->mat);free(temp3->mat);free(temp4->mat);free(temp5->mat);free(temp6->mat);free(temp7->mat);
		free(temp1);free(temp2);free(temp3);free(temp4);free(temp5);free(temp6);free(temp7);

		free(p1);free(p2);free(p3);free(p4);free(p5);free(p6);free(p7);
	
		return c;



	}
}
float** strassen(float** m1,float** m2,int n)
{
	float **a11;
	float **a12;
	float **a21;
	float **a22;
	float **b11;
	float **b12;
	float **b21;
	float **b22;
	float **c1;
	float **c2;
	float **c3;
	float **c4;
	float **c;
	float **M1;
	float **M2;
	float **M3;
	float **M4;
	float **M5;
	float **M6;
	float **M7;
	float **add1;
	float **add2;
	float **add3;
	float **add4;
	float **add5;
	float **add6;
	float **add7;
	float **add8;
	float **sub1;
	float **sub2;
	float **sub3;
	float **sub4;
	float **sub5;
	float **sub6;
	
	if(n==1)
	{
		return Naive(m1,m2,n);
	}
	else
	{

		/*a11 = alloc_array(n/2,n/2);
		a12 = alloc_array(n/2,n/2);
		a21 = alloc_array(n/2,n/2);
		a22 = alloc_array(n/2,n/2);
		b11 = alloc_array(n/2,n/2);
		b12 = alloc_array(n/2,n/2);
		b21 = alloc_array(n/2,n/2);
		b22 = alloc_array(n/2,n/2);

		c1 = alloc_array(n/2,n/2);
		c2 = alloc_array(n/2,n/2);
		c3 = alloc_array(n/2,n/2);
		c4 = alloc_array(n/2,n/2);*/
		c = alloc_array(n,n);
		
		a11 = copy_array(m1,0,0,n/2,n/2,n/2);
		a12 = copy_array(m1,0,n/2,n/2,n,n/2);
		a21 = copy_array(m1,n/2,0,n,n/2,n/2);
		a22 = copy_array(m1,n/2,n/2,n,n,n/2);
		b11 = copy_array(m2,0,0,n/2,n/2,n/2);
		b12 = copy_array(m2,0,n/2,n/2,n,n/2);
		b21 = copy_array(m2,n/2,0,n,n/2,n/2);
		b22 = copy_array(m2,n/2,n/2,n,n,n/2);
		
		//print(a11,n/2);
		//print(a12,n/2);
		add1 = add(a11,a22,n/2);
		add2 = add(b11,b22,n/2);
		M1 = strassen(add1,add2,n/2);
	
		add3 = add(a21,a22,n/2);
       	 	M2 = strassen(add3,b11,n/2);
	
		sub1 = sub(b12,b22,n/2);
        	M3 = strassen(a11,sub1,n/2);

		sub2 = sub(b21,b11,n/2);
        	M4 = strassen(a22,sub2,n/2);

		add4 = add(a11,a12,n/2);
        	M5 = strassen(add4,b22,n/2);

		sub3 = sub(a21,a11,n/2);
		add5 = add(b11,b12,n/2);
        	M6 = strassen(sub3,add5,n/2);

		sub4 = sub(a12,a22,n/2);
		add6 = add(b21,b22,n/2);
		M7 = strassen(sub4,add6,n/2);
		
		
		add7 = add(M1,M4,n/2);
		sub5 = sub(add7,M5,n/2);
		
		c1 = add(sub5,M7,n/2);
        	c2 = add(M3,M5,n/2);
        	c3 = add(M2,M4,n/2);
		sub6 = sub(M1,M2,n/2);
		add8 = add(sub6,M3,n/2);
		
        	c4 = add(add8,M6,n/2);
		
		
		int k=0,g=0,i,j;

		for(i=0;i<n/2;i++)
		{

			k=0;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c1[i][j];
				k++;
			}
			g++;
		}
		g = 0;
		k = n/2;
		for(i=0;i<n/2;i++)
		{
			k = n/2;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c2[i][j];
				k++;
			}
			g++;
		}
		g = n/2;
		k=0;
		for(i=0;i<n/2;i++)
		{
			k = 0;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c3[i][j];
				k++;
			}
			g++;
		}
		g = n/2;
		k=n/2;
		for(i=0;i<n/2;i++)
		{
			k = n/2;
			for(j=0;j<n/2;j++)
			{
				c[g][k] = c4[i][j];
				k++;
			}
			g++;
		}
		//print(c,n);
		
		free_array(a11,n/2);
		free_array(a12,n/2);
		free_array(a21,n/2);
		free_array(a22,n/2);
		free_array(b11,n/2);
		free_array(b12,n/2);
		free_array(b21,n/2);
		free_array(b22,n/2);
		free_array(c1,n/2);
		free_array(c2,n/2);
		free_array(c3,n/2);
		free_array(c4,n/2);
		free(a11);
		free(a12);
		free(a21);
		free(a22);
		free(b11);
		free(b12);
		free(b21);
		free(b22);
		free(c1);
		free(c2);
		free(c3);
		free(c4);

		free_array(add1,n/2);
		free(add1);
		free_array(add2,n/2);
		free(add2);
		free_array(add3,n/2);
		free(add3);
		free_array(add4,n/2);
		free(add4);
		free_array(add5,n/2);
		free(add5);
		free_array(add6,n/2);
		free(add6);
		free_array(sub1,n/2);
		free(sub1);
		free_array(sub2,n/2);
		free(sub2);
		free_array(sub3,n/2);
		free(sub3);
		free_array(M1,n/2);
		free(M1);
		free_array(M2,n/2);
		free(M2);
		free_array(M3,n/2);
		free(M3);
		free_array(M4,n/2);
		free(M4);
		free_array(M5,n/2);
		free(M5);
		free_array(M6,n/2);
		free(M6);
		free_array(M7,n/2);
		free(M7);
		
		
		
		free_array(add7,n/2);
		free(add7);
		free_array(sub4,n/2);
		free(sub4);
		free_array(sub5,n/2);
		free(sub5);
		free_array(sub6,n/2);
		free(sub6);
		
		free_array(add8,n/2);
		free(add8);

		return c;



	}
}

//Allocates 2D array of ints having r rows and c columns
float** alloc_array(int r, int c)
{
	float **a;
	int i;
	a = (float **) malloc(r * sizeof(float *)); //r rows
	for(i = 0; i < c; i++)
	{
		a[i]=(float*)malloc(c*sizeof(float)); //cols for i​ th​  row
	}
	return a;
}

//Frees an allocated 2D array having r rows
void free_array(float **a, int r)
{
	int i;
	for(i = 0; i < r; i++)
	{
		free(a[i]);
	}
}
float** copy_array(float** b,int index1,int index2,int index3,int index4,int size)
{
	int g=0,k,i,j,m;
	float** a;
	//a = alloc_array(size,size);
	a = malloc(sizeof(float*)*size);
		for(m=0;m<size;m++)
		{
			a[m]=malloc(sizeof(float)*size);
		}

	for(i=index1;i<index3;i++)
	{
		k=0;
		for(j=index2;j<index4;j++)
		{
				a[g][k] = b[i][j];
				k++;

		}
		g++;
	}
	return a;
}
void print(float **a,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%.2f ",a[i][j]);
		}
		printf("\n");
	}
}
float** add(float** a,float** b,int n)
{
	float** c;
	int m;
	//c = alloc_array(n,n);
	c = malloc(sizeof(float*)*n);
		for(m=0;m<n;m++)
		{
			c[m]=malloc(sizeof(float)*n);
		}


	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i][j] = a[i][j]+b[i][j];
		}
	}
	return c;
}
float** sub(float** a,float** b,int n)
{
	float** c;
	int i,j,m;
	//c = alloc_array(n,n);
	c = malloc(sizeof(float*)*n);
		for(m=0;m<n;m++)
		{
			c[m]=malloc(sizeof(float)*n);
		}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i][j] = a[i][j]-b[i][j];
		}
	}
	return c;
}
double computeTime(struct timespec start,struct timespec end)
{
	double t = 0;
	t += (end.tv_sec - start.tv_sec)*1000;
	t += (end.tv_nsec - start.tv_nsec)*0.000001;
	return t;
}	







