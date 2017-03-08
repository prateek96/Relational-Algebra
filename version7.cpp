                                                        /*RELATIONAL ALGEBRA
RENAME-- R
NATURAL JOIN  --N
SELECT  --S
CARTESIAN PRODUCT   -C
DIVISION --%
PROJECT --P
UNION --U
SET DIFFERENCE -- D
AGGREGRATE -- A
INTERSECTION --I*/
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  vector<string> Schema;
//Global variables
int attributes;
int pattribues;
int cur_records=0;
int num;
bool error;
//Helper functions
//Converting string to int
long long inte(string c){
    long long ret=0;
    for(int i=0;i<c.size();i++)
        ret=ret*10+(c[i]-'0');
    return ret;
}
//Finding index of attribute in schema
int findi(vector<string> vec,string cell)
{
    int ret=-1;
    for(int i=0;i<vec.size();i++)
        if(vec[i]==cell)return i;
    return ret;
}
//finding the split point for query
int b_close(int index,string query){
        int ob=0;
        int cb=0;
        for(int i=index;i<=query.size();i++){
            if(query[i]=='(')
                ob++;
            else if(query[i]==')')
                cb++;
            if(query[i]==':' && cb + 1==ob )
                return i-1;

        }
}
//Checking for validity of the query
bool check(string query){
    int ob1,ob2,cb1,cb2;
    ob1=ob2=cb1=cb2=0;
    for(int i=0;i<query.size();i++){
        if(query[i]=='(')ob1++;
        if(query[i]==')')cb1++;
        if(query[i]=='[')ob2++;
        if(query[i]==']')cb2++;
        if(cb1>ob1 || cb2>ob2)return false;
    }
//    cout<<ob1<<" "<<ob2<<" "<<cb1<<" "<<cb2<<"\n";
    return (ob1==cb1 && ob2==cb2);
}
//For spliting query intl left and right half.
pair<string,string> resolve(int index,string q){
    int reqiqird=b_close(0,q);
    string name1=q.substr(1,reqiqird);
    string name2=q.substr(reqiqird+2,q.size()-1+1-reqiqird-3);
    return make_pair(name1,name2);
    }
//removing spaces from the query
string remove_spaces(string h){
            string ret="";
            for(int i=0;i<h.size();i++){
                if(h[i]!=' ')ret+=h[i];
            }
            return ret;
                }
//Prototype for a Table
class Table
    {   string f_name;



    public:
        vector< vector<string> > value;
        Schema schema;
        vector<int> type;
        bool opened;
        Table() {}
        map<string,int> attrbute_to_index;
        Table(string nam)                                           //opening file from name
            {f_name=nam;
            string name=nam+".txt";
            const char *myfile = name.c_str();
            ifstream  data(myfile);
            if(!data)opened=false;
            else{opened=true;
            string line;
            int i=0;
            while(getline(data,line))
                {
                    stringstream  lineStream(line);
                    string  cell;
                    vector<string> temp;
                    while(getline(lineStream,cell,','))
                        {
                            temp.push_back(cell);

                        }
                   if(i==0)
                    {schema=temp;
                        for(int k=0;k<temp.size();k++){
                            attrbute_to_index[schema[k]]=k;
                      //  cout<<attrbute_to_index[schema[k]]<<" "<<schema[k]<<"\n";
                                                        }

                    }
                   else
                    {
                      value.push_back(temp);
                    }
                i++;
               }
          string name=nam+"-info.txt";
          const char *myfile = name.c_str();
          ifstream  data(myfile);
          while(getline(data,line))
          {
            stringstream  lineStream(line);
            string  cell;
            vector<int> temp;
            while(getline(lineStream,cell,','))
            {
                if(cell[0]=='1')temp.push_back(1);
                else temp.push_back(0);

            }
            type=temp;



          }





    }}

    };
//Function Prototypes
Table project_(string query ,int print);
Table set_difference_(string query,int print);
Table union_(string query,int print);
Table intersection_(string query ,int print);
Table natural_(string query,int print);
Table cross_(string query,int print);
Table division_(string query,int print);
Table Rename_(string query ,int print);
Table select_(string query,int print);
Table Aggregrate_(string query,int print);
//Function to obtain Table
Table gettable(string name){
                Table T;
                if(name.size()<=2 || name[1]!='('){
                      Table t(name);
                      T = t;

                   }
                else{

                     if(name[0]=='P')                                      //Project
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')                                      //Union
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='D')                                      //Set Difference
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')                                       //Rename
                          T=Rename_(name.substr(1,name.size()-1),0);
                     if(name[0]=='I')                                       //Intersection
                          T=intersection_(name.substr(1,name.size()-1),0);
                     if(name[0]=='N')                                       //Natural Join
                          T=natural_(name.substr(1,name.size()-1),0);
                     if(name[0]=='C')                                        //Cartesian Product
                          T=cross_(name.substr(1,name.size()-1),0);
                     if(name[0]=='%')                                        //Division
                          T=division_(name.substr(1,name.size()-1),0);
                     if(name[0]=='S')                                        //Select
                          T=select_(name.substr(1,name.size()-1),0);
                     if(name[0]=='A')                                        //Aggregrate
                          T=Aggregrate_(name.substr(1,name.size()-1),0);



                  }
                return T;
}

Table f;
string query;
vector <Table> Data;

void print_Table(Table T){
    if(error)                                                            //Error found -skip printing
                return;
    if(!T.value.size())                                                  //Condition for empty table
        {cout<<"Empty Table\n";
         return;}
	for(int i=0;i<T.schema.size()*23;i++)cout<<"-";
    cout<<"\n";
    for(int f=0;f<T.schema.size();f++)
         {if(f!=T.schema.size()-1)cout<<setw(15)<<T.schema[f]<<"   |   ";
          else cout<<setw(15)<<T.schema[f]<<"        |";
         }
    cout<<"\n";

    for(int i=0;i<T.value.size();i++)
        {
    	for(int f=0;f<T.schema.size();f++)
       		{if(f!=T.schema.size()-1)
                cout<<setw(15)<<T.value[i][f]<<"   |   ";
        	 else cout<<setw(15)<<T.value[i][f]<<"        |";
       		}
        cout<<"\n";
        }
    for(int i=0;i<T.schema.size()*23;i++)
        cout<<"-";
    cout<<"\n";
}
//For string evaluation in select
int getWeight(char ch) {
   switch (ch) {
      case '!':return 3;
      case '^': return 2;
      case '|':return 1;
      default : return 0;
        }
}
string x;
// convert infix expression to postfix
string infixtopostfix(string infix, int size) {
   stack<char> s;
   int weight;
   int i = 0;
   int k = 0;
   char ch;
   string postfix="";
   while (i < size) {
      ch = infix[i];

      if (ch == '(') {

         s.push(ch);                                       //push opening paarenthesis
         i++;
         continue;
      }
      if (ch == ')') {



         while (!s.empty() && s.top() != '(') {            //pop till opening parenthesis
            postfix+= s.top();
            s.pop();

         }

         if (!s.empty()) {                                 //pop opening parenthesis if any
            s.pop();
         }
         i++;
         continue;
      }
      weight = getWeight(ch);
      if (weight == 0) {

         // operand append it to postfix expression
         postfix+= ch;

      }
      else {
         //  operator
         if (s.empty()) {

            s.push(ch);
         }
         else {

            while (!s.empty() && s.top() != '(' &&                 //pop till operators of higher precedence
                  weight <= getWeight(s.top())) {
               postfix+= s.top();
               s.pop();

            }

            s.push(ch);                                //push current character
         }
      }
      i++;
   }

   while (!s.empty()) {                                    //pop everything and add to the stack
      postfix+= s.top();
      s.pop();
   }
   return postfix;

}

char eval(string xi){
    string x=infixtopostfix(xi,xi.size());
    char a,b;
    stack<char> s;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] =='T' || x[i]== 'F')
            s.push(x[i]);
        else
        {
            a=s.top();
            s.pop();


            switch(x[i])
            {
            case '^':                                              //And condition
                b=s.top();
                s.pop();

                if(a=='T' && b=='T')                                //Both true
                    s.push('T');
                else s.push('F');
                break;
            case '|':                                             //Or condition
                b=s.top();
                s.pop();
                //cerr<<b;
                if(a=='F' && b=='F')                              //Both false
                    s.push('F');
                else s.push('T');
                break;
            case '!':                                             //Not operator
                if(a=='F')
                    s.push('T');
                else
                    s.push('F');
                break;

            }
        }
    }
    return s.top();

}
Table select_(string query ,int print){
             if(error)
                return f;
             bool out1=true;
             char c;
             c=query[0];
//           cout<<query<<"\n";
             pair<string,string> tables=resolve(0,query);
             if(c!='('){cout<<"Error 109: Invalid Syntax.Use '('\n";
                        out1= false;
                        error=true;}
             if(!out1){return f;}
             string name=tables.first;
             Table T;
             T=gettable(name);
             bool out=false;
             if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;
                    }
             if(error)
                return f;
             Table ret;
             //print_Table(T);
             ret.opened=true;
             string attributes_asked;


//            print_Table(T);
//            cout<<tables.second;9

            attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);            //stores the condition
            //cout<<attributes_asked;
            ret.schema=T.schema;
            ret.type=T.type;
            map<string ,int> attribute_index;
            for(int i=0;i<ret.schema.size();i++){
                attribute_index[ret.schema[i]]=i;
            }
            //cout<<"1";
            for(int i=0;i<T.value.size();i++){                                                   //iterating for all rows
                string current;
                for(int j=0;j<attributes_asked.size();j++){                                      //converting to bolean
                    //cout<<j;
                    if(attributes_asked[j]==')'||attributes_asked[j]=='(')
                        {current+=attributes_asked[j];continue;}
                    if(attributes_asked[j]=='!'||attributes_asked[j]=='^'||attributes_asked[j]=='|')
                        {current+=attributes_asked[j];continue;}
                    string lhs,rhs;
                    char c=attributes_asked[j];
                    while(c!='>' && c!='<' && c!='=' && c!='!'){

                        lhs+=c;
                        j++;
                        c=attributes_asked[j];
                    }
                    int op;
                    if(c=='<' && attributes_asked[j+1]!='=')op=1;
                    if(c=='>' && attributes_asked[j+1]!='=')op=2;
                    if(c=='>' && attributes_asked[j+1]=='='){op=3;j++;}
                    if(c=='<' && attributes_asked[j+1]=='='){op=4;j++;}
                    if(c=='=')op=5;
                    if(c=='!' && attributes_asked[j+1]=='='){op=6;j++;}
                    j++;
                    c=attributes_asked[j];
                    while(c!='>' && c!='<' && c!='=' && c!=')' && c!='^' && c!='!' && c!='|'){
                        rhs+=c;
                        j++;
                        c=attributes_asked[j];
                    }
                    j--;
                    if(attribute_index.find(lhs)==attribute_index.end())
                        {cout<<"Error 109:"<<lhs<<" not found\n";
                         out=true;
                         error=true;
                         return f;
                         break;
                        }
                    bool out =false;
                    string lhi=T.value[i][attribute_index[lhs]];
                    long long lh,rh;
                    if(T.type[attribute_index[lhs]]==0)
                        lh=inte(lhi);
                    //cerr<<i<<"%"<<lhs;
                    //cerr<<op<<"\n";
                    if(op==1){                                                             // operator <
                            if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {

                                    if(attribute_index.find(rhs)==attribute_index.end())               //invalid attribute
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    if(T.type[attribute_index[rhs]]==1)
                                        {
                                         cout<<"Error 110:Invalid comparison";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;

                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }
                            if(lh<rh)                                                      //checking condition
                                current+='T';
                            else
                                current+='F';

                    }
                    if(op==2){                                                            // operator >
                            if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {
                                    if(attribute_index.find(rhs)==attribute_index.end())
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    if(T.type[attribute_index[rhs]]==1)
                                        {
                                         cout<<"Error 110:Invalid Comparison";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;

                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }

                            if(lh>rh)                                                       //checking condition
                                current+='T';
                            else
                                current+='F';
                    }
                    if(op==3){                                                              //operator  >=
                          if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {
                                    if(attribute_index.find(rhs)==attribute_index.end())
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    if(T.type[attribute_index[rhs]]==1)
                                        {
                                         cout<<"Error 110:Invalid comparison";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;

                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }
                            if(lh>=rh)                                                       //checking condition
                                current+='T';
                            else
                                current+='F';

                    }
                    if(op==4){                                                              //operator  <=
                            if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {
                                    if(attribute_index.find(rhs)==attribute_index.end())
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    if(T.type[attribute_index[rhs]]==1)
                                        {
                                         cout<<"Error 110:Invalid Comparison";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;

                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }
                            if(lh<=rh)                                                        //checking condition
                                current+='T';
                            else
                                current+='F';

                    }
                    if(op==5){                                                                //operator  =
                            if(T.type[attribute_index[lhs]]==1)          //string
                            {
                                //cerr<<T.value[i][attribute_index[lhs]]<<"\n";
                                if( T.value[i][attribute_index[lhs]]==rhs.substr(1,rhs.size()-2))
                                    current+='T';
                                else
                                    current+='F';
                            }
                            else
                            {
                                if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {
                                    if(attribute_index.find(rhs)==attribute_index.end())
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }
                            if(lh==rh)
                                current+='T';
                            else
                                current+='F';

                            }
                    }
                    if(op==6){                                                             //operator !=
                            if(T.type[attribute_index[lhs]]==1)          //string
                            {
                                //cerr<<T.value[i][attribute_index[lhs]]<<"\n";
                                if( T.value[i][attribute_index[lhs]]!=rhs.substr(1,rhs.size()-2))
                                    current+='T';
                                else
                                    current+='F';
                            }
                            else
                            {
                                if(rhs[0]>='0' && rhs[0]<='9')
                                {
                                   rh=inte(rhs);
                                }
                            else
                                {
                                    if(attribute_index.find(rhs)==attribute_index.end())
                                        {cout<<"Error 109:"<<rhs<<" not found\n";
                                         out=true;
                                         error=true;
                                         return f;
                                         break;
                                        }
                                    rhs=T.value[i][attribute_index[rhs]];
                                    rh=inte(rhs);
                                }
                            if(lh!=rh)
                                current+='T';
                            else
                                current+='F';

                            }
                    }


                }
                if(out)
                    {break;
                     return f;}
                if(eval(current)=='T')                                            //evaluating the condition
                    ret.value.push_back(T.value[i]);
                }
          if(print==1)
            print_Table(ret);
          return ret;

}

Table cross_(string query,int print){
               bool out1=true;
               char c;
               c=query[0];
               if(c!='('){cout<<"Error 109: Invalid Syntax\n";
                          out1= false;
                          error=true;}
               if(out1==false)return f;
               string name;
               //Obtaining two tables
               pair<string,string> tables=resolve(0,query);
               name=tables.first;
               Table T;
               T=gettable(name);
               bool out=false;
               if(T.opened!=true){                                                          //Unable to open table
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


               T2=gettable(name2);


               if(T2.opened!=true){
                    cout<<"Error 102:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;}
               if(out){
                        return f ;
                     }
               if(error)
                return f;
               Table ret;
               ret.opened=true;
               map<string ,int> found;
               for(int f=0;f<T.schema.size();f++)
                        {
                         found[T.schema[f]]=1;                                        //Stores attributes of table 1

                         }
               set<string> common;                                                    //Stores common attributes

               int j=0;
               for(int f=0;f<T2.schema.size();f++)
                        {if(found.find(T2.schema[f])==found.end())
                            {
                                continue;
                            }
                         else common.insert(T2.schema[f]);

                         }
               for(int f=0;f<T.schema.size();f++){
                    if(common.find(T.schema[f])==common.end())
                        ret.schema.push_back(T.schema[f]);
                    else ret.schema.push_back("A."+T.schema[f]);                      //Adding A. to common attributes from table 1
                    ret.type.push_back(T.type[f]);
                }
              for(int f=0;f<T2.schema.size();f++){
                    if(common.find(T2.schema[f])==common.end())
                        ret.schema.push_back(T2.schema[f]);
                    else ret.schema.push_back("B."+T2.schema[f]);                    //Adding B. to common attributes from table 2
                    ret.type.push_back(T2.type[f]);
                }


              map<vector<string> ,int> currently_printed;
              vector<string> currentmatch;
              vector<string> currentmatch2;
              vector<string> tempo;
              int h=0;
              for(int i=0;i<T.value.size();i++)
               {
                   tempo=T.value[i];
                   for(int j=0;j<T2.value.size();j++){
                      {
                          tempo=T.value[i];                                        //Values from 1st table
                          for(int f=0;f<T2.schema.size();f++)                      //Add values from table 2
                            {
                                tempo.push_back(T2.value[j][f]);
                            }
                          if(currently_printed.find(tempo)==currently_printed.end())
                            ret.value.push_back(tempo);                            //Append into the result table

                      }
               }
               }

             if(print==1){
                print_Table(ret);
             }
             return ret;
        }
Table division_(string query,int print){
               if(error)
                return f;
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){
                    cout<<"Error 109: Invalid Syntax\n";
                    out1= false;
                    error=true;}
               if(out1==false)return f;
               //Obtaining two tables
               string name;
               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               T=gettable(name);
               bool out=false;

               if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }

               T2=gettable(name2);
               if(T2.opened!=true){
                    cout<<"Error 102:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;}
                if(out){
                        return f ;
                    }
             if(error)
                return f;
             bool possible=true;
             for(int i=0;i<T2.schema.size();i++)
             {
                 bool found=false;
                 for(int j=0;j<T.schema.size();j++)
                    if(T2.schema[i]==T.schema[j])found=true;
                 if(!found)
                    possible=false;
             }

             if(!possible)
                {cout<<"Error 110:Attributes are not a subset\n";
                error=true;
                return f;}                //Division not possible
             /*performing division using
             temp1 ← ΠR-S (r )
             temp2 ← ΠR-S ((temp1 x s ) – ΠR-S,S (r ))
             result = temp1 – temp2*/
             //calculating temp1
             vector<string> RS;

             Table temp1;
             vector<string> vec;
             vec.push_back("0");
             //cerr<<"here";
             for(int h=0;h<T.value.size();h++)
                temp1.value.push_back(vec);
             int k=0;
             int ki=0;
             for(int i=0;i<T.schema.size();i++)
             {
                 bool found=false;
                 for(int j=0;j<T2.schema.size();j++)
                    if(T.schema[i]==T2.schema[j])found=true;
                 if(!found)
                    {RS.push_back(T.schema[i]);
                     temp1.schema.push_back(T.schema[i]);
                     temp1.type.push_back(T.type[i]);
                     for(int h=0;h<T.value.size();h++){
                        temp1.value[h][ki]=T.value[h][i];
                        temp1.value[h].push_back("0");
                        }
                    ki++;

             }

             }
             for(int h=0;h<T.value.size();h++)temp1.value[h].pop_back();
             //cerr<<"here2";

             Table ret;                                                            //first table for temp2 i.e temp1*S
             ret.opened=true;
             map<string ,int> found;
             for(int f=0;f<temp1.schema.size();f++)
                        {
                         found[temp1.schema[f]]=1;

                         }
             set<string> common;                                                    //Stores common attributes

             int j=0;
             for(int f=0;f<T2.schema.size();f++)
                        {if(found.find(T2.schema[f])==found.end())
                            {
                                continue;
                            }
                         else common.insert(T2.schema[f]);

                         }
             for(int f=0;f<temp1.schema.size();f++){
                    if(common.find(temp1.schema[f])==common.end())
                        ret.schema.push_back(temp1.schema[f]);
                    else ret.schema.push_back("A."+temp1.schema[f]);
                    ret.type.push_back(temp1.type[f]);
                }
             for(int f=0;f<T2.schema.size();f++){
                    if(common.find(T2.schema[f])==common.end())
                        ret.schema.push_back(T2.schema[f]);
                    else ret.schema.push_back("B."+T2.schema[f]);
                    ret.type.push_back(T2.type[f]);
                }




             map<vector<string> ,int> currently_printed;
             vector<string> currentmatch;
             vector<string> currentmatch2;
             vector<string> tempo;
             int h=0;

             for(int i=0;i<temp1.value.size();i++)
               {
                   tempo=temp1.value[i];
                   for(int j=0;j<T2.value.size();j++)
                      {
                          tempo=temp1.value[i];
                          for(int f=0;f<T2.schema.size();f++)
                            {tempo.push_back(T2.value[j][f]);}
                          for(int it=0;it<ret.schema.size();it++)
                          if(currently_printed.find(tempo)==currently_printed.end())
                            {ret.value.push_back(tempo);currently_printed[tempo]=1;}

                      }

               }

             Table rsr;                                  //second table for temp2 i.e ΠR-S,S (r )
             vector<int> temp2t;
             vector<string> temp2s;
             for(int j=0;j<T.schema.size();j++)
                {
                    bool found=false;
                    for(int f=0;f<T2.schema.size();f++)
                    {
                        if(T.schema[j]==T2.schema[f])
                            found=true;
                    }
                    if(found){temp2s.push_back(T.schema[j]);temp2t.push_back(T.type[j]);}
                    else {rsr.schema.push_back(T.schema[j]);rsr.type.push_back(T.type[j]);}
                }
             for(int i=0;i<temp2t.size();i++)
                    {rsr.schema.push_back(temp2s[i]);rsr.type.push_back(temp2t[i]);}
             for(int i=0;i<T.value.size();i++)
               {vector<string> temp;
                vector<string> temp2;
                temp.clear();
                temp2.clear();
                for(int j=0;j<T.schema.size();j++)
                {
                    bool found=false;
                    for(int f=0;f<T2.schema.size();f++)
                    {
                        if(T.schema[j]==T2.schema[f])
                            found=true;
                    }
                    if(found)temp2.push_back(T.value[i][j]);
                    else temp.push_back(T.value[i][j]);
                }
                for(int i=0;i<temp2.size();i++)
                    temp.push_back(temp2[i]);
                rsr.value.push_back(temp);




               }
            Table ret1;                                            //ret1== temp2 without outer project
            //performing set difference on ret and rsr
            ret1.opened=true;
            set< vector<string> > Present;
            for(int i=0;i<ret.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<ret.schema.size();f++)
                        {
                        cur.push_back(ret.value[i][f]);

                        }
                Present.insert(cur);

               }

            int p=0;
            for(int i=0;i<rsr.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<rsr.schema.size();f++)
                        {cur.push_back(rsr.value[i][f]);

                        }


               if(Present.find(cur)!=Present.end()){
                    Present.erase(cur);

               }

               }



            for(int f=0;f<ret.schema.size();f++)
                        {ret1.schema.push_back(ret.schema[f]);
                         ret1.attrbute_to_index[ret.schema[f]]=f; }

            //cerr<<"debug";
            while(Present.size()!=0){
                    vector<string> pr=*(Present.begin());
                    ret1.value.push_back(pr);
                    Present.erase(Present.begin());}

             ret1.type=ret.type;

             //TEMP1=TEMP1
             //Calculating Temp2 performing project on ret1
             Table temp2;
             set<vector<string> >done;
             for(int j=0;j<T.schema.size()-T2.schema.size();j++)
                     {temp2.schema.push_back(ret1.schema[j]);
                     temp2.type.push_back(ret1.type[j]);}
             for(int i=0;i<ret1.value.size();i++)
             {
                 vector<string> vec;
                 for(int j=0;j<T.schema.size()-T2.schema.size();j++)
                     vec.push_back(ret1.value[i][j]);
                 if(done.find(vec)==done.end())
                    {temp2.value.push_back(vec);
                    done.insert(vec);}
             }
             //Temp2 completed
             //Performing set differnce of temp1 and temp2
             Table result;                                                           //Storing final result
             result.opened=true;
             set< vector<string> > Present1;
             for(int i=0;i<temp1.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<temp1.schema.size();f++)
                        {
                        cur.push_back(temp1.value[i][f]);

                        }
                Present1.insert(cur);

               }

            p=0;
            for(int i=0;i<temp2.value.size();i++)
               {vector<string>cur;
                for(int f=0;f<temp2.schema.size();f++)
                        {
                            cur.push_back(temp2.value[i][f]);
                        }

                if(Present1.find(cur)!=Present1.end()){
                    Present1.erase(cur);

               }

               }
            for(int f=0;f<temp1.schema.size();f++)
                        {result.schema.push_back(temp1.schema[f]);
                         result.attrbute_to_index[temp1.schema[f]]=f; }


            while(Present1.size()!=0){
                    vector<string> pr=*(Present1.begin());
                    result.value.push_back(pr);
                    Present1.erase(Present1.begin());}

            result.type=temp1.type;
             if(print>=1)
                print_Table(result);

             return result;
}
vector <string> data[100];
Table natural_(string query,int print){
               if(error)
                return f;
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){
                    cout<<"Error 109: Invalid Syntax\n";
                    out1= false;
                    error=true;}
               if(out1==false)return f;
               string name;

               //obtaining the two tables
               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               T=gettable(name);


              bool out=false;

              if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


               T2=gettable(name2);


              if(T2.opened!=true){
                    cout<<"Error 102:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;}
                if(out){
                        return f ;
                    }

             //Performing join
             Table ret;
             ret.opened=true;
             map<string ,int> found;
             for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                         T.attrbute_to_index[T.schema[f]]=f;
                         found[T.schema[f]]=1;
                         ret.attrbute_to_index[T.schema[f]]=f;
                         ret.type.push_back(T.type[f]); }
             vector<string> common;

             int j=0;
             //Obtaining common attributes
             for(int f=0;f<T2.schema.size();f++)
                        {
                            T2.attrbute_to_index[T2.schema[f]]=f;
                            if(found.find(T2.schema[f])==found.end())
                            {ret.schema.push_back(T2.schema[f]);
                            ret.attrbute_to_index[T2.schema[f]]=j+T.schema.size();j++;ret.type.push_back(T2.type[f]);}
                            else common.push_back(T2.schema[f]);

                         }


             map<vector<string> ,int> currently_printed;
             vector<string> currentmatch;
             vector<string> currentmatch2;
             vector<string> tempo;
             int h=0;
             for(int i=0;i<T.value.size();i++)
               {currentmatch2.clear();
                currentmatch.clear();
                   for(int k=0;k<common.size();k++)
                    {currentmatch.push_back(T.value[i][T.attrbute_to_index[common[k]]]);                 //Value from table 1
                    }
                   for(int j=0;j<T2.value.size();j++){
                      currentmatch2.clear();

                      for(int k=0;k<common.size();k++)
                        {currentmatch2.push_back(T2.value[j][T2.attrbute_to_index[common[k]]]);          //Value from table 2
                        }
                    bool match=true;
                    //checking if all common attributes have same value
                    for(int i=0;i<currentmatch.size();i++)if(currentmatch2[i]!=currentmatch[i])match=false;
                    if(match){tempo.clear();                                                               //Value same so Append row
                            for(int f=0;f<ret.schema.size();f++){
                                    //found has all attributs of Table T
                                    if(found.find(ret.schema[f]) !=  found.end())                          //Found in 1st table
                                        tempo.push_back(T.value[i][T.attrbute_to_index[ret.schema[f]]]);
                                    else
                                        tempo.push_back(T2.value[j][T2.attrbute_to_index[ret.schema[f]]]);

                            }
                            //checing if it is already present
                            if(currently_printed.find(tempo)==currently_printed.end())
                                {ret.value.push_back(tempo);
                                 currently_printed[tempo]=1;}



                    }
                   }
               }


            if(print==1){
                print_Table(ret);
            }
            return ret;


        }
Table union_(string query,int print){
               if(error)
                return f;
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){
                    cout<<"Error 109: Invalid Syntax\n";
                    out1= false;
                    error=true;}
               if(out1==false)return f;
               string name;

               //obtaining the two tables
               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               T=gettable(name);


               bool out=false;

               if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


               T2=gettable(name2);
               if(T2.opened!=true){
                    cout<<"Error 102:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;}
                if(out){
                        return f ;
                    }
              for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){                        //data type and name of attributes check
                    cerr<<T.schema[i]<<" "<<T2.schema[i];
                    cout<<"Error 108 : Not Union Comapatible\n";
                    out=true;
                    error=true;
                    break;}

             }
             if(out){
                        return f ;
                    }
             if(T.schema.size()-T2.schema.size()){                                         //number of attributes check
                        cout<<"Error 103 : Not Union Comapatible\n";
                        out=true;
                        error=true;}
             if(out){
                        return f ;
                    }
             //Performing Union
             Table ret;
             ret.opened=true;
             for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                        ret.attrbute_to_index[T.schema[f]]=f; }


             map<vector<string> ,int> currently_printed;
             for(int i=0;i<T2.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {
                        cur.push_back(T2.value[i][f]);

                        }
                currently_printed[cur]=1;
                ret.value.push_back(cur);

               }


             for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {cur.push_back(T.value[i][f]);

                        }


               if(currently_printed.find(cur)==currently_printed.end())             //Checking for duplicates
                   {
                        ret.value.push_back(cur);
                        currently_printed[cur]=1;
                   }
               }
            currently_printed.clear();
            ret.type=T.type;
            if(print==1){
                print_Table(ret);
            }
            return ret;


        }
Table intersection_(string query,int print){
               if(error)
                return f;
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){
                    cout<<"Error 109: Invalid Syntax\n";
                    out1= false;
                    error=true;}
               if(out1==false)return f;
               string name;

               //obtaining the two tables
               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               T=gettable(name);


               bool out=false;

               if(T.opened!=true){
                    cout<<"Error 1052:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


               T2=gettable(name2);


               if(T2.opened!=true){
                    cout<<"Error 1022:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;}
               if(out){
                        return f ;
                    }
               if(error)
                    return f;
               for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
                 if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){
                    cout<<"Error 103 : Not Intersection Comapatible\n";
                    out=true;
                    error=true;
                    break;}

               }
               if(out){
                        return f ;
                    }
               if(T.schema.size()-T2.schema.size()){
                        cout<<"Error 103 : Not Intersection Comapatible\n";
                        out=true;
                        error=true;}
               if(out){
                        return f ;
                      }
               //Performing Intersection
               Table ret;
               ret.opened=true;
               for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                        ret.attrbute_to_index[T.schema[f]]=f; }


               map<vector<string> ,int> currently_printed;            //stores rows of table 2
               for(int i=0;i<T2.value.size();i++)
                {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {
                        cur.push_back(T2.value[i][f]);

                        }
                currently_printed[cur]=1;


               }

             map<vector<string> ,int> currently_printed2;
             for(int i=0;i<T.value.size();i++)
               {vector<string>cur;                                              //current row of table 1
                   for(int f=0;f<T.schema.size();f++)
                        {cur.push_back(T.value[i][f]);

                        }

             //checking absent in Table 2 and not already in final table
             if(currently_printed.find(cur)!=currently_printed.end() && currently_printed2.find(cur)==currently_printed2.end())
                   {
                        ret.value.push_back(cur);
                        currently_printed[cur]=1;
                        currently_printed2[cur]=1;
                   }
               }
            currently_printed.clear();
            ret.type=T.type;
            if(print==1){
        	print_Table(ret);
            }
            return ret;
        }
Table set_difference_(string query,int print){
               if(error)
                return f;
               bool out1=true;
               char c;

               c=query[0];

               if(c!='('){
                    cout<<"Error 109: Invalid Syntax\n";
                    out1= false;
                    error=true;}
               if(out1==false)return f;
               string name;

               //obtaining the two tables
               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               T=gettable(name);
               bool out=false;

              if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}
           // scanf("(");
               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


               T2=gettable(name2);


              if(T2.opened!=true){
                    cout<<"Error 102:Table '"<< name2<< "' not found\n";
                    out=true;
                    error=true;;}
                if(out){
                        return f ;
                    }
             if(error)
                return f;
              for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){
                    cout<<"Error 103 : Not Set Difference Comapatible\n";
                    out=true;
                    error=true;
                    break;}

              }
            if(out){
                        return f ;
                    }
                if(T.schema.size()-T2.schema.size()){
                        cout<<"Error 103 : Not Set difference Comapatible\n";
                        out=true;
                        error=true;}
                if(out){
                        return f ;
                    }
            //Performing set difference
            Table ret;
            ret.opened=true;
            set< vector<string> > Present;                           //Stores all rows from table 1
            for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {
                        cur.push_back(T.value[i][f]);

                        }
                Present.insert(cur);

               }

            int p=0;
            for(int i=0;i<T2.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T2.schema.size();f++)
                        {cur.push_back(T2.value[i][f]);

                        }


               if(Present.find(cur)!=Present.end())                //If row from table 2 found  in table 1 remove
                {
                    Present.erase(cur);

                }
               }



            for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                         ret.attrbute_to_index[T.schema[f]]=f; }
            while(Present.size()!=0){                           //All remaining rows of table 1
                    vector<string> pr=*(Present.begin());
                    ret.value.push_back(pr);
                    Present.erase(Present.begin());}

            ret.type=T.type;
            if(print>=1)
                print_Table(ret);

            return ret;
}

Table project_(string query ,int print){
             if(error)
                return f;
             bool out1=true;
             char c;
             c=query[0];
//             cout<<query<<"\n";
             pair<string,string> tables=resolve(0,query);


             if(c!='('){
                        cout<<"Error 109: Invalid Syntax.Use '('\n";
                        out1= false;
                        error=true;}
             if(!out1){
                    return f;
             }
             //Obtaining the table
             string name=tables.first;
             Table T;
             T=gettable(name);
             bool out=false;
             if(T.opened!=true){
                    cout<<"Error 102:Table '"<< name<< "' not found\n";
                    out=true;
                    error=true;}
             if(out){
                return f;
             }
             if(error)
                return f;
             Table ret;
             ret.opened=true;
             string attributes_asked;

             vector<int> precords;
//            print_Table(T);
//            cout<<tables.second;

             attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);        //Stores name of asked attributes
             stringstream  lineStream(attributes_asked);
             string  cell;
             while(getline(lineStream,cell,',')){

                    if(findi(T.schema,cell)==-1)
                        {cout<<"Error 101:Column '"<< cell<< "' not found\n";
                         out=true;
                         error=true;
                         break;}
                    else {
                         precords.push_back(findi(T.schema,cell));}                         //Stores index of asked attributes
                    }
            if(out)return f;

             for(int f=0;f<precords.size();f++)                                            //New schema
                        {
                            ret.schema.push_back(T.schema[precords[f]]);
                            ret.attrbute_to_index[T.schema[precords[f]]]=f;
                            ret.type.push_back(T.type[precords[f]]);

                        }


            map<vector<string> ,int> currently_printed;
            for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<precords.size();f++)
                        {
                            cur.push_back(T.value[i][precords[f]]);                       //pushing values from required columns
                        }


               if(currently_printed.find(cur)==currently_printed.end())                  //checking for duplicates
                   {
                        ret.value.push_back(cur);
                        currently_printed[cur]=1;
                    }
               }
          currently_printed.clear();
          if(print>=1)print_Table(ret);
          return ret;

          precords.clear();
}
Table Rename_(string query,int print){
             if(error)
                {return f;}

             bool out1=true;
             char c;
             c=query[0];
             pair<string,string> tables=resolve(0,query);
             if(c!='('){
                    cout<<"Error 109: Invalid Syntax.Use '('\n";
                    out1= false;
                    error=true;}
             //obtaining table
             if(!out1){return f;}
             string name=tables.first;
             Table T;
             T=gettable(name);

             bool out=false;
             if(T.opened!=true){
                            cout<<"Error 102:Table '"<< name<< "' not found\n";
                            out=true;
                            error=true;
                            return f;}
//          print_Table(T);
             if(error)
                return f;
             Table ret;
             ret.opened=true;
             string attributes_asked;
             vector<int> precords;
//           cout<<tables.second;
             attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);               //Stores the new names
             stringstream  lineStream(attributes_asked);
             string  cell;
             int i=0;
             while(getline(lineStream,cell,',')){
                    T.schema[i]=cell;
                    T.attrbute_to_index[cell]=i;                                                  //Renaming the attributes
                    i++;
            }
//           print_Table(T);
             if(print)
                print_Table(T);
             return T;


}
Table Aggregrate_(string query,int print ){

             bool out1=true;
             char c;
             c=query[0];
             pair<string,string> tables=resolve(0,query);
             if(c!='('){
                    cout<<"Error 109: Invalid Syntax.Use '('\n";
                    out1= false;
                    error=true;}
             //obtaining table
             if(!out1){return f;}
             string name=tables.first;
             Table T;
             T=gettable(name);
             bool out=false;
             if(T.opened!=true){
                            cout<<"Error 102:Table '"<< name<< "' not found\n";
                            out=true;
                            error=true;
                            return f;}
//          print_Table(T);
            if(error)
                return f;
             Table ret;
             ret.opened=true;
             string attributes_asked;
             vector<int> precords;
//           cout<<tables.second;
             attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);               //Stores the new names
             stringstream  lineStream(attributes_asked);
             string  cell;
             int i=0;
             getline(lineStream,cell,',');
             string req=cell;
             int index=findi(T.schema,cell);
             if(index==-1)
                {
                            cout<<"Error 107:column '"<< cell<< "' not found\n";
                            out=true;
                            error=true;
                            return f;}
             vector<string> vec;

             while(getline(lineStream,cell,',')){

                         if(cell=="max"){                                                 //only for numeric columns
                            if(T.type[index]==1)
                                 {
                                cout<<"Error 109:Invalid Comparison\n";
                                out=true;
                                error=true;
                                return f;}

                            ret.schema.push_back(req+"."+cell);
                            long long  m=0;

                            for(int i=0;i<T.value.size();i++)
                                m=max(m,inte(T.value[i][index]));

                            string put="";
                            if(!m)
                                put.push_back('0');
                            while(m){
                                put+=char(m%10 +'0');
                                m/=10;}
                            reverse(put.begin(),put.end());
                            vec.push_back(put);

                            continue;
                         }
                         if(cell=="min"){                                                  //only for numeric columns
                            if(T.type[index]==1)
                                 {
                                cout<<"Error 109:Invalid Comparison\n";
                                out=true;
                                error=true;
                                return f;}
                            ret.schema.push_back(req+"."+cell);
                            long long  m=1000000000000;
                            for(int i=0;i<T.value.size();i++)
                                m=min(m,inte(T.value[i][index]));
                            string put="";
                            if(!m)
                                put.push_back('0');
                            while(m){
                                put+=char(m%10 +'0');
                                m/=10;}
                            reverse(put.begin(),put.end());
                            vec.push_back(put);

                            continue;
                         }
                         if(cell.substr(0,5)=="count" && cell[5]=='(' && cell[cell.size()-1]==')'){
                            ret.schema.push_back(req+"."+cell);
                            long long  m=0;

                            for(int i=0;i<T.value.size();i++)
                                {m+=((T.value[i][index])==cell.substr(6,cell.size()-2-6+1));
                                 }
                            if(cell[6]=='*')
                                m=T.value.size();
                            string put="";

                            if(!m)
                                put.push_back('0');
                            while(m){
                                put+=char(m%10 +'0');
                                m/=10;}

                            reverse(put.begin(),put.end());
                            vec.push_back(put);
                            continue;
                         }
                         if(cell=="sum"){
                            if(T.type[index]==1)                                     //only for numeric columns
                                 {
                                cout<<"Error 109:Invalid Comparison\n";
                                out=true;
                                error=true;
                                return f;}
                            ret.schema.push_back(req+"."+cell);
                            long long  m=0;
                            for(int i=0;i<T.value.size();i++)
                                m+=inte(T.value[i][index]);                           //adding all values
                            string put="";
                            if(!m)
                                put.push_back('0');
                            while(m){
                                put+=char(m%10 +'0');
                                m/=10;}
                            reverse(put.begin(),put.end());
                            vec.push_back(put);

                            continue;
                         }
                         if(cell=="avg"){                                                    //only for numeric columns
                            if(T.type[index]==1)
                                 {
                                cout<<"Error 109:Invalid Comparison\n";
                                out=true;
                                error=true;
                                return f;}
                            ret.schema.push_back(req+"."+cell);
                            long long  m=0;
                            for(int i=0;i<T.value.size();i++)
                                m+=inte(T.value[i][index]);
                            string put="";
                            m/=T.value.size();
                             if(!m)
                                put.push_back('0');
                            while(m){
                                put+=char(m%10 +'0');
                                m/=10;}
                            reverse(put.begin(),put.end());
                            vec.push_back(put);

                            continue;
                         }
                         cout<<"Error 111:Invalid query\n";
                            out=true;
                            error=true;



            }
            if(out)
                return f;
            ret.value.push_back(vec);


//           print_Table();
            if(print==1)
                {print_Table(ret);}
             return ret;


}
int main(){

    f.opened=true;
    string query;
    char a;
    cout<<"R-Algebra->>>> ";
    Schema schema;
    getline(cin,query,'\n');

    query =remove_spaces(query);
    while(!check(query)){
            cout<<"Error 109: Syntax error\n";
            cout<<"R-Algebra->>>> ";
            error=false;
            getline(cin,query,'\n');
            query=remove_spaces(query);
        }

    a=query[0];
while(a!='Q'){
    error=false;
    if(a=='N'){
            natural_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='A'){
            Aggregrate_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }

    else if(a=='%'){
            division_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='C'){
            cross_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='R'){
            Rename_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='I'){
            intersection_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='P'){
            project_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='U'){
        union_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else  if(a=='D'){
        set_difference_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else  if(a=='S'){
            select_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else  if(a=='H'){
            cout<<"The syntax for the operations are:\n";
            cout<<"Project : P(Tablename:[column1,column2....]) ex.P(studentsa:[name])\n";
            cout<<"Select : S(Tablename:[(conditions)]) ex.S(studentsa:[(age>5^class!=8)])\n";
            cout<<"Union : U(Tablename1:Tablename2)  ex.U(studensta:studentsb)\n";
            cout<<"Set Difference : D(Tablename1:Tablename2) ex.%(studensta:studentsb)\n";
            cout<<"Natural Join : N(Tablename1:Tablename2) ex.N(studensta:studentsb)\n";
            cout<<"Intersection : I(Tablename1:Tablename2) ex.I(studensta:studentsb)\n";
            cout<<"Division : %(Tablename1:Tablename2) ex.%(studensta:studentsb)\n";
            cout<<"Cartesian Product : C(Tablename1:Tablename2) ex.C(studensta:studentsb) \n";
            cout<<"Rename : R(Tablename:[column1-newname,column2-newname....]) ex.R(studentsa:[Firtsname,standard,years])\n";
            cout<<"Aggregrate : A(Tablename:[Columnname,operations_required] ex.A(studensta:[age,min,max,avg,sum,count(12),count(*)])\n";
            cout<<"Note:\n1.Outside pair of brackets is mandatory in select.\n";
            cout<<"2.count(*) gives count of total number of enteries.\n";
            cout<<"3.For nested queries Tablename replaced by appropriate Table.\n";
            cout<<"4.count(abc) gives the count of abc in the column.\n";
            cout<<"R-Algebra->>>> ";
            error=false;

    }
    else {cout<<"Error 105:Invalid Query\n";
          cout<<"R-Algebra->>>> ";}


    error=false;

        getline(cin,query,'\n');

        while(!check(query)){
            cout<<"Error 109: Syntax error\n";
            cout<<"R-Algebra->>>> ";
            error=false;
            getline(cin,query,'\n');
            query=remove_spaces(query);
        }
        a=query[0];
    }
    exit(0);

}




