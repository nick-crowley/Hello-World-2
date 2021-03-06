////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\MainWindow.h
//! \brief Defines the main window class
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright � Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HW2_MAIN_WINDOW_H
#define HW2_MAIN_WINDOW_H

#include <wtl/WTL.hpp>                                          //!< Windows Template Library
#include <wtl/utils/Random.hpp>                                 //!< wtl::Random
#include <wtl/windows/Window.hpp>                               //!< wtl::Window
#include <wtl/windows/controls/button/Button.hpp>               //!< wtl::Button
#include <wtl/windows/controls/checkbox/CheckBox.hpp>           //!< wtl::CheckBox
#include <wtl/windows/controls/edit/Edit.hpp>                   //!< wtl::Edit
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
    
    //! \var encoding - Inherit window character encoding
    static constexpr wtl::Encoding  encoding = base::encoding;
  
    //! \enum ControlId - Define control Ids
    enum class ControlId : int16_t
    {
      First = int16_t(wtl::WindowId::User),

      Exit,       //!< Button
      Tick1,      //!< Checkbox
      Tick2,      //!< Checkbox
      Tick3,      //!< Checkbox
      Choice1,    //!< ComboBox
      Text1,      //!< Edit
      Text2,      //!< Edit
    };
  
    // ----------------------------------- REPRESENTATION -----------------------------------
  
    ExitButton<encoding>     Button1;         //!< 'Exit' button 
    wtl::CheckBox<encoding>  Check1,          //!< Example checkbox
                             Check2,          //!< Example checkbox
                             Check3;          //!< Example checkbox
    wtl::ComboBox<encoding>  Combo1;          //!< Example combobox
    wtl::Edit<encoding>      Edit1,           //!< Example edit control
                             Edit2;           //!< Example edit control

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::MainWindow
    //! Create the main window
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow() : Button1(wtl::window_id(ControlId::Exit)),
                   Check1(wtl::window_id(ControlId::Tick1)),
                   Check2(wtl::window_id(ControlId::Tick2)),
                   Check3(wtl::window_id(ControlId::Tick3)),
                   Combo1(wtl::window_id(ControlId::Choice1)),
                   Edit1(wtl::window_id(ControlId::Text1)),
                   Edit2(wtl::window_id(ControlId::Text2))
    {
      //! Initialize window properties
      this->Size    = wtl::SizeL(640,480);
      this->Style   = wtl::WindowStyle::OverlappedWindow;
      this->StyleEx = wtl::WindowStyleEx::None;
      this->Text    = "Hello World 2";
      
      //! Listen for window events
      this->Create  += new wtl::CreateWindowEventHandler<encoding>(this, &MainWindow::onCreate);
      this->Show    += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      //! Initialize child controls
      this->Check1.Position = wtl::PointL(50,50);
      this->Check1.Size     = wtl::SizeL(150,25);
      this->Check1.Text     = "Initially ticked";
      this->Check1.Visible  = true;
      this->Check1.Check    = wtl::ButtonState::Checked;
      this->Check1.Checked += new wtl::CheckBoxCheckedEventHandler<encoding>(this, &MainWindow::onCheck1_Checked);
      
      //! Initialize child controls
      this->Check2.Position = this->Check1.Position + wtl::PointL(0,50);
      this->Check2.Size     = this->Check1.Size;
      this->Check2.Text     = "Initially unticked";
      this->Check2.Visible  = true;
      this->Check2.Check    = wtl::ButtonState::Unchecked;
      this->Check2.Checked += new wtl::CheckBoxCheckedEventHandler<encoding>(this, &MainWindow::onCheck2_Checked);
      
      //! Initialize child controls
      this->Check3.Position = this->Check2.Position + wtl::PointL(0,50);
      this->Check3.Size     = this->Check1.Size;
      this->Check3.Text     = "Initially indeterminate";
      this->Check3.Visible  = true;
      this->Check3.Check    = wtl::ButtonState::Indeterminate;
      this->Check3.Checked += new wtl::CheckBoxCheckedEventHandler<encoding>(this, &MainWindow::onCheck3_Checked);
      
      //! Initialize child controls
      this->Combo1.Position = this->Check3.Position + wtl::PointL(0,50);
      this->Combo1.Size     = this->Check3.Size + wtl::SizeL(0,100);
      this->Combo1.Text     = "Initial text";
      this->Combo1.Visible  = true;
      
      //! Initialise edit control
      this->Edit1.ReadOnly = false;
      this->Edit1.Position = wtl::PointL(250,50);
      this->Edit1.Size     = wtl::SizeL(350,150);
      this->Edit1.Style   |= wtl::EditStyle::Multiline;
      this->Edit1.Text     = "There once was a bear from nantucket \r\n" 
                             "Who desired a less ordinary bucket.\r\n \r\n";
      this->Edit1.Visible  = true;
      this->Edit1.Changed += new wtl::EditChangedEventHandler<encoding>(this, &MainWindow::onEdit1_Changed);
      
      //! Initialise edit control
      this->Edit2.ReadOnly = true;
      this->Edit2.Position = this->Edit1.Position + wtl::PointL(0, this->Edit1.Size().Height + 10);
      this->Edit2.Size     = wtl::SizeL(350,50);
      this->Edit2.Style    = this->Edit1.Style;
      this->Edit2.Visible  = true;
    }
    
    // ----------------------------------- STATIC METHODS -----------------------------------
  public:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::registerClass 
    //! Registers the window-class on the first call, retrieves the pre-registered class upon subsequent calls
    //! 
    //! \param[in] instance - [optional] Module for which to register the window class [Necessary on first call]
    //! \return const WindowClass<encoding>& - Registered window class 
    //! 
    //! \throw wtl::platform_error - Unable to register window class
    /////////////////////////////////////////////////////////////////////////////////////////
    static const wtl::WindowClass<encoding>&  registerClass(::HINSTANCE instance = nullptr)
    {
      static const wtl::String<encoding> name("MainWindowClass");

      static const wtl::WindowClass<encoding> wc(instance,                                              //!< Registering module
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
      return registerClass();
    }
    
    // ----------------------------------- MUTATOR METHODS ----------------------------------
  protected:
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
      this->Button1.create(this);
      this->Check1.create(this);
      this->Check2.create(this);
      this->Check3.create(this);
      this->Combo1.create(this);
      this->Edit1.create(this);
      this->Edit2.create(this);

      // Show 'exit' button [alternative to setting 'Visible = true' in constructor]
      this->Button1.show(wtl::ShowWindowFlags::Show);

      // Insert combobox items
      this->Combo1.Items.append(L"Item1");
      this->Combo1.Items.append(L"Item2");
      this->Combo1.Items.append(L"Item3");
      this->Combo1.MinVisible = 10;

      // [Handled] Accept window parameters
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onDestroy
    //! Called during window destruction to close the program
    //! 
    //! \return wtl::LResult - Routing indicating message was unhandled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onDestroy() override
    { 
      // Close program
      this->post(wtl::WindowMessage::Quit);

      // [Delegate] Pass to base
      return base::onDestroy();
    }

  private:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCheck1_Checked
    //! Called when the check state of the first checkbox changes
    //! 
    //! \param[in] args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCheck1_Checked(wtl::CheckBoxCheckedEventArgs<encoding> args) 
    { 
      // Append edit control
      switch (this->Check1.Check())
      {
      case wtl::ButtonState::Checked:        this->Edit1.Text += L"'Check1' checked \r\n";       break;
      case wtl::ButtonState::Unchecked:      this->Edit1.Text += L"'Check1' unchecked \r\n";     break;
      case wtl::ButtonState::Indeterminate:  this->Edit1.Text += L"'Check1' intermediate \r\n";  break;
      }

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCheck2_Checked
    //! Called when the check state of the second checkbox changes
    //! 
    //! \param[in] args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCheck2_Checked(wtl::CheckBoxCheckedEventArgs<encoding> args) 
    { 
      // Append edit control
      this->Edit1.Text += L"'Check2' check changed \r\n"; 

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCheck3_Checked
    //! Called when the check state of the third checkbox changes
    //! 
    //! \param[in] args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCheck3_Checked(wtl::CheckBoxCheckedEventArgs<encoding> args) 
    { 
      // Append edit control
      this->Edit1.Text += L"'Check3' check changed \r\n"; 

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onEdit1_Changed
    //! Called when text of first edit changes
    //! 
    //! \param[in] &args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult onEdit1_Changed(wtl::EditChangedEventArgs<encoding> args)
    {
      // Display most recent line
      this->Edit2.Text = this->Edit1.Lines.bottom();

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

