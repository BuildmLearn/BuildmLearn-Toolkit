/*
  Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the BuildmLearn nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef TEXTFACTORY_H
#define TEXTFACTORY_H

#include "definitions/definitions.h"

#include <QDateTime>


/// \brief Functionality for working with text.
class TextFactory {
  private:
    // Constructors and destructors.
    explicit TextFactory();

  public:
    /// \brief Does case-insensitive comparison of two strings.
    /// \param lhs First string.
    /// \param rhs Second string.
    /// \return Returns true if lhs is "smaller" than rhs.
    static inline bool isCaseInsensitiveLessThan(const QString &lhs, const QString &rhs) {
      return lhs.toLower() < rhs.toLower();
    }

    /// \brief Tries to parse input textual date/time representation.
    /// \param date_time String of date/time to parse.
    /// \return Returns invalid date/time if processing fails.
    /// \note This method tries to always return time in UTC+00:00.
    static QDateTime parseDateTime(const QString &date_time);

    /// \brief Converts 1970-epoch miliseconds to date/time.
    /// \param milis_from_epoch Number of miliseconds.
    /// \return This apparently returns date/time in localtime.
    static QDateTime parseDateTime(qint64 milis_from_epoch);

    /// \brief Shortens input string according to given length limit.
    /// \param input Input string.
    /// \param text_length_limit Limit length.
    /// \return Returns shortened string.
    static QString shorten(const QString &input, int text_length_limit);
};

#endif // TEXTFACTORY_H
