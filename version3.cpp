#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
//typedef  vector<string> Data;
typedef  vector<string> Schema;
int attributes;
int pattribues;
vector<int> precords;
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
    void print_schema(){
                for(int f=0;f<T.schema.size();f++)
                        {if(f!=T.schema.size()-1)cout<<setw(10)<<T.schema[f]<<"   |   ";else cout<<setw(10)<<T.schema[f]; }
                        cout<<"\n";
    }

    };
vector <Table> Data;






vector <string> data[100];
void union_(){
               bool out1=true;
               char c;
               scanf("%c",&c);
               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return;
               string name;

               getline(cin,name,',');
               // cout<<name;
              Table T(name);
              bool out=false;
            // for(int i=0;i<3;i++)cout<<T.attrbute_to_index[T.schema[i]]<" ";
            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}
           // scanf("(");
               string name2;
                    if(out){
                        return  ;
                    }
               getline(cin,name2,')');
               // cout<<name;
              Table T2(name2);
              if(T2.opened!=true){cout<<"Error 102:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return  ;
                    }
             for(int i=0;i<T.schema.size();i++){
                if(T.type[i]-T2.type[i]){cout<<"Error 103 : Not Union Comapatible\n";out=true;}

             }
             if(out){
                        return  ;
                    }
                if(T.type.size()-T2.type.size()){cout<<"Error 103 : Not Union Comapatible\n";out=true;}
                if(out){
                        return  ;
                    }


         //cerr<<"here"<<cur_records;
         map<vector<string> ,int> currently_printed;
         T.print_schema();
         for(int i=0;i<T2.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {if(f!=T.schema.size()-1)cout<<setw(10)<<T2.value[i][f]<<"   |   ";
                        else cout<<setw(10)<<T2.value[i][f];
                        cur.push_back(T2.value[i][f]);

                        }
                currently_printed[cur]=1;
                cout<<"\n";
               }


         for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {cur.push_back(T.value[i][f]);

                        }


               if(currently_printed.find(cur)==currently_printed.end())
                   {for(int f=0;f<T.schema.size();f++)
                        {if(f!=T.schema.size()-1)cout<<setw(10)<<T.value[i][f]<<"   |   " ;
                        else cout<<setw(10)<<T.value[i][f];

                        }
                        currently_printed[cur]=1;
                cout<<"\n";}
               }
        currently_printed.clear();}
void set_difference_(){
              bool out1=true;
              char c;
              scanf("%c",&c);
              if(c!='('){cout<<"Error 109: Invalid Syntax.Use (\n";out1= false;}
              if(out1==false)return;
               string name;

               getline(cin,name,',');
               // cout<<name;
              Table T(name);
              bool out=false;
            // for(int i=0;i<3;i++)cout<<T.attrbute_to_index[T.schema[i]]<" ";
            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}
           // scanf("(");
               string name2;
                    if(out){
                        return  ;
                    }
               getline(cin,name2,')');
               // cout<<name;
              Table T2(name2);
              if(T2.opened!=true){cout<<"Error 102:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return  ;
                    }
             for(int i=0;i<T.schema.size();i++){
                if(T.type[i]-T2.type[i]){cout<<"Error 103 : Not Set_difference Comapatible\n";out=true;}

             }
             if(out){
                        return  ;
                    }
                if(T.type.size()-T2.type.size()){cout<<"Error 103 : Not Set_difference Comapatible\n";out=true;}
                if(out){
                        return  ;
                    }


         //cerr<<"here"<<cur_records;

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
            T.print_schema();
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
            Present.erase(Present.begin());}}


}
void project_(){
             bool out1=true;
             char c;
             cin>>c;
             //cout<<c;
             if(c!='('){cout<<"Error 109: Invalid Syntax.Use '('\n";out1= false;}
             if(!out1){return;}
             string name;
             bool out=true;
             if(!getline(cin,name,',')){{cout<<"Error 107:Invalid syntax";out=false;}
             if(out==false)return;};
               // cout<<name;
             Table T(name);

            // for(int i=0;i<3;i++)cout<<T.attrbute_to_index[T.schema[i]]<" ";
             if(T.opened!=true){cout<<"Error 104:Table '"<< name<< "' not found\n";out=false;}
             if(out==false)return;

//      //  scanf("%d,[",&pattribues);cout<<pattribues;
//        for(int i=0;i<pattribues;i++)
//               {if(i==pattribues-1)scanf("%[a-z A-Z]]",&attri);
//                 else scanf("%[a-z A-Z],",&attri);
//                if(T.attrbute_to_index.find(arrtostring())==T.attrbute_to_index.end())
//                    {cout<<"Error 101:Column '"<< attri<< "' not found";goto start;}
//                else {  precords.push_back(T.attrbute_to_index[arrtostring()]);}
//
//
//               }
                cin>>c;
            if(c!='['){cout<<"Error 109: Invalid Syntax\n";out= false;}
            if(out==false)return;
            string attributes_asked;
            getline(cin,attributes_asked,']');
            stringstream  lineStream(attributes_asked);
            string  cell;
            while(getline(lineStream,cell,',')){
                    if(T.attrbute_to_index.find(cell)==T.attrbute_to_index.end())
                        {cout<<"Error 101:Column '"<< cell<< "' not found\n";out=false;}
                    else {  precords.push_back(T.attrbute_to_index[cell]);}}
            if(out==false)return;

            for(int f=0;f<precords.size();f++)
                        {if(f!=precords.size()-1)cout<<setw(10)<<T.schema[precords[f]]<<"   |   ";else cout<<setw(10)<<T.schema[precords[f]]; }
            cout<<"\n";
         //cerr<<"here"<<cur_records;
            map<vector<string> ,int> currently_printed;
            for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<precords.size();f++)
                        {cur.push_back(T.value[i][precords[f]]);

                        }


               if(currently_printed.find(cur)==currently_printed.end())
                   {for(int f=0;f<precords.size();f++)
                        {if(f==precords.size()-1){
                            cout<<setw(10)<<T.value[i][precords[f]];
                            continue;
                            }
                            cout<<setw(10)<<T.value[i][precords[f]]<<"   |   ";

                        }
                        currently_printed[cur]=1;
                cout<<"\n";}
               }
          currently_printed.clear();

          precords.clear();}

int main(){
        //Table T("Ab.txt");
        //cout<<T.value[0][1];
   // Data data;
    char a;
    cout<<"R-Algebra->>>> ";
    Schema schema;
    cin>>a;
while(a!='Q'){
    if(a=='C')
    {   scanf("(%d,[",&attributes);
        for(int i=0;i<attributes;i++)
               {if(i==attributes-1)scanf("%[a-z]]",&attri);
                 else scanf("%[a-z],",&attri);
                schema.push_back(arrtostring());
                ato[arrtostring()]=i;

               }
        scanf(",%d,[[",&num);
        //cout<<num;
        for(int i=0;i<num;i++){//cout<<i;
                cur_records++;
                for(int ie=0;ie<attributes;ie++) {
                    if(ie==attributes-1 )
                     {if(i!=num-1){scanf("%[a-z]],[",&attri);}//cout<<arrtostring()<<" ";}
                     else {scanf("%[a-z]]])",&attri);}//cout<<arrtostring()<<" ";}
                     }
                 else {scanf("%[a-z],",&attri);}
                 //cout<<arrtostring()<<" ";
                data[i].push_back(arrtostring());


               }//cerr<<"here";

        }
       // cerr<<"here";

   // cerr<<"here";
    }
    if(a=='P')
        {
            project_();cout<<"R-Algebra->>>> ";
        }
    if(a=='U')
        {
            union_();cout<<"R-Algebra->>>> ";

        }
    if(a=='S'){
                set_difference_();cout<<"R-Algebra->>>> ";
              }





        cin>>a;
    }
    exit(0);

}



