#ifndef FILLFROMFILE ///this used to avod including this header file several time;
#define FILLFROMFILE //if FILLFROMFILE is already defined (included) it skips including;
#include <string>
#include <fstream> //includes fstream to handle file;
#include "Classes.h" //includes "Classes.h" from same directory to use classes and its function;
using namespace std;

//All these functions work in same way;
void readStaff(fstream & file){ //if #staff is encountered it reads lines after this #staff;
	int id = 0;
	string name = " ";
	file>>id; //reads first integere after #staff and stores it in int id defined earlier;
	file>>name; //reads
	
	Staff staff = Staff(id, name); //creates Staff class with id and name;
	staffs[s] = staff; s++; //stores created class "s" in staffs deque;
	}

void readAuditory(fstream & file){
	int id, capacity, lab;
	string line = " ";
	file>>id;
	file>>capacity;
	file>>lab;
	Auditory au = Auditory(id, capacity);
	auditories[a] = au; a++;
	
}
void readGroup(fstream & file){
	int id, size;
	file>>id;
	file>>size;
	Group gr = Group(id, size);
	groups[g] = gr; g++;
	
}
void readCourse(fstream & file){
	int id;
	string name;
	file>>id;
	file>>name;
	Course c = Course(id, name);
	courses[co] = c; co++;

}

//Class can have various number of group ids; 
//readClass should read untill it encounters non-number line; 
void readClass(fstream & file){
	int i = 0, id, lab, duration, staffid, courseid, auditoryid, groupid[10];
		string line; 
		deque<int> g;
				
			file>>id>>lab>>duration>>staffid>>courseid>>auditoryid;
			file>>line;
			bool b = true;
			//in ASCII conversion table numbers 0 - 9 are from 48 - 57 (in decimal);
			//for loop takes each char of line and checks if this char is number;
			while( b ){
				groupid[i] = stoi(line); i++; file>>line;    //stoi(string s) converts s to integer if s consists only numbers;
				for(unsigned int k = 0; k < line.size(); k++){
					if(line[k] >= char(48)  && line[k] <= char(57)){}
					else{ b = false;}
				}
			}
			//above while loop ends when line is non-number string;
			//stream from file now at position where one non-number line after "#class" block;
			//seekg() function returns current position of stream from file to one string back;
			//this important because priogram must check every line
			file.seekg(-line.size(),ios_base::cur);
		
		
		for(int j = 0; j < i; j++){
			g.push_back( groupid[j] );       //all  group ids are stored in deque in Class
		}
	Class c = 	Class(id,duration,staffid,courseid, g, auditoryid); 
	classes[cl] = c; cl++;
	
}

void read(){
	string line;
	fstream file("Input.txt",ios::in);  //opens stream from file "Input.txt" from same directory;
	while(!file.eof()){ 				//runs till the end of class;
		file>>line; 					//read on string from file
		if(line.compare("#staff") == 0) //check if this line is "#staff"
			readStaff(file);  			//if line is "#staff" calls readStaff();
		else if(line.compare("#auditory") == 0)//check if this line is "#staff"
			readAuditory(file);  		//if line is "#auditory" calls readAuditory();
		else if(line.compare("#group") == 0)//check if this line is "#staff"
			readGroup(file );  			//if line is "#group" calls readGroup(); 
		else if(line.compare("#course") == 0)//check if this line is "#staff"
			readCourse(file);			///if line is "#course" calls readCourse();
		else if(line.compare("#class") == 0)//check if this line is "#staff"
			readClass(file);			///if line is "#class" calls readClass();	
		else if(line.compare("#endandend") == 0) //or if encounters line "#endandend" it finished with reeading file;
 			file.close();
	}
	
   file.close(); //closes stream if it is not closed
}


#endif






