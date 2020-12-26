#include "function.h"
#include "constants.h"
#include "limits.h"
#include "cfloat"
#include "string"
#include "ResourcePath.hpp"
func::func(){}
//void func::setSidebar(Sidebar& sidebar)
//{
//    this->sidebar = sidebar;
//
//}
void func::Init(Sidebar& sidebar){
    Input(queue, equation, sidebar);       //typing the function
    cout<<queue<<endl;
    ShuntingYard(queue, result);    //shunting yard
    cout<<result<<endl;
    
    fileName = resourcePath() + "side.txt";

}

void func::Draw(sf::RenderWindow &window, Sidebar& sidebar, double zoom, bool del){

    window.clear();


    //-------DRAWING THE FUNCTION------------------
    Queue<token*> copy = queue;
    // deleting all functions from sidebar
    if(del == true){
        
        remove("side.txt");
        sidebar.Save("side.txt", del, equation);

    }
    //keep loading
    sidebar.Load("side.txt", del);
    

//    double k = min;
//    cout<<"min: "<<min<<endl;
//    cout<<"max: "<<max<<endl;
    for(double i = min; i<= max;){
        // i is x_coord

//        i = i*zoom;
        double temp1 = RPN(result, i);  // y_coord


        //point 1

        double x1 = ORIGIN_X + i*zoom;
        double y1 = ORIGIN_Y - temp1*zoom;
        
        i += 1/(zoom*2);

        if (y1 > SCREEN_HEIGHT || y1 < 0 || x1 > SCREEN_WIDTH || x1 < 0 ){
            continue;
        }


//        sf::VertexArray lines(sf::LinesStrip, 3);

                    sf::Vector2f _dot( x1, y1);
                        sf::CircleShape dot;
                                dot.setPosition(_dot);
                                dot.setRadius(3);
                                dot.setFillColor(sf::Color::Yellow);
                            window.draw(dot);

//        sf::Vector2f dot1( x1, y1);
        


//        lines[0].color = sf::Color::Yellow;
//        lines[0].position = dot1;
        
        
        //        point 2
//        double temp2 = RPN(result, i);
//            double x2 = ORIGIN_X + i*zoom;
//            double y2 = ORIGIN_Y - temp2*zoom;
        
//            sf::Vector2f dot2(x2, y2);
//            lines[1].position = dot2;
//            lines[1].color = sf::Color::Yellow;
//            window.draw(lines);

    }
}

double RPN(Queue<token*> input, double value){
    Stack<token*> s;
    double total;

    while(!input.Empty()){  //while not empty

        token* temp = input.DeQ();      //Pop the queue
        if(temp->Face() == 'n'){        //if the token is number
            s.Push(temp);               //push into stack
        }
        if(temp->Face() == 'v'){
            s.Push(new number(value));      //replace the value with real number
        }
        if(temp->Face() == 'o'){        //if the token is an operator

            string sign = static_cast<op*>(temp)->Sign();           //pop operator from the queue

            if(sign == "sin"){
                double num = static_cast<number*>(s.Pop())->Value();     //pop number from the stack
                total = sin(num);
            }
            else if(sign == "tan"){
                double num = static_cast<number*>(s.Pop())->Value();     //pop number from the stack
                total = tan(num);
            }
            else if(sign == "cos"){
                double num = static_cast<number*>(s.Pop())->Value();     //pop number from the stack
                total = cos(num);
            }
            else if(sign == "cot"){
                double num = static_cast<number*>(s.Pop())->Value();     //pop number from the stack
                total = 1/(tan(num));
            }

            else{
                double s1 = static_cast<number*>(s.Pop())->Value();     //pop number once from the stack
                double s2 = static_cast<number*>(s.Pop())->Value();     //pop number twice from the stack

                if(sign == "+"){        //plus sign
                    total = s1 + s2;
                 }
                if(sign == "*"){        //times
                    total = s1 * s2;
                }
                if(sign == "-"){
                    total = s2 - s1;
                }
                if(sign == "/"){
//                    assert(s1!=0);
                    total = s2/s1;
                }
                if(sign == "^"){
                    total = pow(s2, s1);
                }
            }
            s.Push(new number(total));      //push the total into the stack
        }
    }

    double end = static_cast<number*>(s.Pop())->Value();    //return the last number in the stack

    if(!s.Empty()){     //if the stack is not empty
        ErrorMesg();     //error
        return 0;       //
    }
    return end;
}
void ErrorMesg(){
    cout<<"Invalid Input! Extra added"<<endl;
}
void ShuntingYard(Queue<token*> input, Queue<token*> &result){
    cout<<input<<endl;
    Stack<token*> s;

    cout<<"the queue: "<<input<<endl;

    while(!input.Empty()){      //DEQ input until it's empty
        token* temp = input.DeQ();      //token from input
        cout<<"token in shunting yard: "<<temp<<endl;
        
        
        int pre_of_temp = static_cast<op*>(temp)->Pre();        //the precedence

        if(temp->Face() == 'n' || temp->Face() == 'v'){
            result.EnQ(temp);
        }

        else{

            if(pre_of_temp < 4){        //not parenthese

                if(!s.Empty() ){ //pop if stack not empty
                    token* in_stack = s.Pop();  //poping the one in stack to compare
                    int pre_of_in_stack = static_cast<op*>(in_stack)->Pre();

                    if(pre_of_in_stack == 4){       //if parentheses, push back
                        s.Push(in_stack);

                    }

                    else{                       
                        if(pre_of_in_stack >= pre_of_temp && pre_of_in_stack!=4){
                            bool done = false;
                            while(pre_of_in_stack >= pre_of_temp && !done){
                                result.EnQ(in_stack);
                                if(!s.Empty()){
                                    in_stack = s.Pop();
                                    pre_of_in_stack = static_cast<op*>(in_stack)->Pre();
                                    if(pre_of_in_stack ==4){        //push back if the one in stack is parentheses
                                        s.Push(in_stack);
                                        done = true;

                                    }
                                }
                                else if(s.Empty()) {
                                    done = true;

                                }
                            }
                        }

                        if(pre_of_in_stack < pre_of_temp){
                            s.Push(in_stack);
                        }
                    }
                }

                s.Push(temp);
            }
            if(pre_of_temp == 4){           //if "("
                s.Push(temp);
            }

            if(pre_of_temp == 5){       // if ")"
                token* pop_value = s.Pop();
                int pre_of_pop_value = static_cast<op*>(pop_value)->Pre();
                while(pre_of_pop_value != 4){
                    result.EnQ(pop_value);
                    pop_value = s.Pop();
                    pre_of_pop_value = static_cast<op*>(pop_value)->Pre();
                }


            }
//            cout<<"================================"<<endl;
//            cout<<endl<<"input: "<<input<<endl;

//            cout<<endl<<"stack: "<<s<<endl;

//            cout<<endl<<"result: "<<result<<endl;
//            cout<<endl<<"stack: "<<s<<endl;


        }

    }
    
    while(!s.Empty()){
        token* pop = s.Pop();
        result.EnQ(pop);
    }
//    cout<<"================================"<<endl;


//    cout<<endl<<"i: "<<input<<endl;

//    cout<<endl<<"r: "<<result<<endl;

//    cout<<endl<<"s: "<<s<<endl;

}

double combine(double a, double b){
    if(b == 0){     //special case where b = 0;
        return a*10;
    }
    else{
        if(b == -1){
            b = 0;
        }
       double times = 1;
       while (times <= b)
          times *= 10;
       return a*times + b;
    }
}
void func::Input(Queue<token*> &queue, string &equation, Sidebar& sidebar){
    string s;   // first char
    string o;   // another char
    string r;   // result string
    bool done = false;
    double num = 0; //the number
    stringstream ss_str;    //string stream for string
    stringstream ss_num;    //string stream for number
    stringstream ss;        //regular string stream
    cout<<endl<<endl<<"=================================="<<endl<<endl;
    cout<<"type: ";
    s = cin.get();
    equation = equation + s;
    while(!done){

        o = cin.get();      //start getting character one by one
        //
//        if(o != " "){
            equation = equation + o;
//        }
        if(o == " "){           //if it's a space --> evaluate
            ss<<s;
            ss>>num;
            if(!ss.fail()){
                ss_num<<s;
                ss_num>>num;
                ss_num.str("");
                ss_num.clear();
                queue.EnQ(new number(num));

            }
            else{
                ss_str<<s;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else if(r == "e")
                    queue.EnQ(new number(E));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            s = " ";
        }

        if(o == "\n" ){
            ss<<s;
            ss>>num;
            if(!ss.fail()){
                ss_num<<s;
                ss_num>>num;
                queue.EnQ(new number(num));
                ss_num.str("");
                ss_num.clear();

            }
            else{
                ss_str<<s;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            s = " ";
            done = true;            //stop everything when "return" found
         }
        s = s + o;  //concantenate
    }
    cout<<"result : "<<equation<<endl;
    
//    int n = fileName.length();
//    char char_array[n + 1];
//    strcpy(char_array, fileName.c_str());
    
    sidebar.Save("side.txt", false, equation);
//    sidebar.printString();


}
void Save(char fileName[], string equation, Sidebar& sidebar){ // Save can't be in draw
    ofstream outfile;

    outfile.open(fileName, outfile.app);    //append at the end
//    outfile.open(fileName, outfile);    //append at the end

    if(outfile.fail()){
        cout<<"couldn't open input file....."<<endl;
        exit(0);
    }
    cout<<"equation : "<<equation<<endl;
    equation += "\n";

    outfile<<equation;

    outfile.close();
}
void Save(char fileName[]){ // Save can't be in draw
    ofstream outfile;

    outfile.open(fileName);    //append at the end
//    outfile.open(fileName, outfile);    //append at the end

    if(outfile.fail()){
        cout<<"couldn't open input file....."<<endl;
        exit(0);
    }
    outfile.close();
}

//void Load(char fileName[], Sidebar &sidebar, bool del){
//    ifstream infile;
//    infile.open(fileName);
//    if(infile.fail()){
//        cout<<"could not open file...."<<endl;
//        exit(0);
//    }
//    int count = 0;
//    for(int i = 0; i<10; i++){
//        if(!infile.eof()){
//            getline(infile, sidebar[i]);
////            infile>>sidebar[i];
//            count++;
//        }
//    }
//    if(del == true){
//        for(int i = 0; i<10; i++){
//        sidebar[i] = " ";
//        cout<<" sidebar["<<i<<"]"<<sidebar[i]<<endl;

//        }
//    }
//    infile.close();
//}

void BuildQueue(Queue<token *> &queue){
    queue.EnQ(new number(3));
    queue.EnQ(new op("*"));
    queue.EnQ(new variable("x"));
    queue.EnQ(new op("^"));
    queue.EnQ(new number(2));
    queue.EnQ(new op("+"));
    queue.EnQ(new number(2));

//    queue.EnQ(new op("s"));
//    queue.EnQ(new op("("));
//    queue.EnQ(new number(3.14));
//    queue.EnQ(new op("-"));
//    queue.EnQ(new number(3.14));
//    queue.EnQ(new op(")"));
//    queue.EnQ(new op("+"));
//    queue.EnQ(new number(3));
//    queue.EnQ(new op("*"));
//    queue.EnQ(new number(2));
//    queue.EnQ(new op("^"));
//    queue.EnQ(new number(5));

//    queue.EnQ(new op(")"));
//    queue.EnQ(new op("*"));
//    queue.EnQ(new number(2));



//    queue.EnQ(new op("t"));
//    queue.EnQ(new variable("x"));
//    queue.EnQ(new op("("));
//    queue.EnQ(new number(3.14));
//    queue.EnQ(new op("+"));
//    queue.EnQ(new number(2));
//    queue.EnQ(new op(")"));
//    queue.EnQ(new op("*"));
//    queue.EnQ(new number(2));

//    queue.EnQ(new number(2));
//    queue.EnQ(new op("*"));
//    queue.EnQ(new op("s"));
//    queue.EnQ(new op("("));
//    queue.EnQ(new number(3.14));
//    queue.EnQ(new op("+"));
//    queue.EnQ(new number(2));
//    queue.EnQ(new op(")"));


//    queue.EnQ(new number(2));
//    queue.EnQ(new op("+"));
//    queue.EnQ(new op("s"));
//    queue.EnQ(new op("("));
//    queue.EnQ(new number(3.14));
//    queue.EnQ(new op(")"));

}


void func::setUpGraph(string s, Sidebar& sidebar){
    Queue<token*> queue;
    string temp = s.substr(4);
    string equation = "";
    string str;   // first char
    string o;   // another char
    string r;   // result string
    bool done = false;
    double num = 0; //the number
    stringstream ss_str;    //string stream for string
    stringstream ss_num;    //string stream for number
    stringstream ss;        //regular string stream
    int i = 0;
    int end = temp.size();
    str = temp[i];
    i++;
    int space = 0;
    equation = equation + str;
    while(!done){
        o = temp[i];
        if(o != " " ){
            equation = equation + o;
        }
        if(o == " "){
            space++;
            ss<<str;
            ss>>num;
            if(!ss.fail()){
                ss_num<<str;
                ss_num>>num;
                ss_num.str("");
                ss_num.clear();
                queue.EnQ(new number(num));

            }
            else{
                ss_str<<str;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else if(r == "e")
                    queue.EnQ(new number(E));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            str = " ";
        }
        if(i >= end ){
            ss<<str;
            ss>>num;
            if(!ss.fail()){
                ss_num<<str;
                ss_num>>num;
                queue.EnQ(new number(num));
                ss_num.str("");
                ss_num.clear();

            }
            else{
                ss_str<<str;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            str = " ";
            done = true;            //stop everything when "return" found
         }
        str = str + o;  //concantenate
        i++;
    }
    
    sidebar.Save("side.txt", false, temp);
    cout<<"queue: "<<queue<<endl;
//    this->queue = queue;
    result.clear();
    ShuntingYard(queue, result);
    cout<<result<<endl;
//    myqueue(queue);
    
}


void func::myqueue(Queue<token*> temp){
//    Queue<token*> end;
    result.clear();
//    queue = temp;
    ShuntingYard(temp, result);
    cout<<"temp: "<<temp<<endl;
    cout<<"result: "<<result<<endl;
//    result = end;
    
//    return result;
}
string & func::myequation(){
    return equation;
}
string func::equa(){
    return equation;
}
