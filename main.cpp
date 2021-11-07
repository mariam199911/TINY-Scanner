#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string Reserved_Words[] = { "if","then","else","end","repeat","until","read","write" };
enum Allstates { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
Allstates current_state = START;

bool is_letter(char s) {
    if(s >= 'A' && s <= 'Z' || s >= 'a' && s <= 'z' )
        return true;
    else
        return false;
     }

bool is_digit(char s) {
    if(s >= '0' && s <= '9')
        return true;
    else
        return false;
    }

bool is_symbol(char s) {
    if(s == '+' || s == '-' || s == '*' || s == '/' || s == '=' || s == '<' || s == '(' || s == ')' || s == ';')
        return true;
    else
        return false;
    }

bool is_space(char s) {
    if(s == '\t' || s == ' ' || s == '\n')
        return true;
    else
        return false;
    }


void getToken(string input_code)
{
	string token;
	bool isReserved = false;
	int i = 0;
	while (current_state != DONE) {
		switch (current_state) {
		case START:
		     if (is_digit(input_code[i])) {
				current_state = INNUM;
			}
			else if (is_space(input_code[i])) {
				i++;
				if (i == input_code.length()) current_state = DONE;
				else current_state = START;
			}
			else if (input_code[i] == ':') {
				current_state = INASSIGN;
			}
			else if (is_letter(input_code[i])) {
				current_state = INID;
			}
			else if (input_code[i] == '{') {
				i++;
				current_state = INCOMMENT;
			}
			else if (is_symbol(input_code[i])) {
				cout <<"Special Symbol"<<" -> "<< input_code[i] << endl;
				i++;
				if (i == input_code.length()) current_state = DONE;
				else current_state = START;
			}
			else current_state = DONE;
			break;

		case INNUM:
			while (is_digit(input_code[i])) {
				token += input_code[i];
				i++;
			}
			cout <<"number"<<" -> " <<token <<endl;
			token = "";
			if (i == input_code.length()) current_state = DONE;
			else current_state = START;
			break;

		case INID:
			while (is_letter(input_code[i])) {
				token += input_code[i];
				i++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (Reserved_Words[i] == token) isReserved = true;
			}
			if (isReserved) cout << "Reserved Word"<<" -> "<< token <<endl;
			else cout << "Identifier"<<" -> "<<token <<endl;
			token = "";
			isReserved = false;
			if (i == input_code.length()) current_state = DONE;
			else current_state = START;
			break;

		case INCOMMENT:
			if (current_state == INCOMMENT) {
				while (input_code[i] != '}') {
					i++;
				}
				i++;
				if (i == input_code.length()) current_state = DONE;
				else current_state = START;
			}
			break;

		case INASSIGN:
			if (input_code[i] == ':') {
				i += 2;
				cout <<"assign"<< " -> "<< ":=" <<endl;
				current_state = START;
			}
			else {
				if (i == input_code.length()) current_state = DONE;
				else current_state = START;
			}
			break;
		case DONE:
			break;
		}
	}
}





int main() {
	ifstream file;
	string line, code;
	file.open("input_code.txt");
	while (!file.eof()) {
		getline(file, line);
		code += line;
	}
	//cout<<code;
	freopen("output_code.txt", "w", stdout);
	getToken(code);
	fclose(stdout);
	system("pause");
	return 0;
}

