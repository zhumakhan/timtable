
#ifndef ALGO                      ///this used to avod including this header file several time;
#define ALGO                      //if ALGO is already defined (included) it skips including;

#include "FillClassesFromFile.h" //includes "FillClassesFromFile.h" header file to use "Classes.h" data and functions;
                                 // also to use "FillClassesFromFile.h" data and functions if necessary;





deque<Class> classes_copy;  //algorthim deletes classes that are added to timetable; we need copy of "classes" to use it later;
string auditory;            //stores auditory name or number;
string course;              //stores course name;
string staff;               //stores staff's name;
int t = 0;
void copy_classes(){        //iteratos through classes and adds each iterated element to classes_copy;
	for(unsigned int i = 0; i < cl; i++){
		classes_copy.push_back(classes[i]);
	}
}

//This functions fills times deque
//it goes through all hours in one day; 0 - 9 (9.00 - 18.00);
//in each cycle of hours it goes throuh all working days in week; [0 - 5) (Monday - Firday) ;
//for each day in certain time it iterates through all classes and check if there is not conflict in staff, auditory, and groups;
//if there is no conflict it sets this class to this day and time (consider duration of class);
void fillTime(){
    copy_classes();                     //takes copy of classes to use it;
    int duration = 0, groups, znak = 0; //duration stores duration of class; groups stores number of groups in Class;

 	for(int j = 0; j < 10; j++){      //iteation through hours;
 		for(int i = 0; i < 5; i++){   // iteration through  days;
 			if(j == 4)                //if hours if 4 (13.00) it skips loop because all staff are busy (at lucnh);
 				break;
 			for(unsigned int it = 0; it < cl; it++){ //iteration through all classes (using it copy);
 				znak = 0;                                    //znak = 0 means comflict;
 				duration = classes_copy[it].getDuration();   //gets duration and stores;
 				groups = classes_copy[it].getGroups().size();//gets number of groups in class;
 				
 				for(int d = 0; d < duration; d++){           //cheack if there is no conflict for the duration of class;
 					for(int g = 0; g < groups; g++){         //for all groups that attend this class;
                        if(getGroupWithId(classes_copy[it].getGroups()[g])->getGroupAt(i, j + d) == 1) {znak  = 1;} //znak is set to 1 if there is conflict;                          
                    }
                    if( getAuditoryWithId(classes_copy[it].getAuditoryId())->getAuditoryAt(i, j + d) == 1) {znak = 1;}
                    if( getStaffWithId(classes_copy[it].getStaffId())->getStaffAt(i, j + d) == 1) {znak = 1;}     
                   
 				}

 				if(znak == 0){  							//if there is conflict encountered
                    Time time = Time(i,j,j+duration-1,classes_copy[it].getId()); //creates Time with day, start time, end time and class;
 					 times[t] = time; t++; 					//stores instance of Time in times deque<Time>;
 															//set busy all groups, auditoriy and staff in this day and for the duration of class;
 					for(int d = 0; d < duration; d++){     
 						for(int g = 0; g < groups; g++){
                       		getGroupWithId(classes_copy[it].getGroups()[g])->setGroupAt(i, j + d);                   
                    	}
                    	getAuditoryWithId(classes_copy[it].getAuditoryId())->setAuditoryAt(i, j + d);
                   		getStaffWithId(classes_copy[it].getStaffId())->setStaffAt(i, j + d);                   	
                        
                    }
                	classes_copy.erase(classes_copy.begin() + it); //deletes class that was set in timetable to avoid repetetive set of same class;

                	
                
                	
                } 				
 			}
 		}
 	}
 
}
 //this mecthod get timtable of group specified by id at certain time;
void Data(int id,int i, int j){   
    deque<int> g;

//if this groups doesn't have class at specified time it leaves "course","staff", "auditory" empty;
    course =  "         ";  
    staff =    "         ";
    auditory =         "    ";
    for(int it = 0; it <  t; t++){
    	
      
        if( times[it].getDay() == i && (times[it].getStart() <= j && times[it].getEnd() >= j) ){ //check if day and hours coincide;
            g = getClassWithId((times[it]).getClassId())->getGroups();
            for(unsigned int i = 0; i < g.size(); i++){         	
                if(g[i] == id){   																			//checks if id coincide
                    course = getCourseWithId(getClassWithId((times[it]).getClassId())->getCourseId())->getName(); //gets course name
                    staff = getStaffWithId(getClassWithId((times[it]).getClassId())->getStaffId())->getName(); //gets staff name;
                    auditory = to_string(getClassWithId((times[it]).getClassId())->getAuditoryId()); //gets auditory and convert it to string;
                    
                   	return;
                    
                }
            }
			
        }

    }
}
//goes through all time in week and get timetable of group by id;
void TimeTable(int id){
    int  i = 0;   
  	fstream  output("Output.txt",ios::app);
  	output<<"\n";
  	output<<"Time Table for group: "<<id<<endl;
    output<<"****************************************************************************************************************************************************************\n";
    output<<"        \tMONDAY                      \tTUESDAY                           \t WEDNESDAY                         \tTHURSDAY                         \tFRIDAY\n";
    for(int j = 0; j < 10; j++){
    	output<<j+9<<".00 ";
            for(i = 0; i < 5; i++){
                Data(id,i,j); //calls function Data(id, day, hour) with id, day, hour;
                	output<<"/     "<<course<<" "<<staff<<" "<<auditory<<"    |"; 

            }
            output<<endl;
	}
}










#endif
