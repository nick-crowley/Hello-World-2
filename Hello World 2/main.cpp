////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\Main.cpp
//! \brief Entry point for Hello World program
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#include "HelloWorld2App.h"   

////////////////////////////////////////////////////////////////////////////////
// ::_tWinMain
//! Narrow/wide char entry point
//!
//! \param[in] instance - Program instance 
//! \param[in] previous - Legacy
//! \param[in] cmdLine - Command line
//! \param[in] showMode - Desired display mode
////////////////////////////////////////////////////////////////////////////////
int32_t WINAPI _tWinMain(::HINSTANCE instance, ::HINSTANCE previous, PWSTR cmdLine, int32_t showMode)
{
  try
  {
    hw2::application_t program(instance);
  
    // Run program and return result
    return program.run(cmdLine, wtl::enum_cast<wtl::ShowWindowFlags>(showMode));
  }
  catch (std::exception& e)
  {
    wtl::cdebug << wtl::caught_exception("An unhandled exception caused a terminal error", HERE, e);
    return -1;
  }
}


