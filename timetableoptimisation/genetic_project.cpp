#include<bits/stdc++.h>
#define ll long long int
using namespace std;
class department//It is a class of department.If you don't know what a class is don't worry. It is just a structure which can take functions also. That's it.
{
public:
    string department_name;//Name of department
    int totalsubs;//count of total no of subject of that department.
    vector<int> subs;// A vector is just a array. This array stores the index of subjects that are in cariculum of this department.
    vector<int> timetable[5];//This is a 2D array initialization for timetable of that department.
    department()
    {
        for(int i=0;i<5;i++)
        {
            timetable[i].assign(9,0);
        }
    }
    void initialize_para()//Here we initialize the parameters to start our genetic algorithm.
    {

    }
};

int main()
{
    int d,n;//d is for number of departments and n is for total number of subjects.
    cout<<"Please define the number of departments :"<<endl;
    cin>>d;
    cout<<"Please name them one by one:"<<endl;
    vector<department> departments(d);//Here we initialize the departments. As we know that 'department' is a class.Variable departments is a vector of class 'department'. If you don't know much about classes please don't bother. It is just like a structure.
    for(int i=0;i<d;i++)
    {
        scanf("\n");//Please ignore this if you din't get it.
        getline(cin,departments[i].department_name);//here we read the whole line, hence getline is used instead of cin.
    }
    cout<<"Please tell the total no of subjects: "<<endl;
    cin>>n;
    string sub[n];//It is an array of strings to store the subject names.
    vector<int> sub_array[n];//It is an array which stores the departments index nos to which the nth subject is common. You will understand in code furthur.
    for(int i=0;i<n;i++)
    {
        int x;//No of departments to which ith subject is common to.
        cout<<"Name of subject: "<<endl;
        cin>>sub[i];
        cout<<"specify the no of departments it is common to "<<endl;
        cin>>x;
        cout<<"specify the departments to whom the sub is applicable(please specify the index of department, not the name) "<<endl;
        for(int j=0;j<x;j++)
        {
            int temp;
            cin>>temp;
            sub_array[i].push_back(temp-1);//store the department index to which the subject is common.
            departments[temp-1].subs.push_back(i+1);//For department no 'temp-1' we know that this subject is in its cariculum so we add this subject in subject list of that department.
            departments[temp-1].totalsubs++;//we update total subjects count for that department.
        }
    }

}