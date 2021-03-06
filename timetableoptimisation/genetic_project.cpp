#include<bits/stdc++.h>
#define ll long long int
using namespace std;
class department//It is a class of department.If you don't know what a class is don't worry. It is just a structure which can take functions also. That's it.
{
public:
    string department_name;//Name of department
    int totalsubs;//count of total no of subject of that department.
    vector<int> subs;// A vector is just a array. This array stores the index of subjects that are in cariculum of this department.
    vector<vector<vector<int> > > timetable;//It is a 3d vector.
    vector<vector<vector<int> > > buffer;
    vector<int> sub_imp;//I took a limit that total subs cannot be more that 100;
    vector<int> count_sub_occur;
    department()
    {
        totalsubs = 0;
        sub_imp.assign(100,0);
        count_sub_occur.assign(100,0);
        buffer.assign(4,vector<vector<int> >(5, vector<int>(9,-1)));
        timetable.assign(4,vector<vector<int> >(5, vector<int>(9,-1)));//It signifies 4 timetable for each dep, with 5 rows and 9 cols.Each timetable is a member of population.-1 represents no subject.
    }
    void initialize_count_sub_occur(int key,int index)
    {
        count_sub_occur.assign(100,0);
        for(int i=0;i<5;i++)
            {
                for(int j=0;j<9;j++)
                {
                        //cout<<"inside for"<<endl;
                        if(key==1)
                        {
                            if(timetable[index][i][j]!=-1)
                            {
                            //cout<<"inside if"<<endl;
                                count_sub_occur[timetable[index][i][j]]++;
                            }
                        }
                        else
                        {
                            if(buffer[index][i][j]!=-1)
                            {
                            //cout<<"inside if"<<endl;
                                count_sub_occur[buffer[index][i][j]]++;
                            }
                        }
                }
            }
    }
    void initialize_para(vector<vector<int> > &sub_array,vector<department> &departments)//Here we initialize the parameters to start our genetic algorithm.
    {
       // cout<<"Inside initialize function"<<endl;
        for(int k=0;k<4;k++)
        {
            initialize_count_sub_occur(1,k);
        while(check_condition())
        {
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<9;j++)
                {
                    if(timetable[k][i][j]==-1 && rand()%3==1)//this condition is true when the block in which we are in is not filled yet and also 33% chance of selecting the block.
                    {
                        int temp = give_random_sub(sub_array,departments,k,i,j);
                        timetable[k][i][j] = subs[temp];
                        count_sub_occur[subs[temp]]++;
                        int noofdepcom = sub_array[subs[temp]].size();
                        //cout<<subs[temp]<<endl;
                        for(int l=0;l<noofdepcom;l++)//this loop fills timetable of all the departments with the same subject at the same place if they have that subject in common.
                        {
                            departments[sub_array[subs[temp]][l]].timetable[k][i][j] = subs[temp];
                        }
                        if(!check_condition())
                            break;
                    }
                    if(!check_condition())
                        break;
                }
                if(!check_condition())
                    break;
            }
        }
       // cout<<"outside while"<<endl;
        }
    }
    bool check_condition()//It checks condition, the condition is that all the subs of that dep should have their share of 4 hours.
    {
        //cout<<"inside check condition"<<endl;
        for(int i=0;i<totalsubs;i++)
        {
            if(count_sub_occur[subs[i]]!=4)
                return true;
        }
            return false;
    }
    int give_random_sub(vector<vector<int> > &sub_array,vector<department> &departments,int index,int index_row,int index_col)//It checks whether the sub that is generated randomly has completed its 4 hr quota or not, if completed than it gives another random no.
    {

        int key = 0;
        int temp;
        while(key==0)
        {
        temp = (rand()%totalsubs);
        while(count_sub_occur[subs[temp]]>=4)
        {
            temp = (rand()%(totalsubs));
            cout<<"temp: "<<temp<<endl;
            cout<<count_sub_occur[subs[temp]]<<endl;
        }
        int noofdepcom = sub_array[subs[temp]].size();
        cout<<"assigned noofdepcom "<<noofdepcom<<endl;
        for(int i=0;i<noofdepcom;i++)//this loop checks that the block we are going to fill in each department is empty or not. the subject is common to those departments.
        {

            if(departments[sub_array[subs[temp]][i]].timetable[index][index_row][index_col]!=-1)
            {
                key=2;
            }
        }
        if(key==2)
            key=0;
        else
            key = 1;
        }
        return temp;
    }
    void set_sub_imp(string sub[])//Give importance of each subject for each department
    {
        for(int i=0;i<totalsubs;i++)
        {
            int x;
            cout<<"What is importance of "<<sub[subs[i]]<<" for "<<department_name<<" department in scale of 1 to 10 (1 signifies very less important and 10 signifies extremely important."<<endl;
            cin>>x;
            sub_imp[subs[i]] = x;
        }
    }
};
void apply_condition(vector<department> &departments,int d, vector<vector<int> > &sub_array)
{
    cout<<"inside apply condition"<<endl;
     for(int i=0;i<4;i++)
    {
        for(int j=0;j<d;j++)
        {
            departments[j].initialize_count_sub_occur(0,i);
            while(departments[j].check_condition())
            {
                //cout<<"inside apply condition while"<<endl;
                for(int k=0;k<departments[j].totalsubs;k++)
                {
                    int subject = departments[j].subs[k];
                    cout<<"subject: "<<subject<<"count :"<<departments[j].count_sub_occur[subject]<<endl;

                    if(departments[j].count_sub_occur[subject]<4)
                    {
                        cout<<"inside first if"<<endl;
                        for(int l=0;l<5;l++)
                        {
                            int count = 0;

                            for(int r=0;r<9;r++)
                            {
                                bool key = false;
                                for(int x=0;x<sub_array[subject].size();x++)
                                {
                                    if(departments[sub_array[subject][x]].buffer[i][l][r]!=-1)
                                        key=true;
                                }
                                if(!key)
                                {
                                    cout<<"inside decider if"<<endl;
                                    for(int x=0;x<sub_array[subject].size();x++)
                                    {
                                        departments[sub_array[subject][x]].buffer[i][l][r] = subject;
                                        departments[sub_array[subject][x]].count_sub_occur[subject]++;
                                    }
                                    count++;
                                    break;

                                }

                            }
                            if(count>0)
                                break;
                        }
                        departments[j].initialize_count_sub_occur(0,i);
                    }
                    else
                    {
                        if(departments[j].count_sub_occur[subject]>4)
                        {
                            for(int l=0;l<5 ;l++)
                            {
                                bool key = false;
                                for(int r=0;r<9;r++)
                                {
                                    if(departments[j].buffer[i][l][r]==subject)
                                    {
                                        key = true;
                                        cout<<"inside less decider if"<<endl;
                                        for(int x=0;x<sub_array[subject].size();x++)
                                        {
                                            departments[sub_array[subject][x]].buffer[i][l][r] = -1;
                                            departments[sub_array[subject][x]].count_sub_occur[subject]--;
                                        }
                                        break;
                                    }
                                }
                                if(key)
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
}
void crossover(vector<department> &departments,int d)
{
    cout<<"inside crossover"<<endl;
    for(int i=0;i<4;i++)
    {
        int temp = rand()%4;
        while(temp==i)
        {
            cout<<"inside while"<<endl;
            temp=rand()%4;
        }
        for(int j=0;j<9;j++)
        {
            if(rand()%3==1)
            {
                for(int k=0;k<5;k++)
                {
                     for(int l=0;l<d;l++)
                    {
                        departments[l].buffer[i][k][j] = departments[l].timetable[temp][k][j];
                    }
                }
            }
            else
            {
                 for(int k=0;k<5;k++)
                {
                     for(int l=0;l<d;l++)
                    {
                        departments[l].buffer[i][k][j] = departments[l].timetable[i][k][j];
                    }
                }
            }
        }
    }
    cout<<"outside crossover"<<endl;
}
void mutation(vector<department> &departments,int d,vector<vector<int> > &sub_array)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<d;j++)
        {
            int temp = rand()%10;
            for(int r = 0;r<temp;r++)
            {
                int subject = rand()%departments[j].totalsubs;
                subject = departments[j].subs[subject];
                for(int k=0;k<5;k++)
                {
                    for(int l=0;l<9;l++)
                    {
                        bool key = false;
                        for(int x=0;x<sub_array[subject].size();x++)
                        {
                            if(departments[sub_array[subject][x]].timetable[i][k][l]!= -1)
                                key = true;
                        }
                        if(!key && rand()%5==1)
                        {
                            for(int x=0;x<sub_array[subject].size();x++)
                            {
                                departments[sub_array[subject][x]].timetable[i][k][l]= subject;
                            }
                        }
                    }
                }

            }
        }

    }
}
int main()
{
    srand(time(0));
    int d,n;//d is for number of departments and n is for total number of subjects.
    cout<<"Please define the number of departments :"<<endl;
    cin>>d;
    cout<<"Please name them one by one:"<<endl;
    vector<department> departments(d);//Here we initialize the departments. As we know that 'department' is a class.Variable departments is a vector of class 'department'. If you don't know much about classes please don't bother. It is just like a structure.
    for(int i=0;i<d;i++)
    {
        scanf("\n");//Please ignore this if you din't get it.
        getline(cin,departments[i].department_name);//here we read the whole line, hence getline() is used instead of cin.
    }
    cout<<"Please tell the total no of subjects: "<<endl;
    cin>>n;
    string sub[n];//It is an array of strings to store the subject names.
    vector<vector<int> > sub_array;//It is an array which stores the departments index nos to which the nth subject is common. You will understand in code furthur.
    sub_array.assign(n,vector<int>(0) );
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
            departments[temp-1].subs.push_back(i);//For department no 'temp-1' we know that this subject is in its cariculum so we add this subject in subject list of that department.
            departments[temp-1].totalsubs++;//we update total subjects count for that department.
        }
    }
    for(int i=0;i<d;i++)
    {
        departments[i].initialize_para(sub_array,departments);
    }
    /*for(int i=0;i<d;i++)
    {
        departments[i].set_sub_imp(sub);
    }*/
    crossover(departments,d);
    apply_condition(departments,d,sub_array);
    mutation(departments,d,sub_array);
    apply_condition(departments,d,sub_array);
    for(int l=0;l<d;l++)
    {
        cout<<"Department: "<<departments[l].department_name<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<5;j++)
            {
                for(int k=0;k<9;k++)
                {
                    cout<<departments[l].buffer[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
}
