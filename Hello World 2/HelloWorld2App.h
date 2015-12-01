////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\HelloWorld2App.h
//! \brief Defines the application 
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <wtl/WTL.hpp>                          //!< Windows Template Library
#include <wtl/modules/Application.hpp>          //!< wtl::Application
#include <wtl/windows/skins/ThemedSkin.hpp>     //!< wtl::ThemedSkin
#include "MainWindow.h"                         //!< hw1::Mainwindow

///////////////////////////////////////////////////////////////////////////////
//! \namespace hw2 - Hello World v2 (Controls demonstration)
///////////////////////////////////////////////////////////////////////////////
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
  
    // ----------------------------------- REPRESENTATION -----------------------------------
    
    // ------------------------------------ CONSTRUCTION ------------------------------------
    
    ///////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::HelloWorld2App
    //! Create the application
    //!
    //! \param[in] app - Application instance
    ///////////////////////////////////////////////////////////////////////////////
    HelloWorld2App(::HINSTANCE app) : base(app)
    {
      // Register custom window classes
      MainWindow<encoding>::registerClass(app);

      // Set default skin
      wtl::ThemedSkin<encoding>::get();
    }
    
    // -------------------------------- COPY, MOVE & DESTROY --------------------------------
    
    // ---------------------------------- ACCESSOR METHODS ----------------------------------
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::name const 
    //! Get the application name
    //!
    //! \return String<encoding> - Full application name
    /////////////////////////////////////////////////////////////////////////////////////////
    wtl::String<encoding> name() const override
    {
      return "Hello World 2";
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorld2App::version const 
    //! Get the application version
    //!
    //! \return String<encoding> - Version string
    /////////////////////////////////////////////////////////////////////////////////////////
    wtl::String<encoding> version() const override 
    {
      return "v1.00";
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

