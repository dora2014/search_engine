#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Search_Engine
{
	private:	
  		vector<std::string> name_list;
  		pair<int, string> pair_value;
  		multimap<int, std::string, greater<int> > matched_files;
  		multimap<int, std::string, greater<int> >::iterator matched_list_ptr;
	
	
	public:
   		Search_Engine(); //constructor
  	//	~Search_Engine(); //destructor
  	
  	//find all txt files in the directory, return #of files found
   		int find_files(char *path_name); 
        int seek_words(const char *key_ptr, unsigned int& keyword_size, int& file_num);
		void get_vectorList(int index, std::string &fn);
  	    void store_files(int m, string &fileName);
  	    void get_match_list(std::string keyValue);
  	
};


Search_Engine::Search_Engine()
{
   cout <<" instantiate search engine ohbject" <<endl;	
	
}
