#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



struct StudentRecord {
public:
    StudentRecord(
        string id,
        string Name,
        int age,
        string phoneNumber,
        double gpa
    ) {
        Id = id;
        name=Name;
        PhoneNumber = phoneNumber;
        Age = age;
        Gpa = gpa;
    }

    void display() {
        cout << "   Student ID: " << Id << endl;
        cout << "   First Name: " << name << endl;
        cout << " Phone Number: " << PhoneNumber << endl;
        cout << "          Age: " << Age << endl;
        cout << "          GPA: " << Gpa << endl;
        cout << endl;
    }

    string Id;
    string name;
    string PhoneNumber;
    int Age;
    double Gpa;

};

    class User{
        private:
        int auth;
        const string fileLocation="";
       
        public:
        
vector<StudentRecord> students;
        User()
        {    
                string userName;
                string passWord;
                cout<<"Enter Username";
                cin>> userName;
                cout<<"Enter Password";
                cin>> passWord;
            if(userName.compare(0,3,"990")==0 && passWord.compare(0,9,"notAdmin")==0){
                this->auth=5;
            }
            else if(userName.compare(0,3,"208")==0 && passWord.compare(0,11,"NotStudent")==0){
                this->auth=1;
            }   
            else{
                this->auth=-1;
            }
        

        }
        void getData() {
    ifstream inputFile;
    inputFile.open(this->fileLocation);
    string line = "";
    getline(inputFile, line);
    line="";
    
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        //StudentId,Name, Age, Phone Number, GPA
        string studentId;
        
        string name;
        int age;
        string phone;
        double gpa;
        string tempString;

        getline(inputString, studentId, ',');
        getline(inputString, name, ',');
        getline(inputString, tempString, ',');
        age = atoi(tempString.c_str());
        getline(inputString, phone, ',');
        getline(inputString, tempString);
        gpa = atof(tempString.c_str());

        StudentRecord student(studentId, name, age, phone, gpa);
        this->students.push_back(student);
        line = "";
    }
    inputFile.close();
}
        void menu()
{           
    this->getData();
        string searchopt;
        if(this->auth==1)
        {   

            cout<<"Search Records?"<<endl;
            cin>> searchopt;

            
            if(searchopt.compare(0,1,"y")==0|| searchopt.compare(0,1,"Y")==0)
    {
        search();
    }
    
    else {
        cout<<"See You soon";
    }
        }
        else if(this->auth==5){
            int admOption;
            cout<<"1.Search Records\n"<< "2.Add Record\n";
            cout<<"Enter Option";
            cin>> admOption;
           switch(admOption){
           case 1: search();
                    break;
           case 2: 
                addStudent();
                break;
            default:
                "error";
                break;
            }
             
        }
        else if(this->auth==-1){
            cout<<"Error";

        }
    }

        void deleteStudent(int p)
    {   
        students.erase(students.begin()+p);
        p = -1;
        this->savefile();

    }

        void modify(int p)

 {  string confirmSave;
    string studenId,Name, phone;
    int age;
    double gpa;
    cout<<"Enter Id";
    cin>>studenId;
    cout<<"Enter Name of Student";
    cin>>Name;
    cout<<"Enter Phone Number";
    cin>> phone;
    cout<<"Enter Age";
    cin>>age;
    cout<<"Enter GPA";
    cin>>gpa; 
        students.at(p).Id = studenId;
        students.at(p).name= Name;
        students.at(p).PhoneNumber = phone;
        students.at(p).Age = age;
        students.at(p).Gpa = gpa;


  
    
    cout<< "Save Changes?" ;
    cin>> confirmSave;
    if(confirmSave.compare(0,1,"y")==0 ||confirmSave.compare(0,1,"Y")==0)
    {
        savefile();
    }
 }
        
         void search( ){
            int vecSize= students.size();
    string QueryId;
        cout<< "Enter Student Id";
        cin>> QueryId;
        int p=0;
        if(this->auth==1){  
        while(QueryId.compare(students.at(p).Id) != 0 && p< vecSize)  {     
            p++;
            }
            students.at(p).display();
        }
        if(this->auth==5){  
            int optNumber;
        while(QueryId.compare(students.at(p).Id) != 0 && p< vecSize)  {     
            p++;
            }
            students.at(p).display();
            cout<<"\n1.Modify"<<"\n2. Delete"<<"\n3.Return to Menu"<<endl;
            cin>> optNumber;
            switch(optNumber){
                case 1: modify(p);
                        break;
                case 2: deleteStudent(p);
                    break;
                case 3: 
                this->menu();
                break;
                
               default: 
               cout<<"Error";
              this->menu();
               break;
           
            }
        }

    } ;
        void addStudent()
{
    string studentId,Name, phone;
    int age;
    double gpa;
    cout<<"Enter Id";
    cin>>studentId;
    cout<<"Enter Name of Student";
    cin>>Name;
    cout<<"Enter Phone Number";
    cin>> phone;
    cout<<"Enter Age";
    cin>>age;
    cout<<"Enter GPA";
    cin>>gpa;
    StudentRecord student(studentId, Name, age, phone, gpa);
        students.push_back(student);


}

        void savefile()
{   
    int vecSize= this->students.size();
   //write in file
   int n=0;
   ofstream outputFile;
   outputFile.open(this->fileLocation, ios::out | ios::trunc);
   while(n<vecSize){
        outputFile << this->students.at(n).Id<<","
        <<this->students.at(n).name<<","
        <<this->students.at(n).Age<<","
        <<this->students.at(n).PhoneNumber<<","
        << this->students.at(n).Gpa<<","
        << endl;
        n++;
   }
   outputFile.close();
}
};

int main()
    {
        User usur;  
        usur.menu();

       return 0;


    }
    