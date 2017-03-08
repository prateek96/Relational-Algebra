#include <bits/stdc++.h>
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
//struct Table
//    {
//        vector<string> schema;
//        map<string,int> attrbute_to_index;
//        vector< vector<string> > value;
//    };
vector <string> data[100];
string conditions;
// A utility method to apply an operator 'op' on operands 'a'
    // and 'b'. Return the result.
    bool  applyOp(char op, string a, string b)
    {
        switch (op)
        {
        case '>':
            return a > b;
        case '<':
            return a < b;
        case '!=':
            return a != b;
        case '=':
            return a == b;

        default:cout<<"error string";

        }
    }

// Returns true if 'op2' has higher or same precedence as 'op1',
    // otherwise returns false.
     bool hasPrecedence(char op1, char op2)
    {
        if (op2 == '(' || op2 == ')')
            return false;
        if ((op1 == '>' || op1 == '<') && (op2 == '=' || op2 == '!='))
            return false;
        else
            return true;
    }

    bool  evaluate(string expression,int Row_number)
    {
        //char[] tokens = expression.toCharArray();
            string tokens=expression;
         // Stack for numbers: 'values'
        stack<string> values ;

        // Stack for Operators: 'ops'
        stack<char> ops ;

        for (int i = 0; i < tokens.length(); i++)
        {
             // Current token is a whitespace, skip it
            if (tokens[i] == ' ')
                continue;

            // Current token is a number, push it to stack for numbers
            if ((tokens[i] >= '0' && tokens[i] <= '9' )|| (tokens[i] >= 'a' && tokens[i] <= 'z' ) )
            {
                string sbuf="";
                // There may be more than one digits in number
                while (i < tokens.length() && ((tokens[i] >= '0' && tokens[i] <= '9' )|| (tokens[i] >= 'a' && tokens[i] <= 'z' ) ))
                    sbuf+=(tokens[i++]);
                if(ato.find(sbuf)!=ato.end())values.push(data[Row_number][ato[sbuf]]);
                else values.push(sbuf);
            }

            // Current token is an opening brace, push it to 'ops'
            else if (tokens[i] == '(')
                ops.push(tokens[i]);

            // Closing brace encountered, solve entire brace
            else if (tokens[i] == ')')
            {
                while (ops.top() != '(')
                  {

                  bool j=applyOp(ops.top(), values.top(), values.top());ops.pop();
                  values.pop();values.pop();
                  values.push(j);}
                ops.pop();
            }

            // Current token is an operator.
            else if (tokens[i] == '>' || tokens[i] == '<' ||
                     tokens[i] == '!=' || tokens[i] == '=')
            {
                // While top of 'ops' has same or greater precedence to current
                // token, which is an operator. Apply operator on top of 'ops'
                // to top two elements in values stack
                while (!ops.empty() && hasPrecedence(tokens[i], ops.top()))
                 {

                  bool j=applyOp(ops.top(), values.top(), values.top());ops.pop();
                  values.pop();values.pop();
                  values.push(j);}

                // Push current token to 'ops'.
                ops.push(tokens[i]);
            }
        }

        // Entire expression has been parsed at this point, apply remaining
        // ops to remaining values
        while (!ops.empty())
            {

                  bool j=applyOp(ops.top(), values.top(), values.top());ops.pop();
                  values.pop();values.pop();
                  values.push(j);}

        // Top of 'values' contains result, return it
        return values.top();
    }






int main(){

   // Data data;
    char a;
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
    if(a=='P'){
        scanf("(%d,[",&pattribues);
        for(int i=0;i<pattribues;i++)
               {if(i==pattribues-1)scanf("%[a-z]]",&attri);
                 else scanf("%[a-z],",&attri);
               precords.push_back(ato[attri]);

               }
         for(int f=0;f<precords.size();f++)
                        {cout<<schema[precords[f]]<<"  |  ";}
                        cout<<"\n";
         //cerr<<"here"<<cur_records;
         for(int i=0;i<cur_records;i++)
               {//cout<<i;
                   for(int f=0;f<precords.size();f++)
                        {cout<<data[i][precords[f]]<<"    ";

                        }
                cout<<"\n";
               }


        precords.clear();
    }
    if(a=='S'){cout<<"daj";
            scanf("([");
            //string conditions;
            getline(cin,conditions,']');
            cout<<conditions;
            vector<int> print;
            for(int i=0;i<cur_records;i++)
            {
               // if(evaluate(i))print.push_back(i);
            }

    }


        start:
        cin>>a;
    }
    exit(0);

}


