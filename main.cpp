#include "bridge.h"
#include "factory.h"

int main() {

	PersonFactory pf;
	for(int i=0;i<20;i++)
	std::cout << pf.generateIntRandom(0,1) << std::endl;
#endif
	/*PersonFactory pf;
	pf.randomGeneratePerson();*/
	std::shared_ptr<Bridge> pOOb(new OnlineAndOfflineBridge());
	std::shared_ptr<BaseFactory> pBs(new PersonFactory());
	pOOb->setFactory(pBs);

	std::shared_ptr<Bridge> pOb(new OnlineBridge());
	std::shared_ptr<BaseFactory> pOs(new OnlinePersonFactory());
	pOb->setFactory(pOs);

	Runner r;
	r.addBridge(pOOb);
	r.addBridge(pOb);

	r.run();
	return 0;
}