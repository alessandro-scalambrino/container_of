/* 
 * Re-implementation of the container_of and offsetof macros:
 *
 * `container_of`: This macro retrieves the base address of a structure
 * given a pointer to one of its members. It calculates the offset of
 * the member within the structure and subtracts it from the member pointer 
 * to obtain the structure's starting address.
 *
 * `offsetof`: This macro calculates the byte offset of a specific member
 * within a structure. It is typically used for pointer arithmetic and
 * assists in computing the address of a structure from a member pointer.
 * 
 * Approaches to Implement:
 * 1. Using a Temporary Instance - Calculate offsets with an actual instance.
 * 2. Using a Null-Pointer Base - Calculate offsets using a null pointer base.
 * 3. Using an Inline Macro Definition - Direct inline macro to calculate offset.
 */
#include <stdio.h>

struct some_data {
	char a;
	int b;
	char c;
	int d;
};

struct some_data data;

#define container_of(ptr, type, member)  ((type*) ((char*)ptr - (char*) ( &((type*)0)->member)));

void get_container_temp(char *ptr) {
/* get_container_temp - Retrieves the base address of the structure
 *                         containing a specified member using pointer arithmetic.
 * Using a Temporary Instance (struct some_data temp) to Calculate the Offset.
*/
		int offset;
		
		struct some_data temp;
		offset = (int) ( (char*)&temp.c - (char*)&temp.a );
		struct some_data *data1 = (struct some_data*) (ptr - offset); 
		
		printf("_____Temporary Instance_____\n");
		printf("a: %d\n", data1->a);
		printf("b: %d\n", data1->b);
		printf("c: %d\n", data1->c);
		printf("d: %d\n", data1->d);
		printf("struct base addr: %p\n", (void *)data1);

		
}	
void get_container_deref(char *ptr) {
/* get_container_deref - Retrieves the base address of the structure
 *                         containing a specified member using pointer arithmetic.
 * Using a Null-Pointer Base (((struct some_data*)0)) to Calculate the Offset
*/
		int offset;

		offset =(long) ( &((struct some_data*)0)->c);
		struct some_data *data1 = (struct some_data*) (ptr - offset);

		printf("_____Null-Pointer Base_____\n");
		printf("a: %d\n", data1->a);
		printf("b: %d\n", data1->b);
		printf("c: %d\n", data1->c);
		printf("d: %d\n", data1->d);
    	printf("struct base addr: %p\n", (void *)data1);
}	


int main(){

	/* memory = char1/x/x/x /int1/int1/int1/int1 /char2/x/x/x /int2/int2/int2/int2/ */
	data.a=100;
	data.b=200;
	data.c='a';
	data.d=400;

	// Print structure details
    printf("Your data structure:\n");
    printf("{\n");
    printf("  a: %d\n", data.a);
    printf("  b: %d\n", data.b);
    printf("  c: '%c'\n", data.c);  // using '%c' to print `c` as a character
    printf("  d: %d\n", data.d);
    printf("}\n\n");
	printf("***Retrieving the container class and retrieving all it's members using just the c member***\n\n");

	//get_container_temp using Using a Temporary Instance (struct some_data temp) to calculate the offset--> struct base address; 
	get_container_temp(&data.c);
	//get_container_deref using Using a Null-Pointer Base to calculate the offset--> struct base address; 
	get_container_deref(&data.c);

	//or use the macro defined on top:
	struct some_data *data1 = container_of(&data.b, struct some_data, b);
		printf("_____Macro_____\n");
		printf("a: %d\n", data1->a);
		printf("b: %d\n", data1->b);
		printf("c: %d\n", data1->c);
		printf("d: %d\n", data1->d);
		printf("struct base addr: %p\n", (void *)data1);

	
	return 0;
}

