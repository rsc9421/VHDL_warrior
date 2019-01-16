/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"
#include"mainwindow.h"
#include<QDebug>

//! [0]
//!
//!
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{


    HighlightingRule rule;

    keywordFormat.setForeground(QColor(128,0,128));


    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\babs\\b" << "\\baccess\\b" << "\\bafter\\b"
                    << "\\balias\\b" << "\\ball\\b" << "\\band\\b"
                    << "\\barchitecture\\b" << "\\barray\\b" << "\\bassert\\b"
                    << "\\battribute\\b" << "\\bbegin\\b" << "\\bblock\\b"
                    << "\\bbody\\b" << "\\bbuffer\\b" << "\\bbus\\b"
                    << "\\bconstant\\b" << "\\bdisconnect\\b" << "\\bdownto\\b"
                    << "\\belse\\b" << "\\belsif\\b" << "\\bend\\b"
                    << "\\bentity\\b" << "\\bexit\\b" << "\\bfile\\b"
                    << "\\bfor\\b" << "\\bfunction\\b" << "\\bgenerate\\b"
                    << "\\bgeneric\\b" << "\\bgroup\\b" << "\\bguarded\\b"
                    << "\\bif\\b" << "\\bimpure\\b" << "\\binertial\\b"
                    << "\\binout\\b" << "\\bis\\b" << "\\blabel\\b"
                    << "\\blibrary\\b" << "\\blinkage\\b" << "\\bliteral\\b"
                    << "\\bloop\\b" << "\\bmod\\b" << "\\bmap\\b"
                    << "\\bnand\\b" << "\\bnew\\b" << "\\bnext\\b"
                    << "\\bnor\\b" << "\\bnot\\b" << "\\bnull\\b"
                    << "\\bof\\b" << "\\bon\\b" << "\\bopen\\b"
                    << "\\bor\\b" << "\\bothers\\b" << "\\bout\\b"
                    << "\\bpackage\\b" << "\\bport\\b" << "\\bpostponed\\b"
                    << "\\bprocedure\\b" << "\\bprocess\\b" << "\\bpure\\b"
                    << "\\brange\\b" << "\\brecord\\b" << "\\bregister\\b"
                    << "\\breject\\b" << "\\brom\\b" << "\\breport\\b"
                    << "\\breturn\\b" << "\\brol\\b" << "\\bror\\b"
                    << "\\bselect\\b" << "\\bseverity\\b" << "\\bsignal\\b"
                    << "\\bshared\\b" << "\\bsll\\b" << "\\bsla\\b"
                    << "\\bsra\\b" << "\\bsrl\\b" << "\\bsubtype\\b"
                    << "\\bthen\\b" << "\\bto\\b" << "\\btransport\\b"
                    << "\\btype\\b" << "\\bunaffected\\b" << "\\bunits\\b"
                    << "\\buntil\\b" << "\\buse\\b" << "\\bvariable\\b"
                    << "\\bwait\\b" << "\\bwhen\\b" << "\\bwhile\\b"
                    << "\\bcase\\b" << "\\bcomponent\\b" << "\\bconfiguration\\b" << "\\bin\\b"
                    << "\\bwith\\b" << "\\bxnor\\b" << "\\bxor\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2]
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
//! [2]

//! [3]
    singleLineCommentFormat.setForeground(QColor(0,128,0));
    rule.pattern = QRegularExpression("--[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);
//! [3]

//! [4]
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5]
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
//! [5]

//! [6]
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}
//! [6]

void Highlighter::setcolor(int a){
    //a=0 dark
    if(a==0){
           HighlightingRule rule;
           keywordFormat.setForeground(QColor(0,230,75));
           keywordFormat.setFontWeight(QFont::Bold);
           QStringList keywordPatterns;
           keywordPatterns << "\\babs\\b" << "\\baccess\\b" << "\\bafter\\b"
                           << "\\balias\\b" << "\\ball\\b" << "\\band\\b"
                           << "\\barchitecture\\b" << "\\barray\\b" << "\\bassert\\b"
                           << "\\battribute\\b" << "\\bbegin\\b" << "\\bblock\\b"
                           << "\\bbody\\b" << "\\bbuffer\\b" << "\\bbus\\b"
                           << "\\bconstant\\b" << "\\bdisconnect\\b" << "\\bdownto\\b"
                           << "\\belse\\b" << "\\belsif\\b" << "\\bend\\b"
                           << "\\bentity\\b" << "\\bexit\\b" << "\\bfile\\b"
                           << "\\bfor\\b" << "\\bfunction\\b" << "\\bgenerate\\b"
                           << "\\bgeneric\\b" << "\\bgroup\\b" << "\\bguarded\\b"
                           << "\\bif\\b" << "\\bimpure\\b" << "\\binertial\\b"
                           << "\\binout\\b" << "\\bis\\b" << "\\blabel\\b"
                           << "\\blibrary\\b" << "\\blinkage\\b" << "\\bliteral\\b"
                           << "\\bloop\\b" << "\\bmod\\b" << "\\bmap\\b"
                           << "\\bnand\\b" << "\\bnew\\b" << "\\bnext\\b"
                           << "\\bnor\\b" << "\\bnot\\b" << "\\bnull\\b"
                           << "\\bof\\b" << "\\bon\\b" << "\\bopen\\b"
                           << "\\bor\\b" << "\\bothers\\b" << "\\bout\\b"
                           << "\\bpackage\\b" << "\\bport\\b" << "\\bpostponed\\b"
                           << "\\bprocedure\\b" << "\\bprocess\\b" << "\\bpure\\b"
                           << "\\brange\\b" << "\\brecord\\b" << "\\bregister\\b"
                           << "\\breject\\b" << "\\brom\\b" << "\\breport\\b"
                           << "\\breturn\\b" << "\\brol\\b" << "\\bror\\b"
                           << "\\bselect\\b" << "\\bseverity\\b" << "\\bsignal\\b"
                           << "\\bshared\\b" << "\\bsll\\b" << "\\bsla\\b"
                           << "\\bsra\\b" << "\\bsrl\\b" << "\\bsubtype\\b"
                           << "\\bthen\\b" << "\\bto\\b" << "\\btransport\\b"
                           << "\\btype\\b" << "\\bunaffected\\b" << "\\bunits\\b"
                           << "\\buntil\\b" << "\\buse\\b" << "\\bvariable\\b"
                           << "\\bwait\\b" << "\\bwhen\\b" << "\\bwhile\\b"
                           << "\\bcase\\b" << "\\bcomponent\\b" << "\\bconfiguration\\b" << "\\bin\\b"
                           << "\\bwith\\b" << "\\bxnor\\b" << "\\bxor\\b";
           foreach (const QString &pattern, keywordPatterns) {
               rule.pattern = QRegularExpression(pattern);
               rule.format = keywordFormat;
               highlightingRules.append(rule);

           }

           classFormat.setFontWeight(QFont::Bold);
           classFormat.setForeground(Qt::darkMagenta);
           rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
           rule.format = classFormat;
           highlightingRules.append(rule);

           singleLineCommentFormat.setForeground(Qt::darkMagenta);
           rule.pattern = QRegularExpression("--[^\n]*");
           rule.format = singleLineCommentFormat;
           highlightingRules.append(rule);

           multiLineCommentFormat.setForeground(Qt::red);
       //! [3]

       //! [4]
           quotationFormat.setForeground(Qt::darkGreen);
           rule.pattern = QRegularExpression("\".*\"");
           rule.format = quotationFormat;
           highlightingRules.append(rule);
       //! [4]

       //! [5]
           functionFormat.setFontItalic(true);
           functionFormat.setForeground(QColor(240,240,0));
           rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
           rule.format = functionFormat;
           highlightingRules.append(rule);
       //! [5]

       //! [6]
           commentStartExpression = QRegularExpression("/\\*");
           commentEndExpression = QRegularExpression("\\*/");

           QSyntaxHighlighter::rehighlight();
           }


    if(a==1){
        HighlightingRule rule;

        keywordFormat.setForeground(QColor(128,0,128));


        keywordFormat.setFontWeight(QFont::Bold);
        QStringList keywordPatterns;
        keywordPatterns << "\\babs\\b" << "\\baccess\\b" << "\\bafter\\b"
                        << "\\balias\\b" << "\\ball\\b" << "\\band\\b"
                        << "\\barchitecture\\b" << "\\barray\\b" << "\\bassert\\b"
                        << "\\battribute\\b" << "\\bbegin\\b" << "\\bblock\\b"
                        << "\\bbody\\b" << "\\bbuffer\\b" << "\\bbus\\b"
                        << "\\bconstant\\b" << "\\bdisconnect\\b" << "\\bdownto\\b"
                        << "\\belse\\b" << "\\belsif\\b" << "\\bend\\b"
                        << "\\bentity\\b" << "\\bexit\\b" << "\\bfile\\b"
                        << "\\bfor\\b" << "\\bfunction\\b" << "\\bgenerate\\b"
                        << "\\bgeneric\\b" << "\\bgroup\\b" << "\\bguarded\\b"
                        << "\\bif\\b" << "\\bimpure\\b" << "\\binertial\\b"
                        << "\\binout\\b" << "\\bis\\b" << "\\blabel\\b"
                        << "\\blibrary\\b" << "\\blinkage\\b" << "\\bliteral\\b"
                        << "\\bloop\\b" << "\\bmod\\b" << "\\bmap\\b"
                        << "\\bnand\\b" << "\\bnew\\b" << "\\bnext\\b"
                        << "\\bnor\\b" << "\\bnot\\b" << "\\bnull\\b"
                        << "\\bof\\b" << "\\bon\\b" << "\\bopen\\b"
                        << "\\bor\\b" << "\\bothers\\b" << "\\bout\\b"
                        << "\\bpackage\\b" << "\\bport\\b" << "\\bpostponed\\b"
                        << "\\bprocedure\\b" << "\\bprocess\\b" << "\\bpure\\b"
                        << "\\brange\\b" << "\\brecord\\b" << "\\bregister\\b"
                        << "\\breject\\b" << "\\brom\\b" << "\\breport\\b"
                        << "\\breturn\\b" << "\\brol\\b" << "\\bror\\b"
                        << "\\bselect\\b" << "\\bseverity\\b" << "\\bsignal\\b"
                        << "\\bshared\\b" << "\\bsll\\b" << "\\bsla\\b"
                        << "\\bsra\\b" << "\\bsrl\\b" << "\\bsubtype\\b"
                        << "\\bthen\\b" << "\\bto\\b" << "\\btransport\\b"
                        << "\\btype\\b" << "\\bunaffected\\b" << "\\bunits\\b"
                        << "\\buntil\\b" << "\\buse\\b" << "\\bvariable\\b"
                        << "\\bwait\\b" << "\\bwhen\\b" << "\\bwhile\\b"
                        << "\\bcase\\b" << "\\bcomponent\\b" << "\\bconfiguration\\b" << "\\bin\\b"
                        << "\\bwith\\b" << "\\bxnor\\b" << "\\bxor\\b";
        foreach (const QString &pattern, keywordPatterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
    //! [0] //! [1]
        }
    //! [1]

    //! [2]
        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
        rule.format = classFormat;
        highlightingRules.append(rule);
    //! [2]

    //! [3]
        singleLineCommentFormat.setForeground(QColor(0,128,0));
        rule.pattern = QRegularExpression("--[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(Qt::red);
    //! [3]

    //! [4]
        quotationFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegularExpression("\".*\"");
        rule.format = quotationFormat;
        highlightingRules.append(rule);
    //! [4]

    //! [5]
        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = functionFormat;
        highlightingRules.append(rule);
    //! [5]

    //! [6]
        commentStartExpression = QRegularExpression("/\\*");
        commentEndExpression = QRegularExpression("\\*/");

        QSyntaxHighlighter::rehighlight();
           }
    }


//! [7]
void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
//! [7] //! [8]
    setCurrentBlockState(0);
//! [8]

//! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
//! [11]
