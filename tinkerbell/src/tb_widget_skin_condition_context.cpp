// ================================================================================
// == This file is a part of TinkerBell UI Toolkit. (C) 2011-2012, Emil Seger�s  ==
// ==                   See tinkerbell.h for more information.                   ==
// ================================================================================

#include "tb_widget_skin_condition_context.h"
#include "tb_widgets_common.h"
#include "tb_window.h"
#include "tb_tab_container.h"

namespace tinkerbell {

// == TBWidgetSkinConditionContext ======================================================

bool TBWidgetSkinConditionContext::GetCondition(TBSkinCondition::TARGET target, const TBSkinCondition::CONDITION_INFO &info)
{
	switch (target)
	{
	case TBSkinCondition::TARGET_THIS:
		return GetCondition(m_widget, info);
	case TBSkinCondition::TARGET_PARENT:
		return m_widget->m_parent && GetCondition(m_widget->m_parent, info);
	case TBSkinCondition::TARGET_ANCESTORS:
		{
			TBWidget *widget = m_widget->m_parent;
			while (widget)
			{
				if (GetCondition(widget, info))
					return true;
				widget = widget->m_parent;
			}
		}
	}
	return false;
}

bool TBWidgetSkinConditionContext::GetCondition(TBWidget *widget, const TBSkinCondition::CONDITION_INFO &info)
{
	switch (info.prop)
	{
	case TBSkinCondition::PROPERTY_SKIN:
		return widget->m_skin_bg == info.value;
	case TBSkinCondition::PROPERTY_WINDOW_ACTIVE:
		if (TBWindow *window = widget->GetParentWindow())
			return window->IsActive();
		return false;
	case TBSkinCondition::PROPERTY_AXIS:
		return TBID(widget->GetAxis() == AXIS_X ? "x" : "y") == info.value;
	case TBSkinCondition::PROPERTY_ALIGN:
		if (TBTabContainer *tc = TBSafeCast(TBTabContainer, widget))
		{
			TBID widget_align;
			if (tc->GetAlignment() == TB_ALIGN_LEFT)				widget_align = TBIDC("left");
			else if (tc->GetAlignment() == TB_ALIGN_TOP)			widget_align = TBIDC("top");
			else if (tc->GetAlignment() == TB_ALIGN_RIGHT)		widget_align = TBIDC("right");
			else if (tc->GetAlignment() == TB_ALIGN_BOTTOM)		widget_align = TBIDC("bottom");
			return widget_align == info.value;
		}
		return false;
	case TBSkinCondition::PROPERTY_ID:
		return widget->m_id == info.value;
	case TBSkinCondition::PROPERTY_STATE:
		return !!(widget->GetAutoState() & info.value);
	case TBSkinCondition::PROPERTY_VALUE:
		return widget->GetValue() == info.value;
	case TBSkinCondition::PROPERTY_HOVER:
		return TBWidget::hovered_widget && widget->IsAncestorOf(TBWidget::hovered_widget);
	case TBSkinCondition::PROPERTY_CAPTURE:
		return TBWidget::captured_widget && widget->IsAncestorOf(TBWidget::captured_widget);
	case TBSkinCondition::PROPERTY_FOCUS:
		return TBWidget::focused_widget && widget->IsAncestorOf(TBWidget::focused_widget);
	case TBSkinCondition::PROPERTY_CUSTOM:
		return widget->GetCustomSkinCondition(info);
	}
	return false;
}

}; // namespace tinkerbell