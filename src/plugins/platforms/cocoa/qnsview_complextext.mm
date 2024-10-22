/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

// This file is included from qnsview.mm, and only used to organize the code

@implementation QNSView (ComplexText)

// ------------- Text insertion -------------

/*
    Inserts the given text, potentially replacing existing text.

    The text input management system calls this as a result of:

     - A normal key press, via [NSView interpretKeyEvents:] or
       [NSInputContext handleEvent:]

     - An input method finishing (confirming) composition

     - Pressing a key in the Keyboard Viewer panel

     - Confirming an inline input area (accent popup e.g.)

    \a replacementRange refers to the existing text to replace.
    Under normal circumstances this is {NSNotFound, 0}, and the
    implementation should replace either the existing marked text,
    the current selection, or just insert the text at the current
    cursor location.
*/
- (void)insertText:(id)text replacementRange:(NSRange)replacementRange
{
    qCDebug(lcQpaKeys).nospace() << "Inserting \"" << text << "\""
        << ", replacing range " << replacementRange;

    if (m_sendKeyEvent && m_composingText.isEmpty() && [text isEqualToString:m_inputSource]) {
        // We do not send input method events for simple text input,
        // and instead let handleKeyEvent send the key event.
        qCDebug(lcQpaKeys) << "Not sending simple text as input method event";
        return;
    }

    QObject *focusObject = m_platformWindow->window()->focusObject();
    if (queryInputMethod(focusObject)) {
        QInputMethodEvent inputMethodEvent;

        const bool isAttributedString = [text isKindOfClass:NSAttributedString.class];
        QString commitString = QString::fromNSString(isAttributedString ? [text string] : text);

        const auto markedRange = [self markedRange];
        const auto selectedRange = [self selectedRange];

        // If the replacement range is not specified we are expected to compute
        // the range ourselves, based on the current state of the input context.
        if (replacementRange.location == NSNotFound) {
            if (markedRange.location != NSNotFound)
                replacementRange = markedRange;
            else
                replacementRange = selectedRange;
        }

        // Qt's QInputMethodEvent has different semantics for the replacement
        // range than AppKit does, so we need to sanitize the range first.
        long long replaceFrom = replacementRange.location;
        long long replaceLength = replacementRange.length;

        // The QInputMethodEvent replacement start is relative to the start
        // of the marked text (the location of the preedit string).
        if (markedRange.location != NSNotFound)
            replaceFrom -= markedRange.location;
        else
            replaceFrom = 0;

        // The replacement length of QInputMethodEvent already includes
        // the selection, as the documentation says that "If the widget
        // has selected text, the selected text should get removed."
        replaceLength -= selectedRange.length;

        // The replacement length of QInputMethodEvent already includes
        // the preedit string, as the documentation says that "When doing
        // replacement, the area of the preedit string is ignored".
        replaceLength -= markedRange.length;

        // What we're left with is any _additional_ replacement.
        // Make sure it's valid before passing it on.
        replaceLength = qMax(0ll, replaceLength);

        if (replaceFrom == NSNotFound) {
            qCWarning(lcQpaKeys) << "Failed to compute valid replacement range for text insertion";
            inputMethodEvent.setCommitString(commitString);
        } else {
            qCDebug(lcQpaKeys) << "Replacing from" << replaceFrom << "with length" << replaceLength
                << "based on marked range" << markedRange << "and selection" << selectedRange;
            inputMethodEvent.setCommitString(commitString, replaceFrom, replaceLength);
        }

        QCoreApplication::sendEvent(focusObject, &inputMethodEvent);

        // prevent handleKeyEvent from sending a key event
        m_sendKeyEvent = false;
    }

    m_composingText.clear();
    m_composingFocusObject = nullptr;
}

- (void)insertNewline:(id)sender
{
    Q_UNUSED(sender);
    qCDebug(lcQpaKeys) << "Inserting newline";
    m_resendKeyEvent = true;
}

// ------------- Text composition -------------

/*
    Updates the composed text, potentially replacing existing text.

    The NSTextInputClient protocol refers to composed text as "marked",
    since it is "marked differently from the selection, using temporary
    attributes that affect only display, not layout or storage.""

    The concept maps to the preeditString of our QInputMethodEvent.

    \a selectedRange refers to the part of the marked text that
    is considered selected, for example when composing text with
    multiple clause segments (Hiragana - Kana e.g.).

    \a replacementRange refers to the existing text to replace.
    Under normal circumstances this is {NSNotFound, 0}, and the
    implementation should replace either the existing marked text,
    the current selection, or just insert the text at the current
    cursor location. But when initiating composition of existing
    committed text (Hiragana - Kana e.g.), the range will be valid.
*/
- (void)setMarkedText:(id)text selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange
{
    qCDebug(lcQpaKeys).nospace() << "Marking \"" << text << "\""
        << " with selected range " << selectedRange
        << ", replacing range " << replacementRange;

    const bool isAttributedString = [text isKindOfClass:NSAttributedString.class];
    QString preeditString = QString::fromNSString(isAttributedString ? [text string] : text);

    QList<QInputMethodEvent::Attribute> preeditAttributes;
    preeditAttributes << QInputMethodEvent::Attribute(
        QInputMethodEvent::Cursor, selectedRange.location + selectedRange.length, true);


    // QInputMethodEvent::Selection unfortunately doesn't apply to the
    // preedit text, and QInputMethodEvent::Cursor which does, doesn't
    // support setting a selection. Until we've introduced attributes
    // that allow us to propagate the preedit selection semantically
    // we resort to styling the selection via the TextFormat attribute,
    // so that the preedit selection is visible to the user.
    QTextCharFormat selectionFormat;
    auto *platformTheme = QGuiApplicationPrivate::platformTheme();
    auto *systemPalette = platformTheme->palette();
    selectionFormat.setBackground(systemPalette->color(QPalette::Highlight));
    preeditAttributes << QInputMethodEvent::Attribute(
        QInputMethodEvent::TextFormat,
        selectedRange.location, selectedRange.length,
        selectionFormat);

    int index = 0;
    int composingLength = preeditString.length();
    while (index < composingLength) {
        NSRange range = NSMakeRange(index, composingLength - index);

        static NSDictionary *defaultMarkedTextAttributes = []{
            NSTextView *textView = [[NSTextView new] autorelease];
            return [textView.markedTextAttributes retain];
        }();

        NSDictionary *attributes = isAttributedString
            ? [text attributesAtIndex:index longestEffectiveRange:&range inRange:range]
            : defaultMarkedTextAttributes;

        qCDebug(lcQpaKeys) << "Decorating range" << range << "based on" << attributes;
        QTextCharFormat format;

        if (NSNumber *underlineStyle = attributes[NSUnderlineStyleAttributeName]) {
            format.setFontUnderline(true);
            NSUnderlineStyle style = underlineStyle.integerValue;
            if (style & NSUnderlineStylePatternDot)
                format.setUnderlineStyle(QTextCharFormat::DotLine);
            else if (style & NSUnderlineStylePatternDash)
                format.setUnderlineStyle(QTextCharFormat::DashUnderline);
            else if (style & NSUnderlineStylePatternDashDot)
                format.setUnderlineStyle(QTextCharFormat::DashDotLine);
            if (style & NSUnderlineStylePatternDashDotDot)
                format.setUnderlineStyle(QTextCharFormat::DashDotDotLine);
            else
                format.setUnderlineStyle(QTextCharFormat::SingleUnderline);

            // Unfortunately QTextCharFormat::UnderlineStyle does not distinguish
            // between NSUnderlineStyle{Single,Thick,Double}, which is used by CJK
            // input methods to highlight the selected clause segments.
        }
        if (NSColor *underlineColor = attributes[NSUnderlineColorAttributeName])
            format.setUnderlineColor(qt_mac_toQColor(underlineColor));
        if (NSColor *foregroundColor = attributes[NSForegroundColorAttributeName])
            format.setForeground(qt_mac_toQColor(foregroundColor));
        if (NSColor *backgroundColor = attributes[NSBackgroundColorAttributeName])
            format.setBackground(qt_mac_toQColor(backgroundColor));

        if (format != QTextCharFormat()) {
            preeditAttributes << QInputMethodEvent::Attribute(
                QInputMethodEvent::TextFormat, range.location, range.length, format);
        }

        index = range.location + range.length;
    }

    m_composingText = preeditString;

    if (QObject *focusObject = m_platformWindow->window()->focusObject()) {
        m_composingFocusObject = focusObject;
        if (queryInputMethod(focusObject)) {
            QInputMethodEvent event(preeditString, preeditAttributes);
            QCoreApplication::sendEvent(focusObject, &event);
            // prevent handleKeyEvent from sending a key event
            m_sendKeyEvent = false;
        }
    }
}

- (NSArray<NSString *> *)validAttributesForMarkedText
{
    return @[
        NSUnderlineColorAttributeName,
        NSUnderlineStyleAttributeName,
        NSForegroundColorAttributeName,
        NSBackgroundColorAttributeName
    ];
}

- (BOOL)hasMarkedText
{
    return !m_composingText.isEmpty();
}

/*
    Returns the range of marked text or {cursorPosition, 0} if there's none.

    This maps to the location and length of the current preedit (composited) string.

    The returned range measures from the start of the receiver’s text storage,
    that is, from 0 to the document length.
*/
- (NSRange)markedRange
{
    QObject *focusObject = m_platformWindow->window()->focusObject();
    if (auto queryResult = queryInputMethod(focusObject, Qt::ImAbsolutePosition)) {
        int absoluteCursorPosition = queryResult.value(Qt::ImAbsolutePosition).toInt();

        // The cursor position as reflected by Qt::ImAbsolutePosition is not
        // affected by the offset of the cursor in the preedit area. That means
        // that when composing text, the cursor position stays the same, at the
        // preedit insertion point, regardless of where the cursor is positioned within
        // the preedit string by the QInputMethodEvent::Cursor attribute. This means
        // we can use the cursor position to determine the range of the marked text.

        // The NSTextInputClient documentation says {NSNotFound, 0} should be returned if there
        // is no marked text, but in practice NSTextView seems to report {cursorPosition, 0},
        // so we do the same.
        return NSMakeRange(absoluteCursorPosition, m_composingText.length());
    } else {
        return {NSNotFound, 0};
    }
}

/*
    Confirms the marked (composed) text.

    The marked text is accepted as if it had been inserted normally,
    and the preedit string is cleared.

    If there is no marked text this method has no effect.
*/
- (void)unmarkText
{
    // FIXME: Match cancelComposingText in early exit and focus object handling

    qCDebug(lcQpaKeys) << "Unmarking" << m_composingText
        << "for focus object" << m_composingFocusObject;

    if (!m_composingText.isEmpty()) {
        QObject *focusObject = m_platformWindow->window()->focusObject();
        if (queryInputMethod(focusObject)) {
            QInputMethodEvent e;
            e.setCommitString(m_composingText);
            QCoreApplication::sendEvent(focusObject, &e);
        }
    }

    m_composingText.clear();
    m_composingFocusObject = nullptr;
}

/*
    Cancels composition.

    The marked text is discarded, and the preedit string is cleared.

    If there is no marked text this method has no effect.
*/
- (void)cancelComposingText
{
    if (m_composingText.isEmpty())
        return;

    qCDebug(lcQpaKeys) << "Canceling composition" << m_composingText
        << "for focus object" << m_composingFocusObject;

    if (queryInputMethod(m_composingFocusObject)) {
        QInputMethodEvent e;
        QCoreApplication::sendEvent(m_composingFocusObject, &e);
    }

    m_composingText.clear();
    m_composingFocusObject = nullptr;
}

// ------------- Key binding command handling -------------

- (void)doCommandBySelector:(SEL)selector
{
    qCDebug(lcQpaKeys) << "Trying to perform command" << selector;
    [self tryToPerform:selector with:self];
}

// ------------- Various text properties -------------

/*
    Returns the range of selected text, or {cursorPosition, 0} if there's none.

    The returned range measures from the start of the receiver’s text storage,
    that is, from 0 to the document length.
*/
- (NSRange)selectedRange
{
    QObject *focusObject = m_platformWindow->window()->focusObject();
    if (auto queryResult = queryInputMethod(focusObject,
            Qt::ImCursorPosition | Qt::ImAbsolutePosition | Qt::ImAnchorPosition)) {

        // Unfortunately the Qt::InputMethodQuery values are all relative
        // to the start of the current editing block (paragraph), but we
        // need them in absolute values relative to the entire text.
        // Luckily we have one property, Qt::ImAbsolutePosition, that
        // we can use to compute the offset.
        int cursorPosition = queryResult.value(Qt::ImCursorPosition).toInt();
        int absoluteCursorPosition = queryResult.value(Qt::ImAbsolutePosition).toInt();
        int absoluteOffset = absoluteCursorPosition - cursorPosition;

        int anchorPosition = absoluteOffset + queryResult.value(Qt::ImAnchorPosition).toInt();
        int selectionStart = anchorPosition >= absoluteCursorPosition ? absoluteCursorPosition : anchorPosition;
        int selectionEnd = selectionStart == anchorPosition ? absoluteCursorPosition : anchorPosition;
        int selectionLength = selectionEnd - selectionStart;

        // Note: The cursor position as reflected by these properties are not
        // affected by the offset of the cursor in the preedit area. That means
        // that when composing text, the cursor position stays the same, at the
        // preedit insertion point, regardless of where the cursor is positioned within
        // the preedit string by the QInputMethodEvent::Cursor attribute.

        // The NSTextInputClient documentation says {NSNotFound, 0} should be returned if there is no
        // selection, but in practice NSTextView seems to report {cursorPosition, 0}, so we do the same.
        return NSMakeRange(selectionStart, selectionLength);
    } else {
        return {NSNotFound, 0};
    }
}

- (NSAttributedString *)attributedSubstringForProposedRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    Q_UNUSED(actualRange);

    QObject *focusObject = m_platformWindow->window()->focusObject();
    if (auto queryResult = queryInputMethod(focusObject, Qt::ImCurrentSelection)) {
        QString selectedText = queryResult.value(Qt::ImCurrentSelection).toString();
        if (selectedText.isEmpty())
            return nil;

        NSString *substring = QStringView(selectedText).mid(range.location, range.length).toNSString();
        return [[[NSAttributedString alloc] initWithString:substring] autorelease];

    } else {
        return nil;
    }
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    Q_UNUSED(range);
    Q_UNUSED(actualRange);

    QWindow *window = m_platformWindow->window();
    if (queryInputMethod(window->focusObject())) {
        QRect cursorRect = qApp->inputMethod()->cursorRectangle().toRect();
        cursorRect.moveBottomLeft(window->mapToGlobal(cursorRect.bottomLeft()));
        return QCocoaScreen::mapToNative(cursorRect);
    } else {
        return NSZeroRect;
    }
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point
{
    // We don't support cursor movements using mouse while composing.
    Q_UNUSED(point);
    return NSNotFound;
}

@end
