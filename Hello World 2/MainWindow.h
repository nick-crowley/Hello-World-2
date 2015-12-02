////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\MainWindow.h
//! \brief Defines the main window class
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HW2_MAIN_WINDOW_H
#define HW2_MAIN_WINDOW_H

#include <wtl/WTL.hpp>                                          //!< Windows Template Library
#include <wtl/utils/Random.hpp>                                 //!< wtl::Random
#include <wtl/windows/Window.hpp>                               //!< wtl::Window
#include <wtl/windows/controls/Button.hpp>                      //!< wtl::Button
#include <wtl/windows/controls/CheckBox.hpp>                    //!< wtl::CheckBox
#include <wtl/windows/controls/Edit.hpp>                        //!< wtl::Edit
#include <wtl/windows/commands/NewDocumentCommand.hpp>          //!< wtl::NewDocumentCommand
#include <wtl/windows/commands/OpenDocumentCommand.hpp>         //!< wtl::OpenDocumentCommand
#include <wtl/windows/commands/SaveDocumentCommand.hpp>         //!< wtl::SaveDocumentCommand
#include <wtl/windows/commands/AboutProgramCommand.hpp>         //!< wtl::AboutProgramCommand
#include <wtl/windows/commands/ExitProgramCommand.hpp>          //!< wtl::ExitProgramCommand
#include "ExitButton.h"                                         //!< ExitButton

/////////////////////////////////////////////////////////////////////////////////////////
//! \namespace hw2 - Hello World v2 (Controls demonstration)
/////////////////////////////////////////////////////////////////////////////////////////
namespace hw2
{
  ///////////////////////////////////////////////////////////////////////////////
  //! \struct MainWindow - Main window class
  //! 
  //! \tparam ENC - Window charactrer encoding (Default is UTF-16)
  ///////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC = wtl::Encoding::UTF16>
  struct MainWindow : wtl::Window<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias base - Define base type
    using base = wtl::Window<ENC>;
  
    //! \alias type - Define own type
    using type = MainWindow<ENC>;
    
    //! \alias class_t - Inherit window class type
    using class_t = typename base::class_t;

    //! \var encoding - Inherit window character encoding
    static constexpr wtl::Encoding  encoding = base::encoding;
  
    //! \enum ControlId - Define control Ids
    enum class ControlId : int16_t
    {
      First = int16_t(wtl::WindowId::User),

      Exit = First+1,       //!< Button
      Tick1 = First+2,      //!< Checkbox
      Tick2 = First+3,      //!< Checkbox
      Text = First+4,       //!< Edit
    };
  
    // ----------------------------------- REPRESENTATION -----------------------------------
  
    ExitButton<encoding>     Button1;         //!< 'Exit' button 
    wtl::CheckBox<encoding>  Check1,          //!< Example checkbox
                             Check2;          //!< Example checkbox
    wtl::Edit<encoding>      Edit1;           //!< Example edit control

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::MainWindow
    //! Create the main window
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow() : Button1(wtl::window_id(ControlId::Exit)),
                   Check1(wtl::window_id(ControlId::Tick1)),
                   Check2(wtl::window_id(ControlId::Tick2)),
                   Edit1(wtl::window_id(ControlId::Text))
    {
      //! Initialize window properties
      this->Size    = wtl::SizeL(640,480);
      this->Style   = wtl::WindowStyle::OverlappedWindow;
      this->StyleEx = wtl::WindowStyleEx::None;
      this->Text    = "Hello World 2";
      
      //! Listen for window events
      this->Create  += new wtl::CreateWindowEventHandler<encoding>(this, &MainWindow::onCreate);
      this->Destroy += new wtl::DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
      this->Show    += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      //! Initialize child controls
      Check1.Position = wtl::PointL(50,50);
      Check1.Size     = wtl::SizeL(150,25);
      Check1.Text     = "Initially ticked";
      Check1.Visible  = true;
      Check1.Check    = wtl::ButtonState::Checked;
      Check1.Checked += new wtl::CheckBoxCheckedEventHandler<encoding>(this, &MainWindow::onCheck1_Checked);
      
      //! Initialize child controls
      Check2.Position = wtl::PointL(50,100);
      Check2.Size     = wtl::SizeL(150,25);
      Check2.Text     = "Initially unticked";
      Check2.Visible  = true;
      Check2.Check    = wtl::ButtonState::Unchecked;
      Check2.Checked += new wtl::CheckBoxCheckedEventHandler<encoding>(this, &MainWindow::onCheck2_Checked);
      
      //! Initialise edit control
      Edit1.Position = wtl::PointL(250,50);
      Edit1.Size     = wtl::SizeL(350,150);
      Edit1.Style   |= wtl::EditStyle::Multiline;
      Edit1.Text     = "There once was a bear from nantucket\r\n" 
                       "Who desired a less ordinary bucket.\r\n";
      Edit1.Visible  = true;
    }
  
    // ----------------------------------- STATIC METHODS -----------------------------------
  public:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::registerClass 
    //! Registers the window-class 
    //! 
    //! \param[in] instance - Registering module 
    //! \return const WindowClass<encoding>& - Shared window class 
    //! 
    //! \throw wtl::platform_error - Unable to register window class
    ///////////////////////////////////////////////////////////////////////////////
    static const wtl::WindowClass<encoding>& registerClass(::HINSTANCE instance) 
    {
      static wtl::String<encoding> name("MainWindowClass");

      static wtl::WindowClass<encoding> wc(instance,                                              //!< Registering module
                                           name.c_str(),                                          //!< Class name
                                           wtl::ClassStyle::HRedraw|wtl::ClassStyle::VRedraw,     //!< Styles (Redraw upon resize)
                                           base::WndProc,                                         //!< Window procedure
                                           wtl::ResourceIdW(),                                    //!< Window menu 
                                           wtl::HCursor(wtl::SystemCursor::Arrow),                //!< Window cursor
                                           wtl::HBrush(wtl::Colour::Green),                       //!< Window background brush 
                                           wtl::HIcon(wtl::SystemIcon::WinLogo),                  //!< Large window icon 
                                           wtl::HIcon(wtl::SystemIcon::WinLogo));                 //!< Small window icon 

      // Return singleton
      return wc;
    }

    // ---------------------------------- ACCESSOR METHODS ----------------------------------
  public:
    /////////////////////////////////////////////////////////////////////////////////////////
    // MainWindow::wndclass const
    //! Get the window class
    //! 
    //! \return const WindowClass<encoding>& - Shared window class
    /////////////////////////////////////////////////////////////////////////////////////////
    const wtl::WindowClass<encoding>& wndclass() const override
    {
      return registerClass(nullptr);
    }
    
    // ----------------------------------- MUTATOR METHODS ----------------------------------
  private:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCheck1_Checked
    //! Called when the second checkbox is checked or unchecked
    //! 
    //! \param[in] args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCheck1_Checked(wtl::CheckBoxCheckedEventArgs<encoding> args) 
    { 
      // Query new state and append text box
      switch (Check1.Check) 
      {
      case wtl::ButtonState::Checked:       Edit1.Text += L"'Check1' checked \r\n";       break;
      case wtl::ButtonState::Unchecked:     Edit1.Text += L"'Check1' unchecked \r\n";     break;
      case wtl::ButtonState::Indeterminate: Edit1.Text += L"'Check1' indeterminate \r\n"; break;
      }

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCheck2_Checked
    //! Called when the second checkbox is checked or unchecked
    //! 
    //! \param[in] args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCheck2_Checked(wtl::CheckBoxCheckedEventArgs<encoding> args) 
    { 
      // Query new state and append text box
      switch (Check2.Check) 
      {
      case wtl::ButtonState::Checked:       Edit1.Text += L"'Check2' checked \r\n";       break;
      case wtl::ButtonState::Unchecked:     Edit1.Text += L"'Check2' unchecked \r\n";     break;
      case wtl::ButtonState::Indeterminate: Edit1.Text += L"'Check2' indeterminate \r\n"; break;
      }

      // debug
      Check1.Check = wtl::ButtonState::Indeterminate;
      
      wtl::cdebug << "Check1.Check == " << Button_GetCheck(Check1.handle()) << std::endl
                  << "Check2.Check == " << Button_GetCheck(Check2.handle()) << std::endl;

      //Edit1.Font = wtl::HFont(wtl::String<encoding>("Comic Sans MS"), 14);

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCreate
    //! Called during window creation to modify properties on the fly
    //! 
    //! \param[in,out] &args - Message arguments containing window creation properties 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCreate(wtl::CreateWindowEventArgs<encoding>& args) 
    { 
      // Populate window menu from GUI commands
      this->Menu += base::CommandGroups[wtl::CommandGroupId::File];
      this->Menu += base::CommandGroups[wtl::CommandGroupId::Help];

      // Create child controls
      this->Children.create(Button1);
      this->Children.create(Check1);
      this->Children.create(Check2);
      this->Children.create(Edit1);

      // Set edit control font
      Edit1.Font = wtl::HFont(wtl::String<encoding>("Comic Sans MS"), 14);

      // Show 'exit' button
      Button1.show(wtl::ShowWindowFlags::Show);

      // [Handled] Accept window parameters
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onDestroy
    //! Called during window destruction
    //! 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onDestroy() 
    { 
      // Destroy children
      Button1.destroy();
      Check1.destroy();
      Check2.destroy();
      Edit1.destroy();

      // Close program
      this->post(wtl::WindowMessage::Quit);

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onShowWindow
    //! Called when window is being shown or hidden
    //! 
    //! \param[in] &args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onShowWindow(wtl::ShowWindowEventArgs<encoding> args) 
    { 
      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
  
  };

} // namespace

#endif

