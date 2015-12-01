////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\MainWindow.h
//! \brief Defines the main window class
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HW2_EXIT_BUTTON_H
#define HW2_EXIT_BUTTON_H

#include <wtl/WTL.hpp>                                          //!< Windows Template Library
#include <wtl/windows/controls/Button.hpp>                      //!< wtl::Button
#include <wtl/windows/commands/ExitProgramCommand.hpp>          //!< wtl::ExitProgramCommand

/////////////////////////////////////////////////////////////////////////////////////////
//! \namespace hw2 - Hello World v2 (Controls demonstration)
/////////////////////////////////////////////////////////////////////////////////////////
namespace hw2
{
  /////////////////////////////////////////////////////////////////////////////////////////
  //! \struct ExitButton - Example of a button control customized as a separate class rather than a field of the main window
  /////////////////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC>
  struct ExitButton : wtl::Button<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias type - Define own type
    using type = ExitButton;

    //! \alias base - Define base type
    using base = wtl::Button<ENC>;
      
    //! \var encoding - Inherit window character encoding
    static constexpr wtl::Encoding  encoding = base::encoding;
  
    // ----------------------------------- REPRESENTATION -----------------------------------
      
    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // ExitButton::ExitButton
    //! Creates a standard button control
    //! 
    //! \param[in] id - Control ID
    /////////////////////////////////////////////////////////////////////////////////////////
    ExitButton(wtl::WindowId id) : base(id)
    {
      // Initialize window properties
      this->Icon      = wtl::icon_resource<encoding>(wtl::CommandId::App_Exit).Handle;
      this->Position  = wtl::PointL(480,350);
      this->Style    |= wtl::WindowStyle::Visible;
      this->Size      = wtl::SizeL(120,50);
      this->Text      = "Exit Program";
        
      // Register for events
      this->Click += new wtl::ButtonClickEventHandler<encoding>(this, &ExitButton::onClick);
    }
      
    // ----------------------------------- STATIC METHODS -----------------------------------

    // ---------------------------------- ACCESSOR METHODS ----------------------------------

    // ----------------------------------- MUTATOR METHODS ----------------------------------
  private:
    ///////////////////////////////////////////////////////////////////////////////
    // ExitButton::onClick
    //! Exits the program
    //! 
    //! \param[in] args - Message arguments
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onClick(wtl::ButtonClickEventArgs<encoding> args) 
    { 
      // Execute the 'Exit Program' gui command
      this->execute(wtl::CommandId::App_Exit);
    
      // Handled
      return {wtl::MsgRoute::Handled, 0};
    }
  };

} // namespace

#endif

