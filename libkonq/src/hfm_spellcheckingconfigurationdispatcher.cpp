#include "hfm_spellcheckingconfigurationdispatcher.h"

KonqSpellCheckingConfigurationDispatcher * KonqSpellCheckingConfigurationDispatcher::self()
{
    static KonqSpellCheckingConfigurationDispatcher s_self;
    return &s_self;
}


