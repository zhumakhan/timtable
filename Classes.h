#ifndef CLASSES //this used to avod including this header file several time;
#define CLASSES //if CLASS is already defined (included) it skips including;
#include <string> //including string from standart library ho handle strings
#include <deque> //incuding deque from standart library;
using namespace std; //string and deque are from standart library, we use namesapace std;
unsigned int s = 0, a = 0, g = 0, co = 0, cl = 0;
//All classes are contructed the to store data after readig file, and Time class to store timetable data (class and its time in week);
//class to keep the id, name and information about busyness of staff in certainn time in one week (7 days, 20 hours); 

class Staff{
private:  //private data used to avoid sudden direct accesses from other places;
	int id;  //private id of professor. Id used used to differentiate the Staff classes from each other;
	string name;//The Name of professor is stored in here;
	int week[7][20];  //information about busyness of staff in certainn time in one week (7 days, 20 hours); 1 means busy, and 0 means free;
public:             //public data is used get access to public fields of class to set values;
	void setId(int i){ //sets the id 
		id = i;
	}
	void setName(string s){ //sets name 
		name = s;
	}
	int setStaffAt(int i, int j){// set the 2-D array week at position specified by i - day, and j - hour;
		week[i][j] = 1;
		return 1;
	}
	int getId(){ //returns id;
		return id;
	}
	string getName(){ //returns name;
		return name;
	}
	int getStaffAt(int i, int j){  //returns value of the 2-D array "week" at position specified by i - day, and j - hour;
		return week[i][j];
	}
	Staff(){}
	Staff(int, string);
};
Staff::Staff(int _id, string _name) //Constructor  which initializes id and name, and sets all values in 2-D array to zero;
{
		id = _id;
		name = _name;
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 20; j++){
				if(j == 4)    				// 4-th hour counting from 9.00 is lunch time between 13.00 - 14.00
					week[i][j] = 1;			//when loop encounters this position it sets value 1, which means professor is not free at lunch time
				else
					week[i][j] = 0;
			}
		}
}



//Course class is used to keep names of courses with unique id;
class Course{
	private:  
		int id;
		string name;
	public:
		string getName(){
			return name;
		}
		int getId(){
			return id;
		}
		Course(){}
		Course(int,string);
};
Course::Course(int _id, string _name){
	id = _id;
	name = _name;
}



class Group{
private:
	int id;
	int size;
	int week[7][20];
public:
	int setGroupAt(int i, int j){
        week[i][j] = 1;
        return 1;
    }
	int getId(){
		return id;
	}
	int getSize(){
		return size;
	}
	int getGroupAt(int i,int j){
        return week[i][j];
	}
	Group(){}
	Group(int, int);
};
Group::Group(int _id, int _size){
		id = _id;
		size = _size;			
		for(int i = 0; i < 7; i++){
				for(int j = 0; j < 20; j++){
					week[i][j] = 0;
				}
			}
	

}

class Auditory{
	private:
		int id;
		int capacity;
		int week[7][20];
	public:		
		int setAuditoryAt(int i, int j){
			week[i][j] = 1;
			return 1;
				
		}
		int getId(){
			return id;
		}
		int getAuditoryAt(int i, int j){
			return week[i][j];
		}
		Auditory(){}
		Auditory(int, int);

};
Auditory::Auditory(int _id, int _capacity){
			id = _id;
			capacity = _capacity;
			
			for(int i = 0; i < 7; i++){
				for(int j = 0; j < 20; j++){
					week[i][j] = 0;
				}
			}
}





class Class{
	private:
		int id;
		int duration;
		int staff_id;
		int course_id;
		deque<int> _groups;
		int auditory_id;
	public:
		int getId(){
			return id;
		}
		int getDuration(){
			return duration;
		}
		int getStaffId(){
			return staff_id;
		}
		int getCourseId(){
			return course_id;
		}
		int getAuditoryId(){
			return auditory_id;
		}
		deque<int> getGroups(){
			return _groups;
		}
		Class(){}

		Class(int,int,int, int, deque<int>, int);								
};
Class::Class(int _id, int _duration, int _staff,int _course, deque<int> g,int _audit){

			id = _id;
			duration = _duration;
			staff_id = _staff;
			course_id = _course;
			_groups.swap(g);
			auditory_id = _audit;
}
class Time{
    private:
        int day;
        int start;
        int end;
        int class_id;
    public:
        int getDay(){
            return day;
        }
        int getStart(){
            return start;
        }
        int getEnd(){
            return end;
        }
        int getClassId(){
            return class_id;
        }
        Time(){}
        Time(int, int, int, int);
            
};
Time:: Time(int _day, int _start, int _end, int _id){
            day = _day;
            start = _start;
            end  = _end;
            class_id = _id;
        }
//deque is container of sequences of data and dynamically grows as more elements added.
//There is a deque of each class declared above.
//"courses", "groups", "staffs", "auditories","classes" are filled from file;
//times if filled after "fillTimeTable()" function is called;
/*deque<Course> courses;
deque<Group> groups;
deque<Staff> staffs;
deque<Auditory> auditories;
deque<Class> classes;
deque<Time> times;
 */
Course courses[100];
Group  groups[100];
Staff staffs[100];
Auditory auditories[100];
Class classes[100];
Time times[100];
//Fuctions to get direct access to the certain elements by it id
//this functions iteratos through deque and gets id from each iteratiojn,
//if id of elements equals to passed id, it returns address of this element which holds id equal to passes id; (class);
Course *  getCourseWithId(int id) {
	for(unsigned int i = 0; i < co; i++ ){  //it points to first element. then it goes to next element (it++);
		if(courses[i].getId() == id){ //compares id;
			return (courses+i); break; //retuns address of element in deque with same id as passed argument;
		}
	}
	return courses;
}
Group *  getGroupWithId(int id) {
	for(unsigned int i = 0; i < g; i++ ){  //it points to first element. then it goes to next element (it++);
		if(groups[i].getId() == id){ //compares id;
			return (groups+i); break; //retuns address of element in deque with same id as passed argument;
		}
	}
	return groups;
}
Staff *  getStaffWithId(int id) {
	for(unsigned int i = 0; i < s; i++ ){  //it points to first element. then it goes to next element (it++);
		if(staffs[i].getId() == id){ //compares id;
			return (staffs+i); break; //retuns address of element in deque with same id as passed argument;
		}
	}
	return staffs;
}
Auditory *  getAuditoryWithId(int id) {
	for(unsigned int i = 0; i < a; i++ ){  //it points to first element. then it goes to next element (it++);
		if(auditories[i].getId() == id){ //compares id;
			return (auditories+i); break; //retuns address of element in deque with same id as passed argument;
		}
	}
	return auditories;
}
Class *  getClassWithId(int id) {
	for(unsigned int i = 0; i < cl; i++ ){  //it points to first element. then it goes to next element (it++);
		if(classes[i].getId() == id){ //compares id;
			return (classes+i); break; //retuns address of element in deque with same id as passed argument;
		}
	}
	return classes;
}
  /*
Group * getGroupWithId(int id){
	for(deque<Group>::iterator it = groups.begin(); it != groups.end(); it++){
		if((*it).getId() == id){
			return &(*it); break;
		}
	} 
	return &(*groups.begin());
}
Staff* getStaffWithId(int id){
	for(deque<Staff>::iterator it = staffs.begin(); it != staffs.end(); it++){
		if((*it).getId() == id){
			return &(*it); break;
		}
	}
	return &(*staffs.begin());
}
Auditory * getAuditoryWithId(int id){
	for(deque<Auditory>::iterator it = auditories.begin(); it != auditories.end(); it++){
		if((*it).getId() == id){
			return &(*it); break;
		}
	}
	return &(*auditories.begin());
}
Class* getClassWithId(int id){
	for(deque<Class>::iterator it = classes.begin(); it != classes.end(); it++){
		if((*it).getId() == id){
			return &(*it); break;
		}
	}return &(*classes.begin());
}
*/

#endif