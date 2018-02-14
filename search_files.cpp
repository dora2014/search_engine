/***********************************************************************************************/
/****************   		Search keywords in a directory(text file only)       **************/
/****************   		1) search_files.cpp               	  			    **************/
/****************   		2) search_files.h                	     		   **************/
/****************   		3) search_helper.h                	     		  **************/
/****************  									    				     **************/  
/*****************************************************************************************/

#include <windows.h>
#include <vector>
#include <map>
#include <fstream>
#include <search_files.h>
#include <screen_helper.h>

using namespace std;

/**********************************************************************************/
//find the filename corresponding to the index list
void Search_Engine::get_vectorList(int index, std::string &fn)
{
   fn = name_list.at(index) ;
}


/**********************************************************************************/
//find all text files in the default directory, return number of text files if found
int Search_Engine::find_files(char *path_name)
{
   std::string FILENAME, current_path, path_n_name;
   WIN32_FIND_DATA  fileData;
   HANDLE hFind;
  //DWORD dwError=0;
   
   int loop=0;
   
   //append default path + any text files
   current_path.append(path_name); 
   current_path.append("\\*.txt");
   
   cout << current_path <<endl;  //print current path

   hFind = FindFirstFile(current_path.c_str(), &fileData); //anyfile in the path with .txt extension

  if (hFind == INVALID_HANDLE_VALUE)
  {

       //call GetLastError 
      // dwError = GetLastError();
       cout <<"Failed find first file()  " <<endl;
       return -1;
  }
  else  //get the file name that just found
  {
      FILENAME = fileData.cFileName;
     // cout << FILENAME <<endl;
      
      path_n_name.append(path_name);
      path_n_name.append("\\");
      path_n_name.append(FILENAME);
      cout << path_n_name <<endl;
       
    //  name_list.push_back(fileData.cFileName);
      name_list.push_back(path_n_name);
      path_n_name.clear();
  }

  while(FindNextFile(hFind, &fileData) != 0)  //if there are more .txt files in the directory
  {
   
      FILENAME = fileData.cFileName;
     // cout << FILENAME <<endl;
      path_n_name.append(path_name);
      path_n_name.append("\\");
      path_n_name.append(FILENAME);
      cout << path_n_name <<endl;
      
      name_list.push_back(path_n_name);
      path_n_name.clear();
  }
  
  cout <<"Done detecting all files" <<endl;
  cout << "number of files in the vector list is " << name_list.size() <<'\n';
  FindClose(hFind);
  
  return name_list.size();
}

/**********************************************************************************/
//search words in each file
int Search_Engine::seek_words(const char *key_ptr, unsigned int& keyword_size, int& file_num)
{
     std::string FILENAME, low_data;
     ifstream in_File;   
     int  file_size=0, match_num=0, block_count=0, block_length=0, done_read_len=0, j, str_len;


    // char *low_data_ptr = new char[32];
     char *low_data_ptr, *upper_data_ptr, *upper_key_ptr, up_data_val[128], low_data_val[128], up_key_val[16], c;
  
     memset(low_data_val, 0, sizeof(low_data_val) );
     memset(up_data_val, 0, sizeof(up_data_val) );
     memset(up_key_val, 0, sizeof(up_key_val) );

     low_data_ptr = &low_data_val[0];
     upper_key_ptr = &up_key_val[0];    
     upper_data_ptr = &up_data_val[0];
        
     get_vectorList(file_num,FILENAME);
     
      //convert keywords to upper case
     for (j=0; j<keyword_size; j++)
     {
        c =*key_ptr;
        *upper_key_ptr = toupper(c);
        cout <<"orignial data[" <<j<<"]" <<c <<endl;
		cout <<"upper case data[" <<j<<"]" <<up_key_val[j]<< endl;
        key_ptr++;
        upper_key_ptr++;
	 }
     
     in_File.open(FILENAME, ifstream::in);
     in_File.seekg(0, in_File.end);
     file_size = in_File.tellg();   //find the size of the file
     cout <<"file size: " <<file_size<<endl;
     in_File.seekg(0, in_File.beg); //reset to the start of the file
     
	 //each time read block of data until hits a space
     while(in_File >> low_data)  
     {
     	low_data_ptr = &low_data_val[0];  //reset lower case text data pointer
     	
		cout << "read in data: " << low_data <<'\n';
     	strcpy(low_data_ptr,low_data.c_str());
     	str_len = strlen(low_data_ptr);
     	cout <<"String copied length: " <<str_len<<'\n';
     	
     	upper_key_ptr = &up_key_val[0]; //reset keyword pointer
     	upper_data_ptr = &up_data_val[0]; //reset uppercase text data pointer
     	
		//convert text data from file to upper case
	     for (j=0; j<str_len; j++)
         {
         	 c =*low_data_ptr;
         	*upper_data_ptr = toupper(c);    			     	
            	
          	low_data_ptr++;
         	upper_data_ptr++;
         	
		 }	//end for loop	 
     	
     	//see if key_ptr is part of data_ptr 
     	upper_key_ptr = &up_key_val[0]; //reset keyword pointer
     	upper_data_ptr = &up_data_val[0]; //reset uppercase text data pointer
     	
		cout <<"keyword: " <<upper_key_ptr <<endl;
		cout <<"upper case data: " <<upper_data_ptr << endl;
		
     	if (strstr(upper_data_ptr, upper_key_ptr) == NULL)
      	{
           cout << "No Detection" <<'\n';
      	}
      	else
     	{
	       cout <<"Found match! " <<'\n';
           match_num++;  //increment number of match count
        }//end else(detected)
     	
     	memset(low_data_val, 0, sizeof(low_data_val) );
   		memset(up_data_val, 0, sizeof(up_data_val) );
    
	 } //end of while loop
    
	   //close file
	   in_File.close();
    
    return match_num;
   
}

//save to the class multimap container for auto sorting
void Search_Engine::store_files(int m, string &fileName)
{
   matched_files.insert(pair<int, string>(m, fileName) );
}

void Search_Engine::get_match_list(std::string keyVal)
{
	for (matched_list_ptr = matched_files.begin(); matched_list_ptr!=matched_files.end();matched_list_ptr++)
	{
		cout << "****************************************************************************" <<endl;
		cout << "****************** Final Report ********************************************" <<endl;
		cout << "Matched Information: "	<<endl;	
		cout << "Keyword: " << keyVal<<endl;
		cout <<"File Name: " << matched_list_ptr->second<<'\n';
		cout <<"Matched cases: " <<matched_list_ptr->first<<'\n';
		cout << "*****************************************************************************" <<endl;
	}
}

/**********************************************************************************/
/******************    Main function starts   ************************************/
int main()
{
   unsigned int total_files=0, keyword_size=0, m_count=0;
 
   std::string input_word="", fileName;
   char path_default[64];

   // instantiate search engine object, screenobject 
   Screen screen_help;  
   Search_Engine search_engine1;

   //Display default menu
    screen_help.show_menu();

   //user prompt asking for keywords
   screen_help.get_keywords(input_word, keyword_size);
   
   // display keywords 
   cout <<"Keyword entered: "<<input_word <<'\n';
  // cout <<"Keywords size: "<<keyword_size <<'\n';

   screen_help.get_path(path_default);
   //go to default directory and search text files
   cout <<"Directory entered: " <<path_default<<endl;
   total_files = search_engine1.find_files(path_default) ; //return number of text files found in the default directory

   // system("pause");
   if(total_files > 0)
   {     
      //search through each file
      for(int i=0; i < total_files; i++)
      {
          cout <<"total files to search is " <<total_files<<endl;
		  m_count= search_engine1.seek_words(input_word.c_str(), keyword_size, i);
          if (m_count >0)
          {
             cout <<"Keywords found!" <<'\n';
             cout <<m_count<<" Match Found!" <<'\n';
             
             search_engine1.get_vectorList(i,fileName);
            
			 search_engine1.store_files(m_count, fileName);
          }
         else
		 {
           cout <<" No matched keywords!"  <<endl;
         }  // end else  

      }//end of for each file

    }   //end if total files > 0
    else
    {
      cout << "NO Text Files found...." <<'\n';
    }  //end if...else
   
    search_engine1.get_match_list(input_word);
    system("pause");
    
    return 0;

}
