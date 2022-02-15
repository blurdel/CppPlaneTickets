#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>


class Ticket {
public:
	Ticket(std::string pStart, std::string pEnd) : mStart(pStart), mEnd(pEnd) {}
	std::string mStart, mEnd;
	std::string toString() { return mStart + ", " + mEnd; }
};

//bool operator< (const Ticket& a, const Ticket& b) {
//	return a.mStart < b.mStart;
//}


std::string findStartCity(std::vector<Ticket> pList) {
	std::string start = "ERROR";

	// Set with an explicit comparator
	auto comp = [](const std::string& a, const std::string& b) { return a < b; };
	std::set<std::string, decltype(comp)> aSet(comp);

	for (const Ticket& t : pList) {
		aSet.insert(t.mStart); // Add start cities
	}
	for (const Ticket& t : pList) {
		aSet.erase(t.mEnd); // Remove end cities
	}
	if (aSet.size() == 1) {
		start = *aSet.begin();
	}
	return start;
}

std::string findStartCity(std::map<std::string, Ticket> pMap) {
	std::string start = "ERROR";
	std::set<std::string> aSet;

	for (const auto& pair : pMap) {
		aSet.insert(pair.second.mStart); // Add start cities
	}
	for (const auto& pair : pMap) {
		aSet.erase(pair.second.mEnd); // Remove end cities
	}
	if (aSet.size() == 1) {
		start = *aSet.begin();
	}
	return start;
}

int main()
{
	std::string start = "";

//	std::vector<Ticket> aList = {
//		{"Denver", "Chicago"}, {"Vegas", "Denver"}, {"Chicago", "DC"}, {"San Fran", "Vegas"}
//	};

	// Using a list
	std::vector<Ticket> list;
	list.push_back( {"Denver", "Chicago"} );
	list.push_back( {"DC", "NYC"} );
	list.push_back( {"Vegas", "Denver"} );
	list.push_back( {"Chicago", "DC"} );
	list.push_back( {"San Fran", "Vegas"} );

	for (auto& tic : list) {
		std::cout << tic.toString() << std::endl;
	}
	start = findStartCity(list);
	std::cout << "#list: startCity=" << start << std::endl << std::endl;



	std::map<std::string, Ticket> aMap = {
			{ "Denver", {"Denver", "Chicago"}   },
			{ "DC", {"DC", "NYC"}               },
			{ "Vegas", {"Vegas", "Denver"}      },
			{ "Chicago", {"Chicago", "DC"}      },
			{ "San Fran", {"San Fran", "Vegas"} }
	};

	// Using a map
//	auto comp = [](const string& a, const string& b){ return a < b; };
//	std::map<std::string, Ticket> aMap;
//	aMap.insert( std::make_pair<std::string, Ticket>("Denver", {"Denver", "Chicago"})   );
//	aMap.insert( std::make_pair<std::string, Ticket>("DC", {"DC", "NYC"})               );
//	aMap.insert( std::make_pair<std::string, Ticket>("Vegas", {"Vegas", "Denver"})      );
//	aMap.insert( std::make_pair<std::string, Ticket>("Chicago", {"Chicago", "DC"})      );
//	aMap.insert( std::make_pair<std::string, Ticket>("San Fran", {"San Fran", "Vegas"}) );

	for (auto& pair : aMap) {
		std::cout << pair.second.toString() << std::endl;
	}
	start = findStartCity(aMap);
	std::cout << "#map: startCity=" << start << std::endl << std::endl;


	// Put tickets in order
	std::vector<Ticket> tickets;
	while (aMap.size() > 0) {
		Ticket t = aMap.at(start);
		aMap.erase(start);
		tickets.push_back(t);
		start = t.mEnd;
	}

	// Print proper order
	std::cout << "#Correct order" << std::endl;
	for (auto& t : tickets) {
		std::cout << t.toString() << std::endl;
	}

	return 0;
}
