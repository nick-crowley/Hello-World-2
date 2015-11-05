////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\HelloWorld2App.h
//! \brief Defines the application 
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

// Target Platform v5.01 (WindowsXP)
//#include <WinSDKVer.h>
#define _WIN32_WINNT    _WIN32_WINNT_WINXP
//#include <SDKDDKVer.h>

#include "wtl/WTL.hpp"                      //!< Windows Template Library
#include "wtl/modules/Application.hpp"      //!< wtl::Application
#include "MainWindow.h"                     //!< hw1::Mainwindow

//! \namespace hw2 - Hello World v2 (Controls demonstration)
namespace hw2
{

  ///////////////////////////////////////////////////////////////////////////////
  //! \struct HelloWorld2App - Encapsulates the 'Hello World' program
  //! 
  //! \tparam ENC - Window charactrer encoding (Default is UTF-16)
  ///////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC = wtl::Encoding::UTF16>
  struct HelloWorld2App : wtl::Application<MainWindow<ENC>>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
    
    //! \alias type - Define own type
    using type = HelloWorld2App<ENC>;
    
    //! \alias base - Define base type
    using base = wtl::Application<MainWindow<ENC>>;
    
    //! \alias char_t - Inherit character type
    using char_t = typename base::char_t;

    //! \var encoding - Define app character encoding
    static constexpr wtl::Encoding  encoding = ENC;
  
    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------

    ///////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::HelloWorld2App
    //! Create application from handle supplied by WinMain(..)
    //!
    //! \param[in] app - Application handle
    ///////////////////////////////////////////////////////////////////////////////
    HelloWorld2App(::HMODULE app) : base(app)
    {
    }

    // ---------------------------------- ACCESSOR METHODS ----------------------------------
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::name const 
    //! Get the application name
    //!
    //! \return const char_t* - Full application name
    /////////////////////////////////////////////////////////////////////////////////////////
    const char_t* name() const override
    {
      return wtl::choose<ENC>("Hello World 2", L"Hello World 2");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::version const 
    //! Get the application version
    //!
    //! \return const char_t* - Version string
    /////////////////////////////////////////////////////////////////////////////////////////
    const char_t* version() const override 
    {
      return wtl::choose<ENC>("v1.00", L"v1.00");
    }

    // ----------------------------------- MUTATOR METHODS ----------------------------------  
  protected:
    ///////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::onStart
    //! Called once upon startup to create the main window
    //! 
    //! \param[in] mode - Initial display mode
    //!
    //! \throw wtl::platform_error - Unable to create window
    ///////////////////////////////////////////////////////////////////////////////
    void onStart(wtl::ShowWindowFlags mode) override
    {
      // Create window
      this->Window.create();
    
      // Show window
      this->Window.show(mode);
      this->Window.update();
    }

    // ----------------------------------- REPRESENTATION -----------------------------------
  };


  //! \alias application_t - Define ANSI/UNICODE application type according to build settings (Size of TCHAR)
  using application_t = HelloWorld2App<wtl::default_encoding_t<::TCHAR>::value>;

} // namespace

#endif

