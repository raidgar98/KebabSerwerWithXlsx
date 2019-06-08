#include "sqlinterpreter.h"

#include <list>

void SQLInterpreter::__mCompileFunction(const char separator, std::list<QString>& paramList, QString& query, const std::string & buff) const noexcept
{
	//Starting new line so make it to defaults
	QString temp = "";
	paramList.clear();

	//Detecting all params
	for(quint32 i = 0; i < buff.length(); i++)
	{
		if(buff[i] == separator)
		{
			//cout << this << "compile() -> Detected: " << temp;
			//1temp.replace(" ", "");
			paramList.push_back(temp);
			temp = "";

		}else if(buff[i] == '\n' || buff[i] == '\r') continue; else temp+=buff[i];
	}

	//Replacing single params and creating allParams
	QString allParams = "";
	quint8 i = 1;
	for(auto var = paramList.begin();var != paramList.end(); var++)
	{
		//Replacing params

		temp = "::";
		if(i > 9) temp += "x";
		temp += QString::number(i);

		query.replace(temp, *var);
		cout << "QUERRY "<<temp<<" "<< *var<<" : "<<query;

		//Generating allParams
		allParams += "'" +  (*var) +"'";
		if(i != __mSymbols.size()) allParams+= ", ";

		i++;
	}

	//Replacing 'paste all paramas'
	query.replace("::0", allParams);

	//cout <<this << "compile() query: "<<query;
}

SQLInterpreter::~SQLInterpreter()
{
	__mSymbols.clear();
	__mSrc = nullptr;
}

void SQLInterpreter::operator delete(void * src)
{
	//Have to be sure
	auto* var = static_cast<SQLInterpreter*>(src);
	var->~SQLInterpreter();
	free(src);
}

SQLInterpreter::SQLInterpreter(const QString& iInput, QString iSrc, QObject * parent) noexcept
	:__mInputPath{iInput}, __mSrc{iSrc}, QObject{parent}
{
	//cout << this << " Created!";

	std::ifstream * input = new std::ifstream{iInput.toStdString()};

	if(!input->good())
	{
		//cout <<this << " Cannot open: " << iInput;
		input->close();
		delete input;
		return;
	}

	//Gathering info from first row
	std::string linia;
	std::getline(*input, linia);
	input->close();
	QString temp = "";

	//Choose separator recomended semicolon, because yes
	const char separator = linia[0];

	//Creating index od shorts and column names
	for(quint32 i = 1; i < linia.length(); i++)
	{
		if(linia[i] != separator)
			temp += linia[i];
		else
		{
			//cout << this << "Adding following column: " << temp;

			QString k1 = "::";
			if(__mSymbols.size()+1 > 9) k1 += "x";
			k1+=QString::number(__mSymbols.size()+1);

			__mSymbols[k1] = temp;
			temp = "";
		}
	}

	//cout << this << "Finished adding. Emitting...";

	//Write on screen when ready avaiable shorts
	isOk = true;
}

bool SQLInterpreter::save()
{
	//Open locations
	std::list<QString> paramList;

	//Trying to opopen source file
	std::ifstream input(__mInputPath.toStdString());
	if(!input.good()) { input.close(); return false; }

	//std::getline result
	std::string buff;

	//getting defaults
	QString patternSQL = __mSrc;
	QString query;

	//cout << this << " PatterSQL: "<<patternSQL;

	//First line is config so let's get a separator
	std::getline(input, buff);
	const char separator = buff[0];

	//Reading line by line
	while (std::getline(input, buff))
	{
		//Skip bad lines
		if(buff == "" || buff == "\n" || buff == " " || buff == "\r") continue;

		//it would be very *plum* NOIZZ if somebody writ it at the bottom of txt :)
		if(buff[0] == '!' && buff[1] == 'E' && buff[2] == 'N' && buff[3] == 'D')
		{
			break;
		};

		//Forgotten separator correction
		if(buff[buff.size()-1] != separator) buff+=separator;

		query = patternSQL;

		//Processing input
		__mCompileFunction(separator, paramList, query, buff);

		//Save it
		emit saveSQL(query);
	}

	//Closing stuff
	input.close();
	//output.close();

	return true;

}

QString SQLInterpreter::__mExampleFunction()
{
	//cout << this << "Starting example";
	//Open locations
	std::list<QString> paramList;

	//Trying to opopen source file
	std::ifstream input(__mInputPath.toStdString());
	if(!input.good()) { input.close(); return QString(); }

	std::string buff;

	//getting defaults
	QString query = __mSrc;


	//cout << this << " PatterSQL: "<<query;

	//First line is config so let's get a separator
	std::getline(input, buff);
	const char separator = buff[0];

	//Searching for nice, one, little line
	while (std::getline(input, buff))
	{
		//cout << this << "std::getline(input, buff) -> result: "<<QString(buff.c_str());
		if(buff == "" || buff == "\n" || buff == " " || buff == "\r") continue;		//Skip bad lines
		else
			if(buff[0] == '!' && buff[1] == 'E' && buff[2] == 'N' && buff[3] == 'D') return QString();		//it would be very *plum* NOIZZ if somebody writ it at the bottom of txt :)
			else break;		//If line is not empty break;

	}

	//Forgotten separator correction
	if(buff[buff.size()-1] != separator) buff+=separator;

	//Processing input
	__mCompileFunction(separator, paramList, query, buff);

	//Closing stuff
	input.close();

	//Save it
	return query;

}

size_t SQLInterpreter::__mAmountOfColumnsFunction() const
{
	return __mSymbols.size();
}

QString SQLInterpreter::operator[](const QString src) const
{
	return __mSymbols[src];
}
