#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;



class Ticket {
public:
	Ticket(string start, string end) : mStart(start), mEnd(end) {}
	string mStart, mEnd;
	string toString() { return mStart + ", " + mEnd; }
};

//bool operator< (const Ticket& a, const Ticket& b) {
//	return a.mStart < b.mStart;
//}


string findStartCity(vector<Ticket> pList) {
	string s = "";

	// Set with an explicit comparator
	auto comp = [](const string& a, const string& b) { return a < b; };
	set<string, decltype(comp)> aSet(comp);

	for (const Ticket& t : pList) {
		aSet.insert(t.mStart);
	}
	for (const Ticket& t : pList) {
		aSet.erase(t.mEnd);
	}
	if (aSet.size() == 1) {
		s = *aSet.begin();
	}
	return s;
}

string findStartCity(map<string, Ticket> pMap) {
	string s = "";

	set<string> aSet;

	for (const auto& pair : pMap) { // Add start cities
		aSet.insert(pair.second.mStart);
	}
	for (const auto& pair : pMap) { // Remove end cities
		aSet.erase(pair.second.mEnd);
	}
	if (aSet.size() == 1) {
		s = *aSet.begin();
	}
	return s;
}

int main() {
	cout << "Plane Tickets ..." << endl << endl;
	string start = "";

	// Using a list
	vector<Ticket> list;
	list.push_back(Ticket("Denver", "Chicago"));
	list.push_back(Ticket("Vegas", "Denver"));
	list.push_back(Ticket("Chicago", "DC"));
	list.push_back(Ticket("San Fran", "Vegas"));

	for (auto& e : list) {
		cout << e.toString() << endl;
	}
	start = findStartCity(list);
	cout << "startCity=" << start << endl << endl;


	// Using a map
	map<string, Ticket> aMap;
	aMap.insert(make_pair<string, Ticket>("Denver", {"Denver", "Chicago"}));
	aMap.insert(make_pair<string, Ticket>("Vegas", {"Vegas", "Denver"}));
	aMap.insert(make_pair<string, Ticket>("Chicago", {"Chicago", "DC"}));
	aMap.insert(make_pair<string, Ticket>("San Fran", {"San Fran", "Vegas"}));

	for (auto& m : aMap) {
		cout << m.second.toString() << endl;
	}
	start = findStartCity(aMap);
	cout << "startCity=" << start << endl << endl;

	vector<Ticket> tickets;
	while (aMap.size() > 0) {
//		auto pair = aMap.find(start);
//		aMap.erase(start);
//		tickets.push_back(pair->second);
//		start = pair->second.mEnd;

		Ticket t = aMap.at(start);
		aMap.erase(start);
		tickets.push_back(t);
		start = t.mEnd;
	}

	for (auto& t : tickets) {
		cout << t.toString() << endl;
	}

	return 0;
}
