#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
  int instant;
  int page; 
};

inline vector<node>::iterator first_equals(const vector<node>::iterator &begin,const vector<node>::iterator &end,const node other){
	auto const static isEqual = [&other](auto aux){return other.page == aux.page;};
	return find_if(begin, end, isEqual);
}

inline void replace_equals(const vector<node>::iterator &begin,const vector<node>::iterator &end, const node other, const node new_value){
	auto const static isEqual = [&other](auto aux){return other.page == aux.page;};
	replace_if(begin, end, isEqual, new_value);
}

int opt_algorithm(const int &nPages,vector<node> &reference){
	int fault=0;
	
	vector<node> frames;
	frames.reserve(nPages);
	
	node lastReferenced;
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

int main(int argc, const char *argv[]){
  vector<node> reference;
  int tempPage, nPages = atoi(argv[1]), instant=1;
  while(cin >> tempPage)
	reference.push_back( node{instant++, tempPage} );
	
  opt_algorithm(nPages, reference);
  opt_algorithm(nPages, reference);
}
