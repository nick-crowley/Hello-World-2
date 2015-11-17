////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld2\MainWindow.h
//! \brief Defines the main window class
//! \date 4 November 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wtl/WTL.hpp>                                          //!< Windows Template Library
#include <wtl/utils/Random.hpp>                                 //!< wtl::Random
#include <wtl/windows/WindowBase.hpp>                           //!< wtl::WindowBase
#include <wtl/controls/Button.hpp>                              //!< wtl::Button
#include <wtl/controls/CheckBox.hpp>                            //!< wtl::CheckBox
#include <wtl/windows/commands/NewDocumentCommand.hpp>          //!< wtl::NewDocumentCommand
#include <wtl/windows/commands/OpenDocumentCommand.hpp>         //!< wtl::OpenDocumentCommand
#include <wtl/windows/commands/SaveDocumentCommand.hpp>         //!< wtl::SaveDocumentCommand
#include <wtl/windows/commands/CutClipboardCommand.hpp>         //!< wtl::CutClipboardCommand
#include <wtl/windows/commands/CopyClipboardCommand.hpp>        //!< wtl::CopyClipboardCommand
#include <wtl/windows/commands/PasteClipboardCommand.hpp>       //!< wtl::PasteClipboardCommand
#include <wtl/windows/commands/AboutProgramCommand.hpp>         //!< wtl::AboutProgramCommand
#include <wtl/windows/commands/ExitProgramCommand.hpp>          //!< wtl::ExitProgramCommand


//! \namespace hw2 - Hello World v2 (Controls demonstration)
namespace hw2
{
  /////////////////////////////////////////////////////////////////////////////////////////
  //! \struct ExitButton - Defines the 'exit' button control
  /////////////////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC>
  struct ExitButton : wtl::Button<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias type - Define own type
    using type = ExitButton;

    //! \alias base - Define base type
    using base = wtl::Button<ENC>;
      
    //! \alias resource_t - Inherit resource identifier type
    using resource_t = typename base::resource_t;
    
    //! \var encoding - Inherit window character encoding
    static constexpr wtl::Encoding  encoding = base::encoding;
  
    // ----------------------------------- REPRESENTATION -----------------------------------
      
    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // ExitButton::ExitButton
    //! Creates a standard button control
    //! 
    //! \param[in] instance - Owning instance
    //! \param[in] id - Control ID
    //! 
    //! \throw platform_error - Unrecognised system window class
    /////////////////////////////////////////////////////////////////////////////////////////
    ExitButton(::HINSTANCE instance, wtl::WindowId id) : base(instance)
    {
      // Properties
      this->Font      = wtl::HFont(wtl::c_str("MS Shell Dlg 2"), 11, wtl::FontWeight::Bold);
      this->Ident     = id;
      this->Position  = wtl::PointL(500,50);
      this->Style    |= wtl::WindowStyle::Visible;
      this->Size      = wtl::SizeL(100,50);
      this->Text      = wtl::c_str(L"Goodbye");
      this->Icon      = wtl::IconResource(resource_t(wtl::CommandId::App_Exit)).Handle;
        
      // Events
      this->Click += new wtl::ButtonClickEventHandler<encoding>(this, &ExitButton::onClick);
    }
      
    // ----------------------------------- STATIC METHODS -----------------------------------

    // ---------------------------------- ACCESSOR METHODS ----------------------------------

    // ----------------------------------- MUTATOR METHODS ----------------------------------

    ///////////////////////////////////////////////////////////////////////////////
    // ExitButton::onClick
    //! Exits the program
    //! 
    //! \param[in] args - Message arguments
    //! \return wtl::LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onClick(wtl::ButtonClickEventArgs<encoding> args) 
    { 
      // Execute 'Exit Program' gui command
      //this->execute(wtl::CommandId::App_Exit);
    
      // Handled
      return 0;     
    }
  };


  ///////////////////////////////////////////////////////////////////////////////
  //! \struct MainWindow - Main window class
  //! 
  //! \tparam ENC - Window charactrer encoding (Default is UTF-16)
  ///////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC = wtl::Encoding::UTF16>
  struct MainWindow : wtl::WindowBase<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias base - Define base type
    using base = wtl::WindowBase<ENC>;
  
    //! \alias type - Define own type
    using type = MainWindow<ENC>;

    //! \alias wndmenu_t - Inherit window menu type
    using wndmenu_t = typename base::wndmenu_t;

    //! \alias wndclass_t - Inherit window class type
    using wndclass_t = typename base::wndclass_t;

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
    //! 
    //! \param[in] instance - Module handle
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow(::HINSTANCE instance) : base(getClass(instance)), 
                                       GoodbyeBtn(instance, wtl::window_id(ControlId::Goodbye)),
                                       Check1(instance)
    {
      // Properties
      this->Size    = wtl::SizeL(640,480);
      this->Style   = wtl::WindowStyle::OverlappedWindow;
      this->StyleEx = wtl::WindowStyleEx::None;
      this->Text    = wtl::c_str(L"Hello World");
      
      // Events
      this->Create  += new wtl::CreateWindowEventHandler<encoding>(this, &MainWindow::onCreate);
      this->Destroy += new wtl::DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
      this->Paint   += new wtl::PaintWindowEventHandler<encoding>(this, &MainWindow::onPaint);
      this->Show    += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      // Controls
      Check1.Font     = wtl::HFont(wtl::c_str("MS Shell Dlg 2"), 11, wtl::FontWeight::Bold);
      Check1.Ident    = wtl::window_id(ControlId::Hello);
      Check1.Position = wtl::PointL(150,50);
      Check1.Size     = wtl::SizeL(75,25);
      Check1.Style   |= wtl::WindowStyle::Visible;
      Check1.Text     = wtl::c_str(L"Hello");

      // Commands: File
      base::CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::File, { new wtl::NewDocumentCommand<encoding>(*this),
                                                                                          new wtl::OpenDocumentCommand<encoding>(*this),
                                                                                          new wtl::SaveDocumentCommand<encoding>(*this),
                                                                                          new wtl::ExitProgramCommand<encoding>(*this) });
      // Commands: Edit
      base::CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::Edit, { new wtl::CutClipboardCommand<encoding>(),
                                                                                          new wtl::CopyClipboardCommand<encoding>(),
                                                                                          new wtl::PasteClipboardCommand<encoding>() });
      // Commands: Help
      base::CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::Help, { new wtl::AboutProgramCommand<encoding>(*this) });
    }
  
    // ----------------------------------- STATIC METHODS -----------------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::getClass 
    //! Get the window class
    //! 
    //! \param[in] instance - Module handle
    //! \return wndclass_t& - Window class 
    ///////////////////////////////////////////////////////////////////////////////
    static wndclass_t& getClass(::HINSTANCE instance) 
    {
      static wndclass_t wc(instance,                                              //!< Registering module
                           wtl::resource_name(L"MainWindowClass"),                //!< Class name
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

    // ----------------------------------- MUTATOR METHODS ----------------------------------
  protected:
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
      this->Menu += base::CommandGroups[wtl::CommandGroupId::Edit];
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
    // MainWindow::onOwnerDraw
    //! Called to paint the button
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return wtl::LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    //wtl::LResult  onOwnerDraw(OwnerDrawEventArgs<encoding>& args)
    //{
    //  if (args.Ident == ControlId::Goodbye)
    //  {
    //    args.Graphics.fill(args.Rect, wtl::StockBrush::Green);
    //  }

    //  // Handled
    //  return 0;
    //}

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onPaint
    //! Called to paint the client area of the window
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onPaint(wtl::PaintWindowEventArgs<encoding>& args) 
    {
      static int32_t numEggs = wtl::Random::number(4,8);

      // Draw background
      args.Graphics.fill(args.Rect, wtl::StockBrush::Green);

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

