#include "Repository.h"

void Repository::read_from_file()
{
	elems.clear();
	ifstream in(file_name);
	if (!in.is_open())
	{
		ofstream first_run(file_name);
		if (!first_run.is_open()) throw exception("Fisierul nu a putut fi deschis pentru citire !\n");
		first_run.close();
		in.clear();
		in.open(file_name);
	}

	while (!in.eof())
	{
		string line;
		getline(in, line);
		if (line.size() == 0)
			break;

		stringstream ss(line);
		string word;
		vector<string>words;
		while (getline(ss, word, ';'))
			words.push_back(word);

		if (words.size() <= 3) break;

		int id = stoi(words[0]);
		string descriere = words[1];
		vector<string>programatori;
		for (int i = 2; i < words.size() - 1; i++)
			programatori.push_back(words[i]);
		string stare = words[words.size() - 1];

		Task t{ id, descriere, programatori, stare };
		add(t);
	}
	in.close();
}

void Repository::write_to_file()
{
	ofstream out(file_name);
	if (!out.is_open()) throw exception("Fisierul nu a putut fi deschis pentru scriere !\n");
	for (const auto& t : elems)
	{
		out << t.get_id() << ";";
		out << t.get_descriere() << ";";
		for (const auto& pr : t.get_programatori())
			out << pr << ";";
		out << t.get_stare() << "\n";
	}
	out.close();
}

void Repository::add(const Task& t)
{
	for (const auto& el : elems)
		if (el.get_id() == t.get_id())
			throw exception("ID deja existent !\n");
	elems.push_back(t);
	write_to_file();
}

void Repository::modif(int id, string stare)
{
	for(auto& el : elems)
		if (el.get_id() == id)
		{
			el.set_stare(stare);
			write_to_file();
			return;
		}
	throw exception("ID inexistent !\n");
}

const Task& Repository::cauta(const int id)
{
	for (const auto& el : elems)
		if (el.get_id() == id)
			return el;
	throw exception("Task inexistent !\n");
}

vector<Task>& Repository::get_all()
{
	return elems;
}
