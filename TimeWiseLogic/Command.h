#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Constants.h"
/* @author Tran Hue Mai
 *=======================
 
 Command Add
 
 *=======================
 */

class Command
{
private:
	CMD_TYPE _type;
	string _description;
public:
	CMD_TYPE setType(CMD_TYPE);
	string setDescription(string);
}
#endif