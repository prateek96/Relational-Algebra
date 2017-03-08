#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  vector<string> Schema;
int attributes;
int pattribues;

char attri[100];
map<string,int> ato;
map<string, int> name_to_table;
int cur_records=0;
int num;

string arrtostring(){int i=0;
        string h="";
        while(attri[i]!='\0'){h=h+char(attri[i]);i++;}return h;
}
void print_schema(vector<string> s){//cout<<s.size();
            for(int i=0;i<s.size();i++){cout<<s[i];cout<<"  |  ";}
            cout<<"\n";
}
class Table
    {   string f_name;



    public:
        vector< vector<string> > value;
        vector<string> schema;
        vector<int> type;
        bool opened;
        Table() {}
        map<string,int> attrbute_to_index;
        Table(string nam)
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
Table f;
string query;
vector <Table> Data;
int b_close(int index,string query){
        int ob=1;
        int cb=0;
        for(int i=index+1;i<=query.size();i++){
            if(query[i]=='(')
                ob++;
            else if(query[i]==')')
                cb++;
            if(cb==ob)return index+1;
        }



}
void print_Table(Table T){
	for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
    cout<<"\n";
    for(int f=0;f<T.schema.size();f++)
         {if(f!=T.schema.size()-1)cout<<setw(10)<<T.schema[f]<<"   |   ";
          else cout<<setw(10)<<T.schema[f];
         }
    cout<<"\n";

    for(int i=0;i<T.value.size();i++) {
    	for(int f=0;f<T.schema.size();f++)
       		{if(f!=T.schema.size()-1)cout<<setw(10)<<T.value[i][f]<<"   |   ";
        	 else cout<<setw(10)<<T.value[i][f];
       		}
       cout<<"\n";
   }
   for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
   cout<<"\n";
}


Table project_(string query ,int print);
Table set_difference_(string query,int print);
Table union_(string query,int print);

vector <string> data[100];
Table union_(string query,int print){
               bool out1=true;
               char c;
               //scanf("%c",&c);
               c=query[0];
               //cout<<query;
               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;

               //getline(cin,name,',');
               // cout<<name;
               Table T;
               name=query.substr(1,query.rfind(";")-1);
              // cout<<name;
               if(name.size()<=3 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }//cout<<query.substr(1,query.rfind(":"))<<" ";
             else{//cerr<<"fbad";
                   // T=project_(query.substr(2,query.rfind(":")-2),0);
                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);

                }


              bool out=false;
              //cout<<T.opened;
            // for(int i=0;i<3;i++)cout<<T.attrbute_to_index[T.schema[i]]<" ";
            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}
           // scanf("(");
               string name2;
               Table T2;
                    if(out){
                        return f ;
                    }
               //getline(cin,name2,')');
                name2=query.substr(query.rfind(";")+1,query.size()-1+1-1-1-query.rfind(";"));

                if(name2.size()<=3 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }//cout<<query.substr(1,query.rfind(":"))<<" ";
             else{
                   // T=project_(query.substr(2,query.rfind(":")-2),0);
                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);

                }
               // cout<<name;

              if(T2.opened!=true){cout<<"Error 102:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }
            for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){
                    cout<<"Error 103 : Not Union Comapatible\n";
                    out=true;
                    break;}

             }
            if(out){
                        return f ;
                    }
                if(T.schema.size()-T2.schema.size()){cout<<"Error 103 : Not Union Comapatible\n";out=true;}
                if(out){
                        return f ;
                    }
        //     if(print==1){
        //      for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
        //        cout<<"\n";
        //      for(int f=0;f<T.schema.size();f++)
        //                 {if(f!=T.schema.size()-1)cout<<setw(10)<<T.schema[f]<<"   |   ";else cout<<setw(10)<<T.schema[f]; }
        //                 cout<<"\n";
        //  //cerr<<"here"<<cur_records;
        //  map<vector<string> ,int> currently_printed;
        //  for(int i=0;i<T2.value.size();i++)
        //        {vector<string>cur;
        //            for(int f=0;f<T.schema.size();f++)
        //                 {if(f!=T.schema.size()-1)cout<<setw(10)<<T2.value[i][f]<<"   |   ";
        //                 else cout<<setw(10)<<T2.value[i][f];
        //                 cur.push_back(T2.value[i][f]);

        //                 }
        //         currently_printed[cur]=1;
        //         cout<<"\n";
        //        }


        //  for(int i=0;i<T.value.size();i++)
        //        {vector<string>cur;
        //            for(int f=0;f<T.schema.size();f++)
        //                 {cur.push_back(T.value[i][f]);

        //                 }


        //        if(currently_printed.find(cur)==currently_printed.end())
        //            {for(int f=0;f<T.schema.size();f++)
        //                 {if(f!=T.schema.size()-1)cout<<setw(10)<<T.value[i][f]<<"   |   " ;
        //                 else cout<<setw(10)<<T.value[i][f];

        //                 }
        //                 currently_printed[cur]=1;
        //         cout<<"\n";}

        //        }
        //        for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
        //     cout<<"\n";
        // currently_printed.clear();
        // return f;}
        // else{
                    Table ret;
             ret.opened=true;
             for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                        ret.attrbute_to_index[T.schema[f]]=f; }

         //cerr<<"here"<<cur_records;
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


               if(currently_printed.find(cur)==currently_printed.end())
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
Table set_difference_(string query,int print){
               bool out1=true;
               char c;
               //scanf("%c",&c);
               c=query[0];
               //cout<<query;
               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;

               //getline(cin,name,',');
               // cout<<name;
               Table T;
               name=query.substr(1,query.rfind("%")-1);
              // cout<<name;
               if(name.size()<=3 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }//cout<<query.substr(1,query.rfind(":"))<<" ";
             else{//cerr<<"fbad";
                   // T=project_(query.substr(2,query.rfind(":")-2),0);
                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                         { T=set_difference_(name.substr(1,name.size()-1),0);}

                }


              bool out=false;
              //cout<<T.opened;
            // for(int i=0;i<3;i++)cout<<T.attrbute_to_index[T.schema[i]]<" ";
            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}
           // scanf("(");
               string name2;
               Table T2;
                    if(out){
                        return f ;
                    }

                name2=query.substr(query.rfind("%")+1,query.size()-1+1-1-1-query.rfind("%"));

                if(name2.size()<=3 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }//cout<<query.substr(1,query.rfind(":"))<<" ";
             else{
                   // T=project_(query.substr(2,query.rfind(":")-2),0);
                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);

                }
               // cout<<name;

              if(T2.opened!=true){cout<<"Error 111:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }
            for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){cout<<"Error 103 : Not Set difference Comapatible\n";
                                                                    out=true;break;}

             }
            if(out){
                        return f ;
                    }
                if(T.schema.size()-T2.schema.size()){cout<<"Error 103 : Not Set difference Comapatible\n";out=true;}
                if(out){
                        return f ;
                    }


         //cerr<<"here"<<cur_records;
         if(print==1){

         set< vector<string> > Present;
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


               if(Present.find(cur)!=Present.end()){
                    Present.erase(cur);

               }

               }

        if(Present.size()==0){
            cout<<setw(10)<<"Empty Table:\n";
        }
        else{//cerr<<"debug";
            for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
            cout<<"\n";
            for(int f=0;f<T.schema.size();f++)
                        {if(f!=T.schema.size()-1)cout<<setw(10)<<T.schema[f]<<"   |   ";else cout<<setw(10)<<T.schema[f]; }
                        cout<<"\n";
            //cerr<<"debug";
            while(Present.size()!=0){vector<string> pr=*(Present.begin());
            for(int f=0;f<pr.size();f++)
                        {if(f==pr.size()-1){
                            cout<<setw(10)<<pr[f];
                            continue;
                            }
                            cout<<setw(10)<<pr[f]<<"   |   ";

                        }

                cout<<"\n";
            Present.erase(Present.begin());}
            for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
            cout<<"\n";
            }return f;}
            else{Table ret;
                ret.opened=true;
         set< vector<string> > Present;
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


               if(Present.find(cur)!=Present.end()){
                    Present.erase(cur);

               }

               }



            for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                         ret.attrbute_to_index[T.schema[f]]=f; }

            //cerr<<"debug";
            while(Present.size()!=0){
                    vector<string> pr=*(Present.begin());
                    ret.value.push_back(pr);
                    Present.erase(Present.begin());}

             ret.type=T.type;
             return ret;
            }


}
Table project_(string query ,int print){
             bool out1=true;
             char c;
             c=query[0];

             if(c!='('){cout<<"Error 109: Invalid Syntax.Use '('\n";out1= false;}
             if(!out1){return f;}
             string name;
             bool out=true;
             Table T;

             if(query.size()<=3 || query[2]!='('){
                 Table t(query.substr(1,query.find(":")-1));
                 T=t;
                 }//cout<<query.substr(1,query.rfind(":"))<<" ";
             else{  int index=b_close(2,query);
                    if(query[1]=='P')
                        T=project_(query.substr(2,index-2),0);
                     if(query[1]=='S')
                          T=set_difference_(query.substr(2,index-2),0);
                    if(query[1]=='U')
                          T=union_(query.substr(2,index-2),0);

                }

            if(T.opened!=true){
                    cout<<"Error 104:Table '"<< query.substr(1,query.rfind(":")-1)<< "' not found\n";
                    out=false;}
            if(out==false)return f;


             c=query[query.rfind(":")+1];
            if(c!='['){cout<<"Error 109: Invalid Syntax\n";out= false;}
//            if(out==false)return f;
//            if(print>=1){//cerr<<"DLFLKF";
//            string attributes_asked;
//           // getline(query.substr(query.rfind(":")+2,query.find("]")-1-query.find(":")),attributes_asked,']');
//            attributes_asked = query.substr(query.rfind("[")+1,query.rfind("]")-1-query.rfind("["));
//            vector<int> precords;
//            stringstream  lineStream(attributes_asked);
//            string  cell;
//            while(getline(lineStream,cell,',')){
//                    if(T.attrbute_to_index.find(cell)==T.attrbute_to_index.end())
//                        {cout<<"Error 101:Column '"<< cell<< "' not found\n";out=false;}
//                    else {  precords.push_back(T.attrbute_to_index[cell]);}}
//            if(out==false)return f;
//           // cerr<<"DLFLKF";
//           for(int i=0;i<precords.size()*18;i++)cout<<"-";
//            cout<<"\n";
//            for(int f=0;f<precords.size();f++)
//                        {if(f!=precords.size()-1)cout<<setw(10)<<T.schema[precords[f]]<<"   |   ";else cout<<setw(10)<<T.schema[precords[f]]; }
//            cout<<"\n";
//          // cerr<<"here"<<cur_records;
//            map<vector<string> ,int> currently_printed;
//            for(int i=0;i<T.value.size();i++)
//               {vector<string>cur;
//                   for(int f=0;f<precords.size();f++)
//                        {cur.push_back(T.value[i][precords[f]]);
//
//                        }
//
//
//               if(currently_printed.find(cur)==currently_printed.end())
//                   {for(int f=0;f<precords.size();f++)
//                        {if(f==precords.size()-1){
//                            cout<<setw(10)<<T.value[i][precords[f]];
//                            continue;
//                            }
//                            cout<<setw(10)<<T.value[i][precords[f]]<<"   |   ";
//
//                        }
//                        currently_printed[cur]=1;
//                cout<<"\n";}
//               }
//               for(int i=0;i<precords.size()*18;i++)cout<<"-";
//            cout<<"\n";
//          currently_printed.clear();
//
//          precords.clear();return f;}
//          else {
             Table ret;
             ret.opened=true;
             string attributes_asked;
            //getline(query.substr(query.rfind(":")+2,query.find("]")-1-query.find(":")),attributes_asked,']');
            vector<int> precords;
            attributes_asked = query.substr(query.rfind("[")+1,query.rfind("]")-1-query.rfind("["));
            stringstream  lineStream(attributes_asked);
            string  cell;
            while(getline(lineStream,cell,',')){
                    if(T.attrbute_to_index.find(cell)==T.attrbute_to_index.end())
                        {cout<<"Error 101:Column '"<< cell<< "' not found\n";out=false;}
                    else {  precords.push_back(T.attrbute_to_index[cell]);}}
            if(out==false)return f;

            for(int f=0;f<precords.size();f++)
                        {
                            ret.schema.push_back(T.schema[precords[f]]);
                            ret.attrbute_to_index[T.schema[precords[f]]]=f;
                            ret.type.push_back(T.type[f]);

                        }

         //cerr<<"here"<<cur_records;
            map<vector<string> ,int> currently_printed;
            for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<precords.size();f++)
                        {cur.push_back(T.value[i][precords[f]]);

                        }


               if(currently_printed.find(cur)==currently_printed.end())
                   {
                        ret.value.push_back(cur);


                        currently_printed[cur]=1;
                    }
               }
          currently_printed.clear();//cerr<<"vvjjc"<<ret.opened;;
          if(print>=1)print_Table(ret);
          return ret;

          precords.clear();
}









string remove_spaces(string h){
            string ret="";
            for(int i=0;i<h.size();i++){
                if(h[i]!=' ')ret+=h[i];
            }
            return ret;
                }
int main(){
        //Table T("Ab.txt");
        //cout<<T.value[0][1];
   // Data data;
    f.opened=true;
    string query;
    char a;
    cout<<"R-Algebra->>>> ";
    Schema schema;
    getline(cin,query,'\n');

    query =remove_spaces(query);

    a=query[0];
while(a!='Q'){

    if(a=='P'){project_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='U'){union_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";

    }
    else  if(a=='S'){set_difference_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";}
    else {cout<<"Error 105:Invalid Query\n";cout<<"R-Algebra->>>> ";}




        getline(cin,query,'\n');
        a=query[0];
    }
    exit(0);

}



