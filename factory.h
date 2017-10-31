#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <mutex>



//TODO：可以改为抽象工厂
/*按照要求产生线上和线下人物属性*/

class BaseService;
class Person;
struct Location;

enum class PersonType {
	OFFLINE = 1,
	ONLINE_INFECT = 2,
	ONLINE_UNINFECT = 3
};

class BaseFactory {
public:
	BaseFactory() = default;
	std::shared_ptr<Person> randomGenerateOnePerson(PersonType ptype , int stunum);
	Location randomGenerateLocation();
	virtual std::shared_ptr<BaseService> accquireService() = 0;
};


class PersonFactory : public BaseFactory
{
 private:
	std::vector<std::shared_ptr<Person>> m_vecOnlinePersons;
	std::vector<std::shared_ptr<Person>> m_vecOfflinePersons;
	int m_onlineCounts;
	int m_offlineCounts;

 private:
	 void setOnLineCounts(int);
	 void setOfflineCounts(int);
	 std::vector<std::shared_ptr<Person>> getOnlinePersons();
	 std::vector<std::shared_ptr<Person>> getOfflinePersons();
	 void randomGeneratePerson();

 public:
	 PersonFactory() {
		 m_vecOnlinePersons.clear();
		 m_vecOnlinePersons.shrink_to_fit();
		 m_vecOfflinePersons.clear();
		 m_vecOfflinePersons.shrink_to_fit();
	 }

	 std::shared_ptr<BaseService> accquireService() override;

};

class OnlinePersonFactory : public BaseFactory {
private:
	std::vector<std::shared_ptr<Person>> m_infectPerson;
	std::vector<std::shared_ptr<Person>> m_uninfectPerson;
	int m_infectCounts;
	int m_uninfectCounts;

private:
	void setInfectCounts(int);
	void setUninfectCounts(int);
	void randomGenerateOnliePerson();
	std::vector<std::shared_ptr<Person>> getInfectPersons();
	std::vector<std::shared_ptr<Person>> getUninfectPersons();

public:
	OnlinePersonFactory() {
		m_infectPerson.clear();
		m_infectPerson.shrink_to_fit();
		m_uninfectPerson.clear();
		m_infectPerson.shrink_to_fit();
	};
	std::shared_ptr<BaseService> accquireService() override;
};
#endif