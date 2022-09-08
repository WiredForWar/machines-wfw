#include "system/pathname.hpp"
#include "gui/RootSharedBitmaps.hpp"

GuiRootSharedBitmaps::GuiRootSharedBitmaps()
    : GuiRootSharedBitmaps(GuiPainter::instance())
{
}

GuiRootSharedBitmaps::GuiRootSharedBitmaps(const IGuiPainter& painter)
    : guiPainter_(painter)
{
}

GuiRootSharedBitmaps::~GuiRootSharedBitmaps()
{
    namedBitmaps_.clear();
    sharedBitmaps_.clear();
}

void GuiRootSharedBitmaps::createUpdateNamedBitmap(const std::string& name, const std::string& image)
{
    loadSharedBitmap(image);
    namedBitmaps_[name] = image;
}

void GuiRootSharedBitmaps::loadSharedBitmap(const std::string& image)
{
    auto sharedBitmap = sharedBitmaps_.find(image);
    // only load once
    if (sharedBitmap == sharedBitmaps_.end())
    {
        sharedBitmaps_[image] = std::make_shared<GuiBitmap>( Gui::bitmap( SysPathName( image ) ) );
    }
}

std::shared_ptr<GuiBitmap> GuiRootSharedBitmaps::getNamedBitmap(const std::string& name) const noexcept
{
    auto sharedBitmapsKey = std::string{ };
    try
    {
        sharedBitmapsKey = namedBitmaps_.at(name);
    }
    catch (const std::out_of_range& ore)
    {
        std::cerr << "GuiRootSharedBitmaps::getNamedBitmap(): " << name << " was never created!!!" << std::endl;
        return std::shared_ptr<GuiBitmap>(nullptr);
    }

    return std::shared_ptr<GuiBitmap>(getSharedBitmap(sharedBitmapsKey));
}

std::weak_ptr<GuiBitmap> GuiRootSharedBitmaps::getSharedBitmap(const std::string& image) const noexcept
{
    try
    {
        return std::weak_ptr<GuiBitmap>(sharedBitmaps_.at(image));
    }
    catch (const std::out_of_range& ore)
    {
        std::cerr << "GuiRootSharedBitmaps::getSharedBitmap(): " << image << " was never loaded!!!" << std::endl;
        return std::weak_ptr<GuiBitmap>();
    }
}

void GuiRootSharedBitmaps::blitNamedBitmapFromArea(const std::shared_ptr<GuiBitmap>& bitmap,
                                                   const Gui::Box& sourceArea,
                                                   const Gui::Coord& destination,
                                                   std::function<Gui::Box(const Gui::Box&)> fnSourceAreaTransform) const
{
    if (bitmap)
    {
        guiPainter_.blit(*bitmap, fnSourceAreaTransform(sourceArea), destination);
    }
    else
    {
        std::cerr << "GuiRootSharedBitmaps::blitNamedBitmapFromArea(): Attempted blit of null named bitmap." << std::endl;
    }
}

void GuiRootSharedBitmaps::blitNamedBitmap(const std::shared_ptr<GuiBitmap>& bitmap,
                                           const Gui::Coord& destination) const
{
    if (bitmap)
    {
        guiPainter_.blit(*bitmap, destination);
    }
    else
    {
        std::cerr << "GuiRootSharedBitmaps::blitNamedBitmap(): Attempted blit of null named bitmap." << std::endl;
    }
}

int GuiRootSharedBitmaps::getWidthOfNamedBitmap(const std::shared_ptr<GuiBitmap>& bitmap) const
{
    int width = 0;

    if (bitmap)
    {
        width = static_cast<int>( bitmap->width() );
    }
    else
    {
        std::cerr << "GuiRootSharedBitmaps::getWidthOfNamedBitmap: Null bitmap. Returning 0" << std::endl;
    }

    return width;
}

int GuiRootSharedBitmaps::getHeightOfNamedBitmap(const std::shared_ptr<GuiBitmap>& bitmap) const
{
    int height = 0;

    if (bitmap)
    {
        height = static_cast<int>( bitmap->height() );
    }
    else
    {
        std::cerr << "GuiRootSharedBitmaps::getHeightOfNamedBitmap: Null bitmap. Returning 0" << std::endl;
    }

    return height;
}