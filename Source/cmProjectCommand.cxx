/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmProjectCommand.h"

// cmProjectCommand
bool cmProjectCommand::InitialPass(std::vector<std::string> const& args)
{
  if(args.size() < 1 )
    {
    this->SetError("PROJECT called with incorrect number of arguments");
    return false;
    } 
  m_Makefile->SetProjectName(args[0].c_str());

  std::string bindir = args[0];
  bindir += "_BINARY_DIR";
  std::string srcdir = args[0];
  srcdir += "_SOURCE_DIR";
  
  m_Makefile->AddCacheDefinition(bindir.c_str(),
                                 m_Makefile->GetCurrentOutputDirectory(),
                                 "Value Computed by CMake", cmCacheManager::STATIC);
  m_Makefile->AddCacheDefinition(srcdir.c_str(),
                                 m_Makefile->GetCurrentDirectory(),
                                 "Value Computed by CMake", cmCacheManager::STATIC);
  
  bindir = "PROJECT_BINARY_DIR";
  srcdir = "PROJECT_SOURCE_DIR";

  m_Makefile->AddDefinition(bindir.c_str(),
          m_Makefile->GetCurrentOutputDirectory());
  m_Makefile->AddDefinition(srcdir.c_str(),
          m_Makefile->GetCurrentDirectory());

  m_Makefile->AddDefinition("PROJECT_NAME", args[0].c_str());

  // Set the CMAKE_PROJECT_NAME variable to be the highest-level
  // project name in the tree.  This is always the first PROJECT
  // command encountered.
  if(!m_Makefile->GetDefinition("CMAKE_PROJECT_NAME"))
    {
    m_Makefile->AddDefinition("CMAKE_PROJECT_NAME", args[0].c_str());
    }

  std::vector<std::string> languages;
  if(args.size() > 1)
    {
    for(size_t i =1; i < args.size(); ++i)
      {
      languages.push_back(args[i]);
      }
    }
  else
    {
    // if no language is specified do c and c++
    languages.push_back("C");
    languages.push_back("CXX");
    }
  m_Makefile->EnableLanguage(languages);
  return true;
}

