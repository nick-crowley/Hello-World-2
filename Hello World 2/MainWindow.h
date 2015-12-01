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

      Hello = First+1,      //!< CheckBox
      Goodbye = First+2,    //!< Exit button
    };
  
    // ----------------------------------- REPRESENTATION -----------------------------------
  
    ExitButton<encoding>     GoodbyeBtn;     //!< 'Exit program' button 
    wtl::CheckBox<encoding>  Check1;         //!< Example checkbox

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::MainWindow
    //! Create the main window
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow() : GoodbyeBtn(wtl::window_id(ControlId::Goodbye)),
                   Check1(wtl::window_id(ControlId::Hello))
    {
      //! Initialize window properties
      this->Size    = wtl::SizeL(640,480);
      this->Style   = wtl::WindowStyle::OverlappedWindow;
      this->StyleEx = wtl::WindowStyleEx::None;
      this->Text    = "Hello World";
      
      //! Register for window events
      this->Create  += new wtl::CreateWindowEventHandler<encoding>(this, &MainWindow::onCreate);
      this->Destroy += new wtl::DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
      this->Paint   += new wtl::PaintWindowEventHandler<encoding>(this, &MainWindow::onPaint);
      this->Show    += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      //! Initialize child controls
      Check1.Position = wtl::PointL(150,50);
      Check1.Size     = wtl::SizeL(75,25);
      Check1.Text     = "Hello";
      Check1.Visible  = true;
      Check1.Checked  = wtl::ButtonState::Checked;

      //! Attach 'File' menu GUI commands
      this->CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::File, { new wtl::NewDocumentCommand<encoding>(*this),
                                                                                          new wtl::OpenDocumentCommand<encoding>(*this),
                                                                                          new wtl::SaveDocumentCommand<encoding>(*this),
                                                                                          new wtl::ExitProgramCommand<encoding>(*this) });
      //! Attach 'Help' menu GUI commands 
      this->CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::Help, { new wtl::AboutProgramCommand<encoding>(*this) });
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
    // MainWindow::onCreate
    //! Called during window creation to modify properties on the fly
    //! 
    //! \param[in] &args - Message arguments containing window creation properties 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCreate(wtl::CreateWindowEventArgs<encoding>& args) 
    { 
      // Populate window menu
      this->Menu += base::CommandGroups[wtl::CommandGroupId::File];
      this->Menu += base::CommandGroups[wtl::CommandGroupId::Help];

      // Create child controls
      this->Children.create(GoodbyeBtn);
      this->Children.create(Check1);

      // Show 'exit' button
      GoodbyeBtn.show(wtl::ShowWindowFlags::Show);

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
      GoodbyeBtn.destroy();

      // Close program
      this->template post<wtl::WindowMessage::Quit>();

      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onPaint
    //! Called to paint the client area of the window
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onPaint(wtl::PaintWindowEventArgs<encoding>& args) 
    {
      // Draw background
      args.Graphics.fill(args.Rect, wtl::StockBrush::AppWorkspace);

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

