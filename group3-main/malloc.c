#include<assert.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
//struct for each block allocated by mymalloc

struct allocate_block {
	int available;
	size_t size;
	struct allocate_block *next;
};

//end of memory list
struct allocate_block *base_address = NULL;
struct allocate_block *tail = NULL;
//block overhead, while memory allocation
int block_overhead = sizeof(struct allocate_block);

//function declaration for new space allocation
struct allocate_block *allocate_space(size_t size, struct allocate_block *prev);

//function declaration for free block search
struct allocate_block *check_available_block(size_t size);

void *malloc(size_t size){
	struct allocate_block *new_block;
	//check size
	if(size <= 0){
		return NULL;
	}
	if(!base_address)
	{
		new_block = allocate_space(size, NULL);
		base_address = new_block;
		tail = new_block;
	} else{
		struct allocate_block *prev = tail;
	       	new_block = check_available_block(size);
		if(!new_block){
			new_block = allocate_space(size, prev);
			tail = new_block;
			return (void*) (new_block+1);
			
		}
		new_block->available = 0;
	
	}
	return (void*) (new_block + 1);
}

void free(void *blockptr){
	struct allocate_block *block = blockptr;
	block -= 1;
	block->available = 1;
	return;
}

void *realloc(void *ptr, size_t size){
	struct allocate_block *old_block =ptr;
	size_t old_size = (old_block - 1)->size;
	void *new_block = malloc(size);
        memcpy(new_block, old_block,size);
        free(ptr);


	if (size > old_size) {		
		void *new_block = malloc(size);
		memcpy(new_block, old_block,size);
		free(ptr);
	}
	else if ((size < old_size) && ((old_size - size) > block_overhead)) {
		(old_block - 1)->size = size;
		allocate_space((old_size - size), (ptr + size));
	}
	else
	{
		return 0;
	}

}

struct allocate_block *check_available_block(size_t size){
	struct allocate_block *current = base_address;
	if(current){
	while(!current->available && current->size < size){
		current = current->next;
	}}
	return NULL;
}

struct allocate_block *allocate_space(size_t size, struct allocate_block *prev){
	struct allocate_block *new_block;
	new_block = sbrk(size + block_overhead);
	if(prev){
		prev->next = new_block;
	}
	new_block->available = 0;
	new_block->size = size;
	new_block->next = NULL;
	return new_block;		
}

void *calloc( size_t num, size_t elem_size )
{
	void* block_address;
    if(num==0){
                return NULL;
        }
        else
        {
                block_address = malloc(elem_size*num);
                
		memset((block_address),0,elem_size*num);

        }
        return (block_address);

}

