/*
  * Copyright (C) 2011 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PAINTERS_SYSTEMRENDERER_H
#define PAINTERS_SYSTEMRENDERER_H

#include <map>
#include <painters/layoutinfo.h>
#include <painters/musicfont.h>
#include <QFontMetricsF>
#include <score/staff.h>

class QGraphicsItem;
class QGraphicsRectItem;
class Score;
class ScoreArea;
class System;

class SystemRenderer
{
public:
    SystemRenderer(const ScoreArea *myScoreArea, const Score &myScore);
    
    QGraphicsItem *operator()(const System &system, int systemIndex,
                              Staff::ViewType view);

private:
    /// Draws the tab clef.
    void drawTabClef(double x, const LayoutInfo &layout);

    /// Draws barlines, along with time signatures, rehearsal signs, etc.
    void drawBarlines(const System &system, int systemIndex,
                      const LayoutConstPtr &layout, bool isFirstStaff);

    /// Draws the tab notes for all notes in the staff.
    void drawTabNotes(const Staff &staff, const LayoutConstPtr &layout);

    /// Centers an item, by using its width to calculate the necessary
    /// offset from xmin.
    void centerItem(QGraphicsItem *item, double xmin, double xmax, double y);

    /// Draws a arpeggio up/down at the given position.
    void drawArpeggio(const Position &position, double x,
                      const LayoutInfo &layout);

    /// Draws system-level symbols such as alternate endings and tempo markers.
    void drawSystemSymbols(const System &system, const LayoutInfo &layout);

    /// Draws a divider line between system symbols.
    void drawDividerLine(double y);

    /// Draws all of the alternate endings in the system.
    void drawAlternateEndings(const System &system, const LayoutInfo &layout,
                              double height);

    /// Draws all of the tempo markers in the system.
    void drawTempoMarkers(const System &system, const LayoutInfo &layout,
                          double height);

    /// Draws all of the directions in the system.
    double drawDirections(const System &system, const LayoutInfo &layout,
                        double height);

    /// Draws the text symbols that appear below the tab staff
    /// (hammerons, slides, etc).
    void drawSymbolsBelowTabStaff(const LayoutInfo &layout);

    /// Creates a pick stroke symbol using the given character.
    QGraphicsItem *createPickStroke(const QString &text);

    /// Creates a plain text item - useful for symbols that don't use the
    /// music font (hammerons, slides, etc).
    QGraphicsItem *createPlainTextSymbol(const QString &text,
                                         QFont::Style style);

    /// Draws symbols that appear above the standard notation staff (e.g. 8va).
    void drawSymbolsAboveStdNotationStaff(const LayoutInfo &layout);

    /// Draws symbols that are grouped across multiple positions
    /// (i.e. consecutive "let ring" symbols).
    QGraphicsItem *createConnectedSymbolGroup(const QString &text,
                                              QFont::Style style, double width,
                                              const LayoutInfo &layout);

    /// Draws symbols that appear below the standard notation staff (e.g. 8vb).
    void drawSymbolsBelowStdNotationStaff(const LayoutInfo &layout);

    /// Draws hammerons, pulloffs, etc in the tab staff.
    void drawLegato(const Staff &staff, const LayoutInfo &layout);

    /// Draws player changes for the given staff.
    void drawPlayerChanges(const System &system, int staffIndex,
                           const LayoutInfo &layout);

    /// Draws the symbols that appear above the tab staff (e.g. vibrato).
    void drawSymbolsAboveTabStaff(const Staff &staff, const LayoutInfo &layout);

    /// Draws a sequence of continuous music symbols (e.g. vibrato).
    QGraphicsItem *drawContinuousFontSymbols(QChar symbol, int width);

    /// Creates a tremolo picking symbol.
    QGraphicsItem *createTremoloPicking(const LayoutInfo &layout);

    /// Creates a trill symbol.
    QGraphicsItem *createTrill(const LayoutInfo &layout);

    /// Creates a dynamic symbol.
    QGraphicsItem *createDynamic(const Dynamic &dynamic);

    /// Draws notes, beams, and rests.
    void drawStdNotation(const System &system, int systemIndex,
                         const Staff &staff, int staffIndex,
                         const LayoutInfo &layout);

    /// Draws a multi-bar rest symbol.
    void drawMultiBarRest(const System &system, const Barline &leftBar,
                          const LayoutInfo &layout, int measureCount);

    /// Draws a rest symbol.
    void drawRest(const Position &pos, double x, const LayoutInfo &layout);

    /// Draws ledger lines for all positions in the staff.
    void drawLedgerLines(const LayoutInfo &layout,
                         const std::map<int, double> &minNoteLocations,
                         const std::map<int, double> &maxNoteLocations,
                         const std::map<int, double> &noteHeadWidths);

    const ScoreArea *myScoreArea;
    const Score &myScore;

    QGraphicsRectItem *myParentSystem;
    QGraphicsItem *myParentStaff;

    MusicFont myMusicFont;
    QFont myMusicNotationFont;
    QFontMetricsF myMusicFontMetrics;
    QFont myPlainTextFont;
    QFont mySymbolTextFont;
    QFont myRehearsalSignFont;
};

#endif
