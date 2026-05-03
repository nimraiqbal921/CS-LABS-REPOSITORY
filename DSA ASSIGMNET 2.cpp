#include <iostream>
#include <string>
using namespace std;

class ItemType {
private:
    char value;

    bool isOperand(char c) {
        return ( (c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z') ||(c >= '0' && c <= '9') );
    }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    bool isParenthesis(char c) {
        return (c == '(' || c == ')');
    }

public:
    bool SetValue(char c) {
        if (isOperand(c) || isOperator(c) || isParenthesis(c)) {
            value = c;
            return true;
        }
        return false;
    }

    char GetValue() const { return value; }
    bool IsOperand() { return isOperand(value); }
    bool IsOperator() { return isOperator(value); }
    bool IsParenthesis() { return isParenthesis(value); }

    int GetPrecedence() {
        if (value == '^') return 3;
        if (value == '*' || value == '/') return 2;
        if (value == '+' || value == '-') return 1;
        return -1;
    }
};

class StackType {
private:
    int top;
    ItemType items[100];
public:
public:
    StackType();             
    bool IsEmpty() const;
    bool IsFull() const;
    void Push(ItemType item); 
    void Pop();
    ItemType Top() const;     
};

StackType::StackType() {
    top = -1;
}

bool StackType::IsEmpty() const {
    return (top == -1);
}

bool StackType::IsFull() const {
    return (top == 99);
}
void StackType::Push(ItemType newItem) {
    if (IsFull())
        throw "FullStack";
    top++;
    items[top] = newItem;
}

void StackType::Pop() {
    if (IsEmpty())
        throw "EmptyStack";
    top--;
}

ItemType StackType::Top() const {
    if (IsEmpty())
        throw "EmptyStack";
    return items[top];
}

string infixToPostfix(string s) {
    StackType st;
    string p = "";

    for(int i = 0; i < s.length(); i++){
        ItemType t; 
        t.SetValue(s[i]);   

        if(t.IsOperand()) {
            p += s[i];      
        }
        else if(s[i] == '(') {
            st.Push(t);     
        }
        else if(s[i] == ')') {
            while(st.Top().GetValue() != '(') {
                p += st.Top().GetValue();
                st.Pop();
            }
            st.Pop();       
        }
        else if(t.IsOperator()) {
            while(!st.IsEmpty() && st.Top().IsOperator() && st.Top().GetPrecedence() >= t.GetPrecedence()) {
                p += st.Top().GetValue();
                st.Pop();
            }
            st.Push(t);     
        }
    }

    while(!st.IsEmpty()) {
        p += st.Top().GetValue();
        st.Pop();
    }

    return p;
}


string infixToPrefix(string s) {
    for(int i = 0, j = s.length()-1; i < j; i++, j--) swap(s[i], s[j]);
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '(') s[i] = ')';
        else if(s[i] == ')') s[i] = '(';
    }

    string post = infixToPostfix(s);   

    for(int i = 0, j = post.length()-1; i < j; i++, j--) swap(post[i], post[j]);

    return post;
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    return 0;
}

