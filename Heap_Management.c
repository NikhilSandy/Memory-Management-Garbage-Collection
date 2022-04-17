#include <stdio.h>
#include <stdlib.h>

#define HEAP_START_ADDR 0
#define HEAP_LEN  10000
#define HEAP_END_ADDR HEAP_START_ADDR + HEAP_LEN - 1

struct Node
{
	int base_add;
	int size;
	struct Node *next;

}*lptr = NULL;

// Memory is allocated using first fit algorithm
int Allocate(int size)
{
	int res = -1; 
	
	if(size > 0) 
	{
		if(lptr == NULL)
		{
			//When Allocate is called for the first time haed of ll is intialised
			if(size <= HEAP_LEN) 
			{
				struct Node *nptr = (struct Node*)malloc(sizeof(struct Node));
				nptr->size = size;
				nptr->base_add = HEAP_START_ADDR;
				nptr->next = NULL;
				lptr = nptr;
				res = lptr->base_add;
			}
		}
		
		else 
		{
		    
			struct Node *curr;
			curr = lptr;
			int flag =0;
			/* Check if there is any Free space at start of Heap but before head of linked list*/
			if(curr->base_add != HEAP_START_ADDR)
			{
				if( (HEAP_START_ADDR + size - 1) < curr->base_add)
				{
				       
					struct Node* nptr = (struct Node*)malloc(sizeof(struct Node));
					nptr->base_add = HEAP_START_ADDR;
					nptr->size = size;
					nptr->next = curr;
					lptr = nptr;
					res = lptr->base_add;
					flag =1;
				}
			}
            
                  if(!flag)
                  
			{   /* Look for first available in between free slot */
			    int flag1 = 0;
			    while(curr->next != NULL && !flag1)
			    {
				    if( (curr->base_add + curr->size + size - 1) < curr->next->base_add) 
				    {
					   struct Node* nptr = (struct Node*)malloc(sizeof(struct Node));
					   nptr->base_add = curr->base_add + curr->size;
					   nptr->size = size;
					   nptr->next = curr->next;
					   curr->next = nptr;
					   res = nptr->base_add;
					   flag1 = 1;
				    }
				    curr = curr->next;
			    }
			    
			    if(!flag1)
			    {
			        /*This is the last node, make sure size is within head limit */
			        if( (curr->base_add + curr->size + size - 1) <= HEAP_END_ADDR) 
			        {
			             struct Node* nptr = (struct Node*)malloc(sizeof(struct Node));
			             nptr->base_add = curr->base_add + curr->size;
				         nptr->size = size;
				         nptr->next = curr->next;
				         curr->next = nptr;
				         res = nptr->base_add;
			        }
			    }
			}
			
			
		}
	}
	
	if(res == -1) 
	{
		printf("Can Not allocate memory size : %d",size) ;
	}
	
	return res;
}

void Free(int start_add) 
{
	struct Node *curr, *prev;
	curr = lptr, prev = NULL;
	if(lptr->base_add == start_add) 
	{
		lptr = curr->next;
		//printf("%d\n",(lptr->next)->base_add);
	}

    else 
    {
        int flag = 0;
        while(curr!= NULL && !flag)
        {
            if(curr->base_add == start_add)
            {
                struct Node* temp;
                temp = curr->next;
                prev->next = temp;
                flag =1;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    
    if (curr == NULL)
    {
        printf("Failed to free given memory\n");
    }
}

void Print() 
{
	struct Node *curr = lptr;
	while(curr != NULL) 
	{
		printf("base_add : %d size : %d \n",curr->base_add , curr->size);
		curr = curr->next;
	}
	printf("---------------------------------------------------------------------------\n");
}

int main() 
{
	int p1 = Allocate(1000);
	//Print();
	
	int p2 = Allocate(500);	
	//Print();
	
	int p3 = Allocate(2000);
	Print();
	
	Free(p2);
	Print();
	
	int p4 = Allocate(500);					
	Print();
	
	Free(p1);
	Print();
	
	int p5 = Allocate(200);	
	Print();
	
	int p6 = Allocate(1000);
	Print();
	
	int p7 = Allocate(800);
	Print();
	
	Free(p5);
	Print();
	
	return 0;
}


