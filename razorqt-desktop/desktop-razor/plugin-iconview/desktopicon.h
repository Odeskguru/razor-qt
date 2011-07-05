/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/projects/razor-qt/
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef DESKTOPICON_H
#define DESKTOPICON_H

#include <QGraphicsLayoutItem>
#include <QGraphicsTextItem>
#include <razorqt/xdgdesktopfile.h>

class RazorMimeInfo;

class IconViewLabel : public QGraphicsTextItem
{
    Q_OBJECT
    
public:
    IconViewLabel(const QString & text, QGraphicsItem * parent = 0);
};


class IconBase : public QGraphicsItem
{
public:
    IconBase(QGraphicsItem * parent=0);

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void setIcon(const QIcon & icon);
    void setText(const QString & text);

    static int iconWidth() { return 80; }
    static int iconHeight() { return 80; }
    
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QPixmap m_pm; // std
    QPixmap m_pm_hi; // highlight
    bool m_highlight;
    QString m_text;

    /**
    @brief Launch assigned m_exec binary/path.
    Called when is the button clicked.
     */
    virtual void launchApp() = 0;
};


/** \brief Icon for the XDG desktop file. It uses XdgDesktopFile handler
from librazorqt.
 */
class DesktopIcon : public IconBase
{
    
public:
    DesktopIcon(XdgDesktopFile * xdg,
                QGraphicsItem * parent = 0
               );
    ~DesktopIcon();

private:
    XdgDesktopFile * m_xdg;

    /**
    @brief Launch assigned m_exec binary/path.
    Called when is the button clicked.
     */
    void launchApp();

};

/** \brief Icon for standard file. It uses QDesktopServices to launch the
"open with" application by file mime type.
 */
class FileIcon : public IconBase
{
    
public:
    FileIcon(const QString & file,
             QGraphicsItem * parent = 0
            );

private:
    QString m_file;
    RazorMimeInfo* m_mimeInfo;

    /**
    @brief Launch assigned m_exec binary/path.
    Called when is the button clicked.
     */
    void launchApp();

};

#endif // DESKTOPICON_H