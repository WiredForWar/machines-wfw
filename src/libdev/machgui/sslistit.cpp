/*
 * S S L I S T I T . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "gui/sslistit.hpp"
#include "machgui/sslistit.hpp"
#include "machgui/sslistbx.hpp"
#include "machgui/startup.hpp"
#include "machgui/gui.hpp"
#include "gui/font.hpp"
#include "gui/painter.hpp"
#include "machgui/internal/mgsndman.hpp"
#include "machgui/ui/MenuStyle.hpp"

MachGuiSingleSelectionListBoxItem::MachGuiSingleSelectionListBoxItem(
    MachGuiStartupScreens* pStartupScreens,
    MachGuiSingleSelectionListBox* pParentListBox,
    size_t width,
    const string& text)
    : GuiSingleSelectionListBoxItem(pParentListBox, width, reqHeight())
    , text_(text)
    , highlighted_(false)
    , pStartupScreens_(pStartupScreens)
    , pMyListBox_(pParentListBox)
{
    pMyListBox_->addListItem(this);

    pRootParent_ = static_cast<GuiRoot*>(pParentListBox->findRoot(this));

    TEST_INVARIANT;
}

// This variant utilized by MachGuiDropDownListBoxItem to initialize it. Hence, pMyListBox_ is null.
MachGuiSingleSelectionListBoxItem::MachGuiSingleSelectionListBoxItem(
    MachGuiStartupScreens* pStartupScreens,
    GuiSingleSelectionListBox* pParentListBox,
    size_t width,
    const string& text)
    : GuiSingleSelectionListBoxItem(pParentListBox, width, reqHeight())
    , text_(text)
    , highlighted_(false)
    , pStartupScreens_(pStartupScreens)
    , pMyListBox_(nullptr)
{
    pRootParent_ = static_cast<GuiRoot*>(pParentListBox->findRoot(this));

    TEST_INVARIANT;
}

MachGuiSingleSelectionListBoxItem::~MachGuiSingleSelectionListBoxItem()
{
    TEST_INVARIANT;

    if (pMyListBox_)
        pMyListBox_->removeListItem(this);
}

void MachGuiSingleSelectionListBoxItem::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachGuiSingleSelectionListBoxItem& t)
{

    o << "MachGuiSingleSelectionListBoxItem "
      << reinterpret_cast<void*>(const_cast<MachGuiSingleSelectionListBoxItem*>(&t)) << " start" << std::endl;
    o << "MachGuiSingleSelectionListBoxItem "
      << reinterpret_cast<void*>(const_cast<MachGuiSingleSelectionListBoxItem*>(&t)) << " end" << std::endl;

    return o;
}

// static
size_t MachGuiSingleSelectionListBoxItem::reqHeight()
{
    size_t myReqHeight = getFont().charHeight();

    myReqHeight += 5 * MachGui::menuScaleFactor();

    return myReqHeight;
}

// static
GuiBmpFont MachGuiSingleSelectionListBoxItem::getFont()
{
    GuiBmpFont bmpFont = GuiBmpFont::getFont(MachGui::Menu::smallFontLight());

    return bmpFont;
}

// static
GuiBmpFont MachGuiSingleSelectionListBoxItem::getHighlightFont()
{
    GuiBmpFont bmpFont = GuiBmpFont::getFont(MachGui::Menu::smallFontDark());

    return bmpFont;
}

// static
GuiBmpFont MachGuiSingleSelectionListBoxItem::getUnderlineFont()
{
    GuiBmpFont bmpFont = GuiBmpFont::getFont(MachGui::Menu::smallFontDark());

    bmpFont.underline(true);

    return bmpFont;
}

// virtual
void MachGuiSingleSelectionListBoxItem::select()
{
    // Play select sound
    MachGuiSoundManager::instance().playSound("gui/sounds/listclik.wav");

    changed();
}

// virtual
void MachGuiSingleSelectionListBoxItem::unselect()
{
    changed();
}

// virtual
void MachGuiSingleSelectionListBoxItem::doDisplay()
{
    if (isSelected())
    {
        if (pMyListBox_ && pMyListBox_->isFocusControl())
        {
            GuiPainter::instance().blit(
                MachGui::longYellowGlowBmp(),
                Gui::Box(0, 0, width(), height() - 1),
                absoluteBoundary().minCorner());
        }
        else
        {
            GuiPainter::instance().blit(
                MachGui::longGlowBmp(),
                Gui::Box(0, 0, width(), height() - 1),
                absoluteBoundary().minCorner());
        }

        getUnderlineFont().drawText(
            text_,
            Gui::Coord(absoluteBoundary().minCorner().x() + 1, absoluteBoundary().minCorner().y() + 1),
            static_cast<int>(width()));
    }
    else if (isHighlighted())
    {
        if (pMyListBox_ && pMyListBox_->isFocusControl())
        {
            GuiPainter::instance().blit(
                MachGui::longYellowGlowBmp(),
                Gui::Box(0, 0, width(), height() - 1),
                absoluteBoundary().minCorner());
        }
        else
        {
            GuiPainter::instance().blit(
                MachGui::longGlowBmp(),
                Gui::Box(0, 0, width(), height() - 1),
                absoluteBoundary().minCorner());
        }

        getHighlightFont().drawText(
            text_,
            Gui::Coord(absoluteBoundary().minCorner().x() + 1, absoluteBoundary().minCorner().y() + 1),
            static_cast<int>(width()));
    }
    else
    {
        // Draw list box item text
        getFont().drawText(
            text_,
            Gui::Coord(absoluteBoundary().minCorner().x() + 1, absoluteBoundary().minCorner().y() + 1),
            static_cast<int>(width()));
    }
}

bool MachGuiSingleSelectionListBoxItem::isHighlighted() const
{
    return highlighted_;
}

// virtual
void MachGuiSingleSelectionListBoxItem::doHandleMouseEnterEvent(const GuiMouseEvent& /*rel*/)
{
    // Play enter sound
    MachGuiSoundManager::instance().playSound("gui/sounds/listhigh.wav");

    highlighted_ = true;

    if (!isSelected())
        changed();
}

// virtual
void MachGuiSingleSelectionListBoxItem::doHandleMouseExitEvent(const GuiMouseEvent& /*rel*/)
{
    highlighted_ = false;

    if (!isSelected())
        changed();
}

const string& MachGuiSingleSelectionListBoxItem::text() const
{
    return text_;
}

MachGuiStartupScreens* MachGuiSingleSelectionListBoxItem::startupScreens()
{
    return pStartupScreens_;
}

MachGuiSingleSelectionListBox* MachGuiSingleSelectionListBoxItem::myListBox()
{
    return pMyListBox_;
}

/* End SSLISTIT.CPP *************************************************/
