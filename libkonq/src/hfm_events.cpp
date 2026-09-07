#include "hfm_events.h"

const char *const KonqFileSelectionEvent::s_fileItemSelectionEventName = "Konqueror/FileSelection";
const char *const KonqFileMouseOverEvent::s_fileItemMouseOverEventName = "Konqueror/FileMouseOver";

KonqFileSelectionEvent::KonqFileSelectionEvent(const KFileItemList &selection, KParts::ReadOnlyPart *part)
    : KParts::Event(s_fileItemSelectionEventName), m_selection(selection), m_part(part)
{
}

KonqFileSelectionEvent::~KonqFileSelectionEvent()
{
}

KonqFileMouseOverEvent::KonqFileMouseOverEvent(const KFileItem &item, KParts::ReadOnlyPart *part)
    : KParts::Event(s_fileItemMouseOverEventName), m_item(item), m_part(part)
{
}

KonqFileMouseOverEvent::~KonqFileMouseOverEvent()
{
}
