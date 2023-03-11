//Justin Ritchey - program 5 - 12/20/2020 - Program is to mimic a 2 pass assembler.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string findAddr(string, string, int&);
string dec_to_hex(int);
string machineCode(string);
string operand(string);

void main()
{
	ifstream file;
	file.open("input.txt");
	string lines[11];
	string line = "";
	string startAddr = "";
	string addrs[9];
	string symTable[2];
	string machCode[9];
	string ops[9];
	int count = 0;
	int temp = 0;
	int total = 0;
	ofstream out;
	out.open("outfile.txt");

	while (getline(file, line))
	{
		lines[count] = line;
		count++;
	}

	for (int i = 0; i < 11; i++)
	{
		line = lines[i];
		if (line[0] == 'L')
		{
			temp = line.find('$');
			if (symTable[0] == "")
			{
				symTable[0]=line.substr(temp+1, temp + 8);
			}
			else
			{
				symTable[1]=line.substr(temp+1, temp + 8);
			}
		}
	}


	file.clear();
	file.seekg(0, ios::beg);

	cout << "Symbol Table:\n";
	out << "Symbol Table:\n";

	for (int i = 0; i < 2; i++)
	{
		cout << "Loop" << i+1 << " " << symTable[i] << endl;
		out << "Loop" << i + 1 << " " << symTable[i] << endl;
	}

	cout << "\n\n";
	out << "\n\n";

	line = lines[0];
	temp = line.find('$');
	startAddr = line.substr(temp + 1, temp + 8);

	cout << "Address       Machine Code   Operands          Instructions\n";
	out << "Address       Machine Code   Operands          Instructions\n";

	for (int i = 0; i < 9; i++)
	{
		addrs[i] = findAddr(lines[i], startAddr, total);
	}
	for (int i = 0; i < 9; i++)
	{
		machCode[i] = machineCode(lines[i+1]);
	}
	for (int i = 0; i < 9; i++)
	{
		ops[i] = operand(lines[i + 1]);
	}
	for (int i = 0; i < 9; i++)
	{
		cout << addrs[i] << "      ";
		out << addrs[i] << "      ";
		out << machCode[i] << "           ";
		cout << machCode[i] << "           ";
		cout << ops[i];
		out << ops[i];
		temp = machCode[i].size() + addrs[i].size() + ops[i].size();

		while (temp < 30)
		{
			cout << " ";
			out << " ";
			temp++;
		}

		cout << lines[i] << endl;
		out << lines[i] << endl;
	}
	
	system("PAUSE");
}


string findAddr(string s, string start, int &total)
{
	int bytes = 0;
	int temp = 0;
	int temp2 = 0;
	int temp3 = 0;
	string line = "";

	switch (s[0])
	{
	case 'M':
		temp = s.find('#');
		temp2 = s.find('$');
		if (temp > 0 && temp2 >0)
		{
			bytes = 8;
			break;
		}
		else if (temp > 0 && temp2 <= 0)
		{
			bytes = 4;
			break;
		}
		else if (temp <= 0 && temp2 > 0)
		{
			bytes = 6;
			break;
		}
		break;
	case 'T':
		bytes = 2;
		break;
	case 'L':
		temp = s.find("M");
		temp2 = s.find("A");
		if (temp > 0)
		{
			line = s.substr(temp);
			findAddr(line, start, total);
			break;
		}
		if (temp2 > 0)
		{
			line = s.substr(temp2);
			findAddr(line, start, total);
			break;
		}
		break;
	case 'A':
		temp = s.find('I');
		temp2 = s.find('$');
		temp3 = s.find('#');
		if (temp > 0)
		{
			if (temp2 > 0 && temp3 > 0)
			{
				bytes = 8;
				break;
			}
		}
		if (temp <= 0)
		{
			if (temp2 > 0)
			{
				bytes = 6;
				break;
			}
		}
		break;
	}

	total = total + bytes;
	line = dec_to_hex(total);

	start = start.substr(0, 6);
	start = start + line;

	return start;
}

string dec_to_hex(int decimal)                                  //function to convert decmial to hexadecimal
{
	string hex = "";                                               //will hold the result in a string
	int hex_divide = 0;                                            //holds the decimal given by the user to convert   
	int r = 0;

	hex_divide = decimal;

	while (hex.size() < 2)                                         //loop to assign hex values
	{
		if (hex_divide > 16)                                       //if decimal number is over 16, will use the modulo to get remainder
		{
			r = hex_divide % 16;
		}
		else if (hex_divide < 16)                                  //if decimal is under 16 will assign decimal as remainder
		{
			r = hex_divide;
		}

		if (r == 0)                                                //loop to assign value based on the remainder varaiable       
		{
			hex = '0' + hex;
		}
		if (r == 1)
		{
			hex = '1' + hex;
		}
		if (r == 2)
		{
			hex = '2' + hex;
		}
		if (r == 3)
		{
			hex = '3' + hex;
		}
		if (r == 4)
		{
			hex = '4' + hex;
		}
		if (r == 5)
		{
			hex = '5' + hex;
		}
		if (r == 6)
		{
			hex = '6' + hex;
		}
		if (r == 7)
		{
			hex = '7' + hex;
		}
		if (r == 8)
		{
			hex = '8' + hex;
		}
		if (r == 9)
		{
			hex = '9' + hex;
		}
		if (r == 10)
		{
			hex = 'A' + hex;
		}
		if (r == 11)
		{
			hex = 'B' + hex;
		}
		if (r == 12)
		{
			hex = 'C' + hex;
		}
		if (r == 13)
		{
			hex = 'D' + hex;
		}

		if (r == 14)
		{
			hex = 'E' + hex;
		}
		if (r == 15)
		{
			hex = 'F' + hex;
		}

		hex_divide = hex_divide / 16;                //making decimal into the left over for next remainder number         
		r = hex_divide;                              //setting remainder equal to this number
	}
	return hex;
}

string machineCode(string s)
{
	int temp = 0;
	int temp2 = 0;
	int temp3 = 0;
	string line = "";


	switch (s[0])
	{
	case 'M':
		temp = s.find('#');
		temp2 = s.find('$');
		if (temp > 0 && temp2 > 0)
		{
			return "33FC";
		}
		else if (temp > 0 && temp2 <= 0)
		{
			return "303C";
		}
		else if (temp <= 0 && temp2 > 0)
		{
			temp3 = s.find('D');
			if (temp3 > temp2)
			{
				return "3039";
			}
			else
			{
				return "33C0";
			}
		}
		break;
	case 'T':
		temp = s.find('#');
		line = s.substr(temp + 1);
		switch (line[0])
		{
		case '0':
			return "4E40";
		case '1':
			return "4E41";
		case '2':
			return "4E42";
		}
		break;
	case 'L':
		temp = s.find("M");
		temp2 = s.find("A");
		if (temp > 0)
		{
			line = s.substr(temp);
			line = machineCode(line);
			return line;
		}
		if (temp2 > 0)
		{
			line = s.substr(temp2);
			line = machineCode(line);
			return line;
		}
	case 'A':
		temp = s.find('I');
		temp2 = s.find('$');
		temp3 = s.find('#');
		if (temp > 0)
		{
			if (temp2 > 0 && temp3 > 0)
			{
				return "0679";
			}
			else
			{
				return "0640";
			}
		}
		if (temp <= 0)
		{
			temp3 = s.find('D');
			if (temp3 > temp2)
			{
				return "D179";
			}
			else
			{
				return "D079";
			}
			break;
		}
	case 'O':
		return "";
	}
}

string operand(string s)
{
	string line = "";
	int temp=0;
	int temp2=0;
	int temp3=0;

	if (s[0] == 'T')
	{
		return "";
	}
    
	temp = s.find('#');
	if (temp > 0)
	{
		temp2 = s.find(',');
		temp2 = temp2 - temp;
		line = s.substr((temp+1), temp2);
		stringstream ss;
		ss << line;
		ss >> temp3;
		
		line = dec_to_hex(temp3);
		line = "00" + line;
	}

	temp = s.find('$');

	if (temp > 0)
	{
		line = line + s.substr(temp+1, 8);
	}

	return line;
	
}