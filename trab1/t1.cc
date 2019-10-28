#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
  int instant;
  int page; 
};

vector<node>::iterator first_equals(const vector<node>::iterator &begin, const vector<node>::iterator &end, const node other){
	auto const isEqual = [&other](auto aux){return other.page == aux.page;};
	return find_if(begin, end, isEqual);
}

 void replace_equals(const vector<node>::iterator &begin, const vector<node>::iterator &end, const node other, const node new_value){
	auto const isEqual = [&other](auto aux){return other.page == aux.page;};
	replace_if(begin, end, isEqual, new_value);
}

int opt_algorithm(const int &nPages, vector<node> &reference){
	int fault=0;
	node lastReferenced;
	
	vector<node> frames;
	frames.reserve(nPages);
	
	vector<node>::iterator proxOcurrence;
	
	for(auto access = reference.begin(); access != reference.end(); ++access){
		if(first_equals(frames.begin(), frames.end(), *access) == frames.end()){
			
			if(frames.size() < nPages)
				frames.push_back(*access);
			else {
				lastReferenced = *reference.begin();
				for(auto frame: frames){
					proxOcurrence = first_equals(access+1, reference.end(), frame);
					if(lastReferenced.instant < proxOcurrence->instant) lastReferenced = *proxOcurrence;
					else if(proxOcurrence == reference.end()){
						lastReferenced = frame;
						break;
					}
				}
				replace_equals(frames.begin(), frames.end(), lastReferenced, *access);
			}
			fault++;
		}
	}
	return fault;
}

int fifo_algorithm(const int &nPages,const vector<node> &reference){
	int fault=0;
	node older;
	
	vector<node> frames;
	frames.reserve(nPages);
	
	for(auto access = reference.begin(); access != reference.end(); ++access){	
		if(first_equals(frames.begin(), frames.end(), *access) == frames.end()){
			if(frames.size() < nPages)
				frames.push_back(*access);
			else {
				older = *(reference.end()-1);
				for(auto frame: frames){
					if(older.instant > frame.instant) older = frame;
				}
				replace_equals(frames.begin(), frames.end(), older, *access);
			}
			fault++;
		}
	}
	return fault;
}

int lru_algorithm(const int &nPages,const vector<node> &reference){
	int fault=0;
	node older;
	
	vector<node> frames;
	frames.reserve(nPages);
	
	for(auto access = reference.begin(); access != reference.end(); ++access){
		auto page = first_equals(frames.begin(), frames.end(), *access);
		if(page == frames.end()){
			if(frames.size() < nPages)
				frames.push_back(*access);
			else {
				older = *(reference.end()-1);
				for(auto frame: frames){
					if(older.instant > frame.instant) older = frame;
				}
				replace_equals(frames.begin(), frames.end(), older, *access);
			}
			fault++;
		}else page->instant = access->instant;
	}
	return fault;
}

int main(int argc, const char *argv[]){
	vector<node> reference;
	int tempPage, nPages = atoi(argv[1]), instant=1;
	while(cin >> tempPage)
		reference.push_back( node{instant++, tempPage} );

	printf ("%5d quadros, %7ld refs: FIFO: %5d PFs, LRU: %5d PFs, OPT: %5d PFs\n",
		nPages, reference.size(), fifo_algorithm(nPages, reference), lru_algorithm(nPages, reference), opt_algorithm(nPages, reference)) ;
}
