#ifndef KHTMLTTS_H
#define KHTMLTTS_H

#include <hfm_kpart_plugin.h>

class QTextToSpeech;

/**
 * KHTML KParts Plugin
 */
class KHTMLPluginTTS : public KonqParts::Plugin
{
    Q_OBJECT
public:

    /**
     * Construct a new KParts plugin.
     */
    KHTMLPluginTTS(QObject *parent, const QVariantList &);

    /**
     * Destructor.
     */
    ~KHTMLPluginTTS() override;
public Q_SLOTS:
    void slotReadOut();
private:
    std::unique_ptr<QTextToSpeech> m_tts;
};

#endif
