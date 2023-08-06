
void* heap=0;
void* _sbrk(int size){
	void* pos =heap;
	heap+=size;
	return pos;

}