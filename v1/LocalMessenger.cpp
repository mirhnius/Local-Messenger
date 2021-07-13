#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>

using namespace std;

vector<string> remove_dup_word(string const &str) { 
    vector<string>wl;
    string word;
    istringstream ss(str);
    do{
    	ss>>word;
    	wl.push_back(word);
    }
    while(ss);
    if(wl.size() != 0)
    	wl.pop_back();
    return wl;
}

vector<int>string_to_int(const vector<string> &data_numbers){

   vector<int> int_numbers;
    for (unsigned int i = 0; i < data_numbers.size() ; i ++){
     int num = atoi(data_numbers.at(i).c_str());
     int_numbers.push_back(num);
    }
    return int_numbers;
}

vector<vector<int>> people_connection(){
	
	string line;
	vector<vector<int>> people;
	fstream people_file;
    people_file.open ("people.txt",ios::in);
    while(!people_file.eof()){
    	getline(people_file,line);
    	if(line=="")
    	    continue;
    	people.push_back(string_to_int(remove_dup_word(line)));  	
    }
    people_file.close(); 
    people.pop_back();
    return people;
}

bool is_digits(const string &str){
    return str.find_first_not_of("0123456789") == string::npos;
}

vector<int>people_numbers(const vector<vector<int>> &people){

	vector<int>numbers(people.size());
	for(unsigned int i = 0;i < people.size();i ++){
	    numbers[i] = people[i][0];
	}
	return numbers;
}

void people_file_creation(const vector<int> &people_number){
	for(unsigned int i = 0;i < people_number.size();i ++){
		fstream person;
        person.open (to_string(people_number[i])+".txt",ios::out);
        person.close();
	}
}

int find_person(int n, vector<int>numbers){
	for(unsigned int i = 0;i< numbers.size();i ++)
		if(numbers[i] == n)
			return i;
	return -1;	
}

void show_msg(string n,const vector<int> &numbers){
	
	if(!is_digits(n)){
		cout<<"failed"<<endl;
		return;
	}
    if(find_person(atoi(n.c_str()),numbers) == -1 ){
    	cout<<"failed"<<endl;
		return;
    }
    // if(find_person(atoi(n.c_str()),numbers)){
	    string line;
	    fstream person;
	    person.open (n + ".txt",ios::in);
	    if(person.is_open()){
            while(!person.eof()){
    	        getline(person,line);
    	        if(line=="")
    	        	continue;
    	        cout<<line<<endl;  	
            }
        }
        else
    	cout<<"failed"<<endl;
}

bool find_connection(int person_id,int n,const vector<vector<int>>people){
	if(person_id == -1)
		return false;
	for(unsigned int i = 0;i < people[person_id].size();i ++)
		if(people[person_id][i] == n)
			return true;
	return false;
}

bool check_connection(int n, int m,const vector<vector<int>> &people){
	
	vector<int> numbers=people_numbers(people);
	if(n > m){
		if(find_connection(find_person(m,numbers),n,people))
			return true;
		}
    else{
    	if(find_connection(find_person(n,numbers),m,people))
			return true;
		}

	return false;
}

bool save_msg(vector<string> command,const vector<vector<int>> &people){
	
	int n = atoi(command[0].c_str());
	int m = atoi(command[1].c_str());

	if(check_connection(n,m,people)){
		
		fstream person;
		person.open (to_string(m) + ".txt",ios::app);
        if(find_person(m,people_numbers(people))<0)
           return false;
        person<<n<<" ";
        for(unsigned int i = 2;i < command.size();i ++){
        	if(i + 1 == command.size())
        		person<<command[i];
        	else
        		person<<command[i]<<" ";
        }
        person<<endl;
        person.close(); 
   
        return true;
	}
	return false;
}

void sent_msg(vector<string> command,const vector<vector<int>> &people){
	if(save_msg(command,people))
		cout<<"sent"<<endl;
	else
		cout<<"failed"<<endl;
}

void commands(vector<string> command, const vector<vector<int>> &people){
	
	if (command[0] == "show_msg")
		show_msg(command[1],people_numbers(people));

	else if(2 <= command.size() && is_digits(command[0]) && is_digits(command[1]))
		 sent_msg(command,people);
    else 
		cout<<"failed"<<endl;	
}

int main(){

	string line;
	vector<vector<int>> people = people_connection();
    people_file_creation(people_numbers(people));
    while(getline(cin,line)){
    	commands(remove_dup_word(line),people);
   }

}
