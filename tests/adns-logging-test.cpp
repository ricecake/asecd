/*
 * Copyright (c) 2010 Peter Simons <simons@cryp.to>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <adns.h>
#include <sstream>
#include <vector>
#include <cassert>
#include <iostream>

void log(adns_state ads, void * ctx, char const * fmt, va_list args)
{
  static std::ostringstream os;
  static std::vector<char>  buf(1024u);
  int rc;
  for(;;)
  {
    rc = vsnprintf(&buf[0], buf.size(), fmt, args);
    assert(rc >= 0);
    if (static_cast<size_t>(rc) < buf.size()) break;
    buf.resize(rc + 1);
  }
  os.write(&buf[0], rc);
  assert(rc > 0);
  if (buf[rc - 1] == '\n')
  {
    std::cout << "*** " << os.str();
    os.str("");
  }
}

int main(int, char**)
{
  using namespace std;
  adns_state st;
  //int const rc( adns_init_logfn(&st, adns_if_debug, NULL, &log, NULL) );
  int const rc( adns_init(&st, adns_if_noerrprint, 0 ) );
  if (rc != 0)
    cerr << "cannot initialize adns" << endl;

   const char *domain = "sutt.buttmuffin.org";

   adns_answer *qid;
   int r = adns_synchronous(st, domain,
                  adns_r_txt,
                  adns_qf_none,
		  &qid);

   if (!r) {
	for (int i = 0; i < qid->nrrs; i++)    
		//std::cout<<qid->status << std::endl << qid->type << std::endl << std::hex << qid->rrs.inaddr[i].s_addr << std::endl;
		std::cout<<qid->status << std::endl << qid->type << std::endl << qid->rrs.manyistr[i]->str << std::endl;
   }
  adns_finish(st);
  return 0;
}
