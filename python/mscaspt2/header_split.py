#!/opt/local/bin/python
import string
import os
import re

def header(n) :
    return "//\n\
// BAGEL - Brilliantly Advanced General Electronic Structure Library\n\
// Filename: MSCASPT2_tasks" + str(n) + ".h\n\
// Copyright (C) 2014 Toru Shiozaki\n\
//\n\
// Author: Toru Shiozaki <shiozaki@northwestern.edu>\n\
// Maintainer: Shiozaki group\n\
//\n\
// This file is part of the BAGEL package.\n\
//\n\
// This program is free software: you can redistribute it and/or modify\n\
// it under the terms of the GNU General Public License as published by\n\
// the Free Software Foundation, either version 3 of the License, or\n\
// (at your option) any later version.\n\
//\n\
// This program is distributed in the hope that it will be useful,\n\
// but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
// GNU General Public License for more details.\n\
//\n\
// You should have received a copy of the GNU General Public License\n\
// along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\
//\n\
\n\
#include <bagel_config.h>\n\
#ifdef COMPILE_SMITH\n\
\n\
#ifndef __SRC_SMITH_MSCASPT2_TASKS" + str(n) + "_H\n\
#define __SRC_SMITH_MSCASPT2_TASKS" + str(n) + "_H\n\
\n\
#include <src/smith/indexrange.h>\n\
#include <src/smith/tensor.h>\n\
#include <src/smith/task.h>\n\
#include <src/smith/subtask.h>\n\
#include <src/smith/storage.h>\n\
\n\
namespace bagel {\n\
namespace SMITH {\n\
namespace MSCASPT2{\n\
\n"

footer = "\n}\n}\n}\n\
#endif\n\
#endif\n\
\n"


header2 = "//\n\
// BAGEL - Brilliantly Advanced General Electronic Structure Library\n\
// Filename: MSCASPT2_tasks.h\n\
// Copyright (C) 2014 Toru Shiozaki\n\
//\n\
// Author: Toru Shiozaki <shiozaki@northwestern.edu>\n\
// Maintainer: Shiozaki group\n\
//\n\
// This file is part of the BAGEL package.\n\
//\n\
// This program is free software: you can redistribute it and/or modify\n\
// it under the terms of the GNU General Public License as published by\n\
// the Free Software Foundation, either version 3 of the License, or\n\
// (at your option) any later version.\n\
//\n\
// This program is distributed in the hope that it will be useful,\n\
// but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
// GNU General Public License for more details.\n\
//\n\
// You should have received a copy of the GNU General Public License\n\
// along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\
//\n\
\n\
#include <bagel_config.h>\n\
#ifdef COMPILE_SMITH\n\
\n\
#ifndef __SRC_SMITH_MSCASPT2_TASKS_H\n\
#define __SRC_SMITH_MSCASPT2_TASKS_H\n\
\n"

footer2 = "\n#endif\n#endif\n\n"

f = open('MSCASPT2_tasks.h', 'r')
lines = f.read().split("\n")[38:][:-6]

tasks = []
tmp = ""

for line in lines:
    if (len(line) >= 10 and line[0:10] == "class Task"):
        if (tmp != ""):
            tasks.append(tmp)
            tmp = ""
    if (line != ""):
        tmp += line + "\n"
        if (len(line) >= 2 and line == "};"):
            tmp += "\n"
tasks.append(tmp)

p = re.compile('[0-9]+')
tmp = ""
num = 0
chunk = 50
n = 1
for task in tasks:
    num = int(p.search(task).group())
    if (num != 0 and num >= n*chunk):
        n = num / chunk
        fout = open("MSCASPT2_tasks" + str(n) + ".h", "w")
        out = header(n) + tmp + footer
        fout.write(out)
        fout.close()
        tmp = ""
        n = n+1
#    num = num+1
    tmp = tmp + task;

n = (num-1) / chunk + 1
fout = open("MSCASPT2_tasks" + str(n) + ".h", "w")
out = header(n) + tmp + footer
fout.write(out)
fout.close()

os.remove("MSCASPT2_tasks.h")
fout = open("MSCASPT2_tasks.h", "w")
out = header2
for i in range(n+1):
    if (i > 0):
        out += "#include <src/smith/caspt2/MSCASPT2_tasks" + str(i) + ".h>\n"
out += footer2
fout.write(out)
fout.close()
