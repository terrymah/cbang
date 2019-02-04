/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

                Copyright (c) 2003-2019, Cauldron Development LLC
                   Copyright (c) 2003-2017, Stanford University
                               All rights reserved.

         The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
       as published by the Free Software Foundation, either version 2.1 of
               the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
          but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
                 Lesser General Public License for more details.

         You should have received a copy of the GNU Lesser General Public
                 License along with the C! library.  If not, see
                         <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
           You may request written permission by emailing the authors.

                  For information regarding this software email:
                                 Joseph Coffland
                          joseph@cauldrondevelopment.com

\******************************************************************************/

#ifndef CBANG_ENUM
#ifndef CBANG_GPUTYPE_H
#define CBANG_GPUTYPE_H

#define CBANG_ENUM_NAME GPUType
#define CBANG_ENUM_PATH cbang/gpu
#define CBANG_ENUM_NAMESPACE cb
#define CBANG_ENUM_PREFIX 4

#include <cbang/enum/MakeEnumeration.def>

#endif // CBANG_GPUTYPE_H
#else // CBANG_ENUM

CBANG_ENUM_VALUE(GPU_NONE, 0)
CBANG_ENUM_ALIAS(GPU_UNKNOWN, GPU_NONE)
CBANG_ENUM_VALUE(GPU_AMD,     1)
CBANG_ENUM_ALIAS(GPU_ATI,     GPU_AMD)
CBANG_ENUM_VALUE(GPU_NVIDIA,  2)
CBANG_ENUM_VALUE(GPU_INTEL,   3)

#endif // CBANG_ENUM
