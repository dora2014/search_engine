#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

//screen class perform screen related tasks
class Screen
{
  private:
  	char recv_keyword[20];
  	string dir_input="";
  	unsigned int keyword_num=0;
  
  public:
     Screen(); //constructor
     ~Screen(); //destructor
	 void show_menu();  //show default menu display, ask for keyword
     void set_keywords();
	 void get_keywords(std::string& keywords, unsigned int& keyword_size); //get keywords from the user
	 void get_path(char *pathV_ptr);

};

Screen::Screen()
{	
	//clear the recv_keyword array;
	cout << "clear screen class variables" <<endl;
	cout << "Instantiate screen help object" <<endl;
	memset(recv_keyword, 0, sizeof(recv_keyword) );
	
}

Screen::~Screen(){
	
	cout << "kill object..." <<endl;
}


void Screen::show_menu()
{
	
	cout <<"*****************************************************************"<<endl;
	cout <<"**********  Welcome to DD Search-Text-File Engine : *************"<<endl;
	cout <<"*****************************************************************"<<endl;
	cout <<endl;
	cout <<endl;
	
	cout << "Please enter a keyword: " ;
	cin >> recv_keyword;
	cout << "Please enter a directory to search: ";
	cin >> dir_input;
	set_keywords();
}

void Screen::get_path(char *pathV_ptr)
{
	
	cout << "get_path(): " <<dir_input<<endl;
	strcpy(pathV_ptr, dir_input.c_str() );
	cout << "get_path(): " <<pathV_ptr<<endl;
}

void Screen::set_keywords()
{
	keyword_num = strlen(recv_keyword);
	
}

void Screen::get_keywords(std::string& keywords, unsigned int& keyword_size)
{
   keywords = recv_keyword;
   keyword_size = keyword_num;

}
