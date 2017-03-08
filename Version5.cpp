#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  vector<string> Schema;
int attributes;
int pattribues;
//-DRENAME-- R
//-DNATURAL JOIN  --N
//SELECT  --S
//--DCROSS PRODUCT   -C
//--DDIVISION --%
//-DPROJECT --P
//-DUNION --U
//-DSET DIFFERENCE -- D
//-DINTERSECTION --I

//REMAINING
//EXTRA IDEAS -- 1.HELP
//SELECT  --S


char attri[100];
map<string,int> ato;
map<string, int> name_to_table;
int cur_records=0;
int num;
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
pair<string,string> resolve(int index,string q){
    int reqiqird=b_close(0,q);

    string name1=q.substr(1,reqiqird);

    string name2=q.substr(reqiqird+2,q.size()-1+1-reqiqird-3);
    return make_pair(name1,name2);
}

string arrtostring(){
        int i=0;
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
Table Rename_(string query );
Table f;
string query;
vector <Table> Data;

void print_Table(Table T){
    if(!T.value.size()){cout<<"Empty Table\n";return;}
	for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
    cout<<"\n";
    for(int f=0;f<T.schema.size();f++)
         {if(f!=T.schema.size()-1)cout<<setw(10)<<T.schema[f]<<"   |   ";
          else cout<<setw(10)<<T.schema[f]<<"        |";
         }
    cout<<"\n";

    for(int i=0;i<T.value.size();i++)
        {
    	for(int f=0;f<T.schema.size();f++)
       		{if(f!=T.schema.size()-1)cout<<setw(10)<<T.value[i][f]<<"   |   ";
        	 else cout<<setw(10)<<T.value[i][f]<<"        |";
       		}
        cout<<"\n";
        }
    for(int i=0;i<T.schema.size()*18;i++)cout<<"-";
    cout<<"\n";
}


Table project_(string query ,int print);
Table set_difference_(string query,int print);
Table union_(string query,int print);
Table intersection_(string query ,int print);
Table natural_(string query,int print);
Table cross_(string query,int print);
Table division_(string query,int print);

Table cross_(string query,int print){
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
               else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                     if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);
                     if(name[0]=='N')
                          T=natural_(name.substr(1,name.size()-1),0);
                     if(name[0]=='C')
                          T=cross_(name.substr(1,name.size()-1),0);
                     if(name[0]=='%')
                          T=division_(name.substr(1,name.size()-1),0);



                }


              bool out=false;

              if(T.opened!=true){cout<<"Error 1052:Table '"<< name<< "' not found\n";out=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }
             else{

                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                     if(name2[0]=='I')
                          T2=intersection_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='N')
                          T2=natural_(name2.substr(1,name2.size()-1),0);
                     if(name[0]=='C')
                          T2=cross_(name2.substr(1,name2.size()-1),0);
                     if(name[0]=='%')
                          T2=division_(name2.substr(1,name2.size()-1),0);

                }


              if(T2.opened!=true){cout<<"Error 1022:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }


                    Table ret;
             ret.opened=true;
             map<string ,int> found;
             for(int f=0;f<T.schema.size();f++)
                        {
                         found[T.schema[f]]=1;

                         }
             set<string> common;

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
                    else ret.schema.push_back("A."+T.schema[f]);
                    ret.type.push_back(T.type[f]);
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
            for(int i=0;i<T.value.size();i++)
               {
                   tempo=T.value[i];
                   for(int j=0;j<T2.value.size();j++){
                      {
                          tempo=T.value[i];
                          for(int f=0;f<T2.schema.size();f++)
                            tempo.push_back(T2.value[j][f]);
                          if(currently_printed.find(tempo)==currently_printed.end())
                            ret.value.push_back(tempo);

                      }
               }
               }

        if(print==1){
        	print_Table(ret);
        }
        return ret;


        }
Table division_(string query,int print){
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
               else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                     if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);
                     if(name[0]=='N')
                          T=natural_(name.substr(1,name.size()-1),0);

                }


              bool out=false;

              if(T.opened!=true){cout<<"Error 1052:Table '"<< name<< "' not found\n";out=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }
             else{

                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                    if(name2[0]=='I')
                          T2=intersection_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='N')
                          T2=natural_(name2.substr(1,name2.size()-1),0);

                }


              if(T2.opened!=true){cout<<"Error 1022:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }
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
             {cout<<"Error 110:Attributes are not a subset\n ";return f;}
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

             Table ret;
             ret.opened=true;
             map<string ,int> found;
             for(int f=0;f<temp1.schema.size();f++)
                        {
                         found[temp1.schema[f]]=1;

                         }
             set<string> common;

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
                for(int i=0;i<ret.schema.size();i++)
                    cout<<ret.schema[i]<<" ";



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
                          for(int it=0;it<ret.schema.size();it++)cout<<tempo[it]<<" ";
                          if(currently_printed.find(tempo)==currently_printed.end())
                            {ret.value.push_back(tempo);currently_printed[tempo]=1;}

                      }

               }

               Table rsr;
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
//                print_Table(T);
//                print_Table(T2);
//                cerr<<"rsr\n";
//                print_Table(rsr);
//                 cerr<<"temp1\n";

                Table ret1;
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
             //RET1== TEMP2 WITHOUT OUTER PROJECT FROM SLIDE
             //TEMP1=TEMP1 FROM SLIDE
             cout<<"ret1\n";
             print_Table(ret1);
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
//             cerr<<"temp1";print_Table(temp1);
//             cerr<<"temp2";print_Table(temp2);

             //TEMP2 HAS TEMP2 FROM SLIDES
             Table result;
                result.opened=true;
         set< vector<string> > Present1;
         for(int i=0;i<temp1.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<temp1.schema.size();f++)
                        {
                        cur.push_back(temp1.value[i][f]);

                        }
                Present.insert(cur);

               }

             p=0;
         for(int i=0;i<temp2.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<temp2.schema.size();f++)
                        {cur.push_back(temp2.value[i][f]);

                        }


               if(Present.find(cur)!=Present.end()){
                    Present.erase(cur);

               }

               }



            for(int f=0;f<temp1.schema.size();f++)
                        {result.schema.push_back(temp1.schema[f]);
                         result.attrbute_to_index[temp1.schema[f]]=f; }


            while(Present.size()!=0){
                    vector<string> pr=*(Present.begin());
                    result.value.push_back(pr);
                    Present.erase(Present.begin());}

             result.type=temp1.type;
             if(print>=1)
                print_Table(result);

             return result;











        }
vector <string> data[100];
Table natural_(string query,int print){
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
               else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                     if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);
                     if(name[0]=='N')
                          T=natural_(name.substr(1,name.size()-1),0);

                }


              bool out=false;

              if(T.opened!=true){cout<<"Error 1052:Table '"<< name<< "' not found\n";out=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }
             else{

                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                    if(name2[0]=='I')
                          T2=intersection_(name2.substr(1,name2.size()-1),0);
                     if(name2[0]=='N')
                          T2=natural_(name2.substr(1,name2.size()-1),0);

                }


              if(T2.opened!=true){cout<<"Error 1022:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }


                    Table ret;
             ret.opened=true;
             map<string ,int> found;
             for(int f=0;f<T.schema.size();f++)
                        {ret.schema.push_back(T.schema[f]);
                         found[T.schema[f]]=1;
                        ret.attrbute_to_index[T.schema[f]]=f;
                        ret.type.push_back(T.type[f]); }
             vector<string> common;

             int j=0;
             for(int f=0;f<T2.schema.size();f++)
                        {if(found.find(T2.schema[f])==found.end())
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
                    {currentmatch.push_back(T.value[i][T.attrbute_to_index[common[k]]]);
                    cerr<<T.value[i][T.attrbute_to_index[common[k]]]<<"\n";}
                   for(int j=0;j<T2.value.size();j++){
                      currentmatch2.clear();

                      for(int k=0;k<common.size();k++)
                        {currentmatch2.push_back(T2.value[j][T2.attrbute_to_index[common[k]]]);
                        cerr<<T2.value[j][T2.attrbute_to_index[common[k]]]<<"\n";}
                    bool match=true;
                    for(int i=0;i<currentmatch.size();i++)if(currentmatch2[i]!=currentmatch[i])match=false;
                    if(match){tempo.clear();
                            for(int f=0;f<ret.schema.size();f++){
                                    if(found.find(ret.schema[f]) !=  found.end())
                                        tempo.push_back(T.value[i][T.attrbute_to_index[ret.schema[f]]]);
                                    else
                                        tempo.push_back(T2.value[j][T2.attrbute_to_index[ret.schema[f]]]);

                            }
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
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
               else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                     if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);

                }


              bool out=false;

              if(T.opened!=true){cout<<"Error 1052:Table '"<< name<< "' not found\n";out=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }
             else{

                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                    if(name2[0]=='I')
                          T2=intersection_(name2.substr(1,name2.size()-1),0);

                }


              if(T2.opened!=true){cout<<"Error 1022:Table '"<< name2<< "' not found\n";out=true;}
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
Table intersection_(string query,int print){
               bool out1=true;
               char c;
               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


               pair<string,string> tables=resolve(0,query);

               name=tables.first;
               Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
               else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                     if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                     if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                     if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);

                }


              bool out=false;

              if(T.opened!=true){cout<<"Error 1052:Table '"<< name<< "' not found\n";out=true;}

               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
                 Table t1(name2);
                 T2=t1;
                 }
             else{

                     if(name2[0]=='P')
                          T2=project_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='U')
                          T2=union_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='S')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);
                    if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                    if(name2[0]=='I')
                          T2=set_difference_(name2.substr(1,name2.size()-1),0);

                }


              if(T2.opened!=true){cout<<"Error 1022:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }
            for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){
                    cout<<"Error 103 : Not Intersection Comapatible\n";
                    out=true;
                    break;}

             }
            if(out){
                        return f ;
                    }
                if(T.schema.size()-T2.schema.size()){cout<<"Error 103 : Not Intersection Comapatible\n";out=true;}
                if(out){
                        return f ;
                    }

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


               }

         map<vector<string> ,int> currently_printed2;
         for(int i=0;i<T.value.size();i++)
               {vector<string>cur;
                   for(int f=0;f<T.schema.size();f++)
                        {cur.push_back(T.value[i][f]);

                        }


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
         bool out1=true;
               char c;

               c=query[0];

               if(c!='('){cout<<"Error 109: Invalid Syntax\n";out1= false;}
               if(out1==false)return f;
               string name;


              pair<string,string> tables=resolve(0,query);
//              cout<<tables.first<<"\n";
//              cout<<tables.second<<"\n";
               name=tables.first;
              Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 }
             else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                    if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                    if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);

                }


              bool out=false;

            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}
           // scanf("(");
               string name2;
               name2=tables.second;
               Table T2;
                    if(out){
                        return f ;
                    }


                if(name2.size()<=2 || name2[1]!='('){
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
                    if(name2[0]=='R')
                          T2=Rename_(name2.substr(1,name2.size()-1));
                    if(name2[0]=='I')
                          T2=intersection_(name2.substr(1,name2.size()-1),0);


                }
// cout<<name;

              if(T2.opened!=true){cout<<"Error 102:Table '"<< name2<< "' not found\n";out=true;}
                if(out){
                        return f ;
                    }
            for(int i=0;i<min(T2.schema.size(),T.schema.size());i++){
               if(T.schema[i]!=T2.schema[i]||T.type[i]!=T2.type[i]){
                    cout<<"Error 103 : Not Set Difference Comapatible\n";
                    out=true;
                    break;}

             }
            if(out){
                        return f ;
                    }
                if(T.schema.size()-T2.schema.size()){cout<<"Error 103 : Not Set difference Comapatible\n";out=true;}
                if(out){
                        return f ;
                    }




            Table ret;
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
             if(print>=1)
                print_Table(ret);

             return ret;



}
int findi(vector<string> vec,string cell)
{
    int ret=-1;
    for(int i=0;i<vec.size();i++)
        if(vec[i]==cell)return i;
    return ret;
}
Table project_(string query ,int print){
             bool out1=true;
             char c;
             c=query[0];
//             cout<<query<<"\n";
             pair<string,string> tables=resolve(0,query);


             if(c!='('){cout<<"Error 109: Invalid Syntax.Use '('\n";out1= false;}
             if(!out1){return f;}
            string name=tables.first;
              Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;

                 T.opened=true;

                 }
             else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                    if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));
                    if(name[0]=='I')
                          T=intersection_(name.substr(1,name.size()-1),0);

                }


              bool out=false;



            if(T.opened!=true){cout<<"Error 102:Table '"<< name<< "' not found\n";out=true;}






             Table ret;
             ret.opened=true;
             string attributes_asked;

            vector<int> precords;
//            print_Table(T);
//            cout<<tables.second;

            attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);
            stringstream  lineStream(attributes_asked);
            string  cell;
            while(getline(lineStream,cell,',')){
                   // cout<<cell<<" ";
                    if(findi(T.schema,cell)==-1)
                        {cout<<"Error 101:Column '"<< cell<< "' not found\n";out=false;}
                    else {  precords.push_back(findi(T.schema,cell));}}
            //if(out==false)return f;

            for(int f=0;f<precords.size();f++)
                        {
                            ret.schema.push_back(T.schema[precords[f]]);
                            ret.attrbute_to_index[T.schema[precords[f]]]=f;
                            ret.type.push_back(T.type[f]);

                        }


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
Table Rename_(string query ){
             bool out1=true;
             char c;
             c=query[0];


             pair<string,string> tables=resolve(0,query);


             if(c!='('){cout<<"Error 109: Invalid Syntax.Use '('\n";out1= false;}
             if(!out1){return f;}
            string name=tables.first;
              Table T;
               if(name.size()<=2 || name[1]!='('){
                 Table t(name);
                 T=t;



                 }
             else{

                     if(name[0]=='P')
                         { T=project_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='U')
                         { T=union_(name.substr(1,name.size()-1),0);}
                    if(name[0]=='S')
                          T=set_difference_(name.substr(1,name.size()-1),0);
                    if(name[0]=='R')
                          T=Rename_(name.substr(1,name.size()-1));

                }


              bool out=false;



            if(T.opened!=true){cout<<"Error 10782:Table '"<< name<< "' not found\n";out=true;return f;}





//            print_Table(T);
             Table ret;
             ret.opened=true;
             string attributes_asked;

            vector<int> precords;
//            cout<<tables.second;

            attributes_asked = (tables.second).substr(1,tables.second.size()-2-1+1);
            stringstream  lineStream(attributes_asked);
            string  cell;
            int i=0;
            while(getline(lineStream,cell,',')){
                    T.schema[i]=cell;
                    ret.attrbute_to_index[cell]=i;
            i++;
            }



//           print_Table(T);
            return T;


}









string remove_spaces(string h){
            string ret="";
            for(int i=0;i<h.size();i++){
                if(h[i]!=' ')ret+=h[i];
            }
            return ret;
                }
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
int main(){

    f.opened=true;
    string query;
    char a;
    cout<<"R-Algebra->>>> ";
    Schema schema;
    getline(cin,query,'\n');

    query =remove_spaces(query);
    if(!check(query))
     {
        cout<<"Error 109: Syntax error\n";
        cout<<"R-Algebra->>>> ";
        getline(cin,query,'\n');

    }

    a=query[0];
while(a!='Q'){
    if(a=='N'){natural_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='D'){division_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";}
    else if(a=='C'){cross_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";}
    else if(a=='I'){intersection_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";}
    else if(a=='P'){project_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";
    }
    else if(a=='U'){union_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";

    }
    else  if(a=='S'){set_difference_(query.substr(1,query.size()-1),1);cout<<"R-Algebra->>>> ";}
    else {cout<<"Error 105:Invalid Query\n";cout<<"R-Algebra->>>> ";}




        getline(cin,query,'\n');
        if(!check(query))
    {
        cout<<"Error 109: Syntax error\n";
        cout<<"R-Algebra->>>> ";
        getline(cin,query,'\n');
        if(!check(query))
    {
        cout<<"Error 109: Syntax error\n";
        cout<<"R-Algebra->>>> ";
        getline(cin,query,'\n');
        if(!check(query))
    {
        cout<<"Error 109: Syntax error\n";
        cout<<"R-Algebra->>>> ";
        getline(cin,query,'\n');

    }

    }

    }
        a=query[0];
    }
    exit(0);

}




