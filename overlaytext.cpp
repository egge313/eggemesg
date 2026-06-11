#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QFont>

void overlayTextOnBitmap ( QPixmap & originalPixmap, const QString overlayText )
{
   // 2. Create a painter initialized with the pixmap
   QPainter painter(&originalPixmap);
   
   // 3. Customize font, color, and alignment
   painter.setPen ( Qt::black );
   QFont font("Arial", 96, QFont::Bold);
   painter.setFont(font);
   
   // 4. Draw the text (using a bounding rectangle for alignment)
   QRect textRect(10, 10, 500, 500); // x, y, width, height
   painter.drawText(textRect, Qt::AlignCenter | Qt::AlignBottom, overlayText );
   
   // 5. End the painting session
   painter.end();
}
