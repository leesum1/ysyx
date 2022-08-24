#ifndef __MYSDB_H
#define __MYSDB_H

#include <iostream>
#include <vector>
#include <string>

extern unsigned cmd_help(const std::vector<std::string>&);
extern unsigned cmd_x(const std::vector<std::string>& input);
extern unsigned cmd_si(const std::vector<std::string>& input);
extern unsigned cmd_c(const std::vector<std::string>& input);
extern unsigned cmd_info(const std::vector<std::string>& input);
extern unsigned cmd_p(const std::vector<std::string>& input);
extern unsigned cmd_w(const std::vector<std::string>& input);
extern unsigned cmd_d(const std::vector<std::string>& input);
extern unsigned cmd_sdb(const std::vector<std::string>& input);


#endif