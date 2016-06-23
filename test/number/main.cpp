
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline int32_t is_pow2(uint32_t size){
	return !(size&(size-1));
}
static inline int32_t is_pow(uint32_t a, int b = 0) {
	b += a % 2;
	a = a >> 1;
	printf("\ta=%x, b=%d\n",a,b);
	if( b > 1 ) 
		return 0;
	if ( a == 0 ) return 1;
	return is_pow(a,b);
}
	
static inline uint32_t size_of_pow2(uint32_t size)
{
    if(is_pow2(size)) return size;
	size = size-1;
	size = size | (size>>1);
	size = size | (size>>2);
	size = size | (size>>4);
	size = size | (size>>8);
	size = size | (size>>16);
	return size + 1;
}

static inline uint8_t get_pow2(uint32_t size)
{
	uint8_t pow2 = 0;
    if(!is_pow2(size)) size = (size << 1);
	while(size > 1){
		pow2++;
		size = size >> 1;
	}
	return pow2;
}

int main()
{
	//printf("size of pow2 128 is %d\n",size_of_pow2(128));
	//printf("size of pow2 127 is %d\n",size_of_pow2(127));
	//printf("size of pow2 16 is %d\n",size_of_pow2(16));
	//printf("size of pow2 18 is %d\n",size_of_pow2(18));
	//if( is_pow2(
	//printf("size of pow2 18 is %d\n",size_of_pow2(18));

	printf("size of pow 128 is %d\n",is_pow2(128));
	printf("size of pow 127 is %d\n",is_pow2(127));
	printf("size of pow 1 is %d\n",is_pow2(1));
	printf("size of pow 18 is %d\n",is_pow2(18));
	
	printf("size of pow 128 is %d\n",is_pow(128));
	printf("size of pow 127 is %d\n",is_pow(127));
	printf("size of pow 1 is %d\n",is_pow(1));
	printf("size of pow 18 is %d\n",is_pow(18));

	printf("=====================");
    enum {main_handle=1,};
    uint32_t v = (uint32_t)(-main_handle);
    printf("-1 to uint32 v=%u\n",v);

    char sz[]  = "type";
    long isz = atoll(sz);
    printf("str type atoll number:%ld\n",isz);


	const int32_t th = 0x7FFFFFFF;
	printf("th:%d\n", th);

	uint32_t unth = th + 1;
	printf("th+1 to uint32:%d\n", unth);
   	
	int32_t fromuint32 = unth;
	printf("fromuint32 :%d\n", fromuint32);
	

	long long lln;
	printf("size of long long is %d\n", sizeof(lln));

	return 0;
}
