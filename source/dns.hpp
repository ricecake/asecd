#ifndef __DNS_HPP__
#define __DNS_HPP__

#include <common.hpp>
#include <adns.h>

class asDNS {
	public:
		asDNS() {
			if (adns_init(&state, adns_if_noerrprint, 0)) {
				throw DnsInit;
			}
		}
		~asDNS() {
			adns_finish(state);
		}
		std::vector<std::string> queryTXT(std::string domain) {
			adns_answer* query;
			int fail = adns_synchronous(state, domain.c_str(), adns_r_txt, adns_qf_none, &query);
			if (fail) {
				throw DnsQueryFail;
			}
			std::vector<std::string> result;
			for (int i = 0; i < query->nrrs; i++) {
				std::string record(query->rrs.manyistr[i]->str);
				result.push_back(record);
			}
			return result;
		}
		std::vector<unsigned long> queryA(std::string domain) {
			adns_answer* query;
			int fail = adns_synchronous(state, domain.c_str(), adns_r_a, adns_qf_none, &query);
			if (fail) {
				throw DnsQueryFail;
			}
			std::vector<unsigned long> result;
			for (int i = 0; i < query->nrrs; i++) {
				unsigned long record = (unsigned long) query->rrs.inaddr[i].s_addr;
				result.push_back(record);
			}
			return result;
		}
	protected:
	private:
		adns_state state;
};

#endif

