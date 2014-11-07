// test_resolver.cc
//
#include <vector>
#include <iostream>
using namespace std;

#include <boost/net/dns_resolver.hpp>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>

using namespace boost;
using namespace asio;

int main(int argc, char* argv[])
{
	io_service  ios;

	boost::net::dns::dns_resolver dnsResolver(ios); 
  
	dnsResolver.add_nameserver( ip::address::from_string("64.81.45.2") );
  
	boost::net::dns::rr_list_t linfo;

	cout << to_simple_string(posix_time::second_clock::local_time()) << " sutt.buttmuffin.org:txt" << endl;
	linfo = dnsResolver.resolve("sutt.buttmuffin.org.", net::dns::type_txt);
	cout << linfo.size() << endl;
	for (net::dns::rr_list_t::iterator riter = linfo.begin(); riter != linfo.end(); ++riter) {
		net::dns::txt_resource *t = dynamic_cast<net::dns::txt_resource*>(riter->get());
	       cout << t->text() << endl;
	}	       
  
	return 0;
}
