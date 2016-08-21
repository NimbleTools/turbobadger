// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_IMAGE_WIDGET_H
#define TB_IMAGE_WIDGET_H

#include "tb_widgets.h"

#ifdef TB_IMAGE

#include "image/tb_image_manager.h"

namespace tb {

enum IMAGE_FIT {
	IMAGE_FIT_NONE,
	IMAGE_FIT_SCALE
};

/** TBImageWidget is a widget showing a image loaded by TBImageManager,
	constrained in size to its skin.
	If you need to show a image from the skin, you can use TBSkinImage. */

class TBImageWidget : public TBWidget
{
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBImageWidget, TBWidget);

	TBImageWidget() {}

	void SetImage(const TBImage &image) { m_image = image; }
	void SetImage(const char *filename) { m_image = g_image_manager->GetImage(filename); }

	void SetFit(IMAGE_FIT fit) { m_fit = fit; }

	virtual PreferredSize OnCalculatePreferredContentSize(const SizeConstraints &constraints);

	virtual void OnInflate(const INFLATE_INFO &info);
	virtual void OnPaint(const PaintProps &paint_props);
private:
	TBImage m_image;
	IMAGE_FIT m_fit = IMAGE_FIT_SCALE;
};

} // namespace tb

#endif // TB_IMAGE
#endif // TB_IMAGE_WIDGET_H
